/******************************************************************************\
 *  
 *  snorTest.java
 *
 *  Skriven av Johan Öhlin
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.16
 *  
 *  Beskrivning:  Testar så att snor.java fungerar som den är menad att göra.
 *                När den körs ska filen TAEMOT vara exakt samma som SKICKA.
 *                Dessutom ska en XML-fil finnas med samma innehåll.
 *  
\******************************************************************************/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class snorTest {
    /**
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     *  XXX  Kom ihåg att ändra dessa!  XXX
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     */
    private static final int PORT = 8989;
    private static final File skicka = new File("SKICKA");
    private static final File taemot = new File("TAMOT");
    private static int fileLength, i;
    
    private static Socket socket = null;
    private static File file = null;
    private static OutputStream os = null;
    private static byte[] byteArray = null;
    private static InputStream is = null;
    private static FileInputStream fis = null;
    private static FileOutputStream fos = null;
    
    /**
     *  Main-metod.
     */
    public static void main(String args[]) {
        /***********************************************************************
         *  Ansluter till server.
         */
        System.out.print("Skapar ny Socket... ");
        try {
            socket = new Socket("localhost", PORT);
        } catch (UnknownHostException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        } catch (IOException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        System.out.println("Klar!");
        
        /***********************************************************************
         *  Skickar till server.
         */
        fileLength = (int) skicka.length();
        System.out.print("Skapar en byte[] av File... ");
        byteArray = new byte[fileLength];
        try {
            fis = new FileInputStream(skicka);
        } catch(FileNotFoundException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        try {
            for(i = 0; i < fileLength; i++)
                byteArray[i] = (byte) fis.read();
            fis.close();
        } catch(IOException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        System.out.println("Klar!");
        
        System.out.print("Skapar en FileOutputStream och skriver... ");
        try {
            os = socket.getOutputStream();
            os.write(byteArray);
        } catch(IOException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        System.out.println("Klar!");
        
        /***********************************************************************
         *  Tar emot från server.
         */
        System.out.print("Skapar en InputStream och läser... ");
        fileLength = 1024*1024;
        byteArray = new byte[fileLength];
        try {
            is = socket.getInputStream();
            i = 0;
            while( (byteArray[i] = (byte) is.read()) != -1 )
                i++;
            is.close();
        } catch(IOException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        System.out.println("Klar!");
        
        System.out.print("Skapar en File av byte[]... ");
        try {
            fos = new FileOutputStream(taemot);
        } catch(FileNotFoundException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        try {
            fos.write(byteArray, 0, (i-1));
            fos.close();
        } catch(IOException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        System.out.println("Klar!");
        
        /***********************************************************************
         *  Stänger anslutning till server.
         */
        System.out.print("Stänger Socket... ");
        try {
            socket.close();
            os.close();
        } catch(IOException e) {
            System.err.println(e);
            System.exit(-1);
        }
        System.out.println("Klar!");
        
        System.out.println("Hej då.");
        System.exit(0);
    }
}
