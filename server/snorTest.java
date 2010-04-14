/******************************************************************************\
 *  
 *  snorTest.java
 *
 *  Skriven av Johan Öhlin, 2010.
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.12
 *  
 *  Beskrivning:  Testar så att snor.java fungerar som den är menad att göra.
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
     *  XXX  Kom ihåg att ändra denna!  XXX
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     */
    private static final int PORT = 8989;
    private static final String skicka = "snorTest.java";   //  :-O
    private static final String taemot = "FIL";   //  :-O
    private static int fileLength, i;
    
    private static Socket socket = null;
    private static File file = null;
    private static OutputStream os = null;
    private static byte[] byteArray = null;
    private static InputStream instream = null;
    private static FileOutputStream fos = null;
    
    /**
     *  Main-metod.
     */
    public static void main(String args[]) {
        /**
         *  Ansluter till server.
         */
        try {
            socket = new Socket("localhost", PORT);
        } catch (UnknownHostException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        } catch (IOException e) {
            System.err.println("Error: " + e);
            System.exit(-1);
        }
        
        /**
         *  Skickar till server.
         */
        try {
            file = new File(skicka);
        } catch(NullPointerException e) {
            System.err.println(e);
        }

        /**
         * Gör en File till en byte[].
         */
        byteArray  = new byte[(int)skicka.length()];
        fileLength = (int)skicka.length();
        i = 0;
        try {
            instream = new FileInputStream(skicka);
            while((byteArray[i] = (byte)instream.read()) > -1 && (++i) < fileLength) {}

        } catch(FileNotFoundException e) {
            System.err.println(e);
            System.exit(-1);
        } catch(IOException e) {
            System.err.println(e);
            System.exit(-1);
        }
        
        /**
         * Får en OutputStream av vår socket, och skickar byte[].
         */
        try {
            OutputStream os = socket.getOutputStream();
            os.write(byteArray);
            os.close();
        } catch(IOException e) {
            System.err.println(e);
            System.exit(-1);
        }
        
        
        /**
         *  Tar emot från server.
         */
        byteArray = new byte[1024*1024];
        i = 0;
        try {
            instream = socket.getInputStream();
            while((byteArray[i] = (byte)instream.read()) > -1 && (++i) < fileLength) {}
            instream.close();
        } catch(IOException e) {
            System.err.println(e);
            System.exit(-1);
        }
        
        /**
         * Här har vi byte:arna i filen. Nu ska vi skriva den till filen, vilket
         * görs med FileOutputStream.
         */
        try {
            fos = new FileOutputStream(taemot);
            fos.write(byteArray, 0, i);
            fos.close();
        } catch(FileNotFoundException e) {
            System.err.println(e);
            System.exit(-1);
        } catch(IOException e) {
            System.err.println(e);
            System.exit(-1);
        } 

        /**
         *  Stänger anslutning till server.
         */
        try {
            socket.close();
        } catch(IOException e) {
            System.err.println(e);
            System.exit(-1);
        }
        
        System.exit(0);
    }
}
