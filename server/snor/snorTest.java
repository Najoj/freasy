/******************************************************************************\
 *  
 *  snorTest.java
 *
 *  Skriven av Johan Öhlin
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.17
 *  
 *  Beskrivning:  Testar så att snor.java fungerar som den är menad att göra.
 *                När den körs ska filen TAMOT vara exakt samma som SKICKA.
 *                Dessutom ska en XML-fil finnas med samma innehåll, givet att
 *                filerna inte tas bort i snortHead.java.
 *  
\******************************************************************************/

package snor;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
//import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class snorTest {
    /**
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     *  XXX  Kom ihåg att ändra dessa!  XXX
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     */
    private static final int PORT = 8989;
    private static final File skicka = new File("SKICKA");
    private static final File taemot = new File("TAMOT");
    private static int fileLength;//, i;
    
    private static byte[] byteArray = null;
    private static Socket socket = null;
    //private static File file = null;
    
    private static BufferedInputStream bis = null;
    private static BufferedOutputStream bos = null;
    private static FileInputStream fis = null;
    private static FileOutputStream fos = null;
    private static InputStream is = null;
    private static OutputStream os = null;
    
    /**
     *  Main-metod.
     */
    public static void main(String args[]) throws IOException {
        /***********************************************************************
         *  Skickar till server.
         */
        System.out.print("Skickar till server... ");
        socket = new Socket("localhost", PORT);
        
        fileLength = (int)skicka.length();
        byteArray  = new byte[fileLength];
        
        fis = new FileInputStream(skicka);
        bis = new BufferedInputStream(fis);
        bis.read(byteArray, 0, fileLength);
        
        os = socket.getOutputStream();
        os.write(byteArray, 0, fileLength);
        os.flush();

        System.out.println("Klar!");
        
        /***********************************************************************
         *  Tar emot från server.
         */
        System.out.print("Tar emot från server... ");

        fileLength = 1024*1024;
        byteArray  = new byte[fileLength];
        int current;
        
        is = socket.getInputStream();

        int bytesRead = is.read(byteArray, 0, fileLength);
        current = bytesRead;

        do {
            bytesRead = is.read(byteArray, current, (fileLength-current));
            if(bytesRead >= 0) current += bytesRead;
        } while(bytesRead > -1);
        is.close();

        fos = new FileOutputStream(taemot);
        bos = new BufferedOutputStream(fos);
        bos.write(byteArray, 0, current);
        bos.flush();
        bos.close();
        
        socket.close();
        System.out.println("Klar!");
        
        System.out.println("Hej då.");
        System.exit(0);
    }
}
