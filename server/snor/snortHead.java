/******************************************************************************\
 *  
 *  Send aNd Only Recive THrEAD     (SNORTHEAD)
 *
 *  Skriven av Johan Öhlin
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.17
 *  
 *  Beskrivning:  Trådklass som laddar ner XML-filen, skickar till en behandlare
 *                som i sin tur skickar tillbaka en fil efter kommunikation med
 *                server.
 *  
\******************************************************************************/

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;


class snortHead extends Thread {
    private static int fileLength, readBytes;
    
    private static ServerSocket serverSocket = null;
    private static Socket clientSocket       = null;
    private static byte[] byteArray          = null;
    private static String name               = null;
    
    private static BufferedOutputStream bos = null;
    private static BufferedInputStream bis  = null;
    private static FileOutputStream fos     = null;
    private static FileInputStream fis      = null;
    private static OutputStream os          = null;
    private static InputStream is           = null;
    private static File received            = null;
    private static File send                = null;
    
    /**
     * En konstruktor som inte gör så vidare mycket alls.
     */
    snortHead(Socket clientSocket, long time, int random) {
        super("snortHead");
        this.clientSocket = clientSocket;
        /**
         * Filnamnet är på formatet "(sekunder sedan 1 januari 1970)_(pseudoslumpat
         * hexadecimalt värde)_(received eller send).xml".
         */
        this.name     = time + "_" + Integer.toHexString(random);
        this.received = new File( name + "_received.xml" );
        this.send     = new File( name + "_send.xml" );
    }
    
    /**
     * Startas av Thread
     */
    public void start() {
        try {
            /*******************************************************************
             * Tar emot filen.
             */
            // Uppskattad maximal filstorlek, 1 MB. Det är generöst.
            fileLength = 1024*1024;
            byteArray = new byte[fileLength];
            
            is = clientSocket.getInputStream();
            readBytes = is.read(byteArray);
            
            fos = new FileOutputStream(received);
            bos = new BufferedOutputStream(fos);
            bos.write(byteArray, 0, readBytes);
            bos.flush();
            
            /*******************************************************************
             * Anropar parser.
             */
             new FileToParse().parseFile(input, output);
            
            /*******************************************************************
             * Skickar filen.
             */
            fileLength = (int)send.length();
            byteArray = new byte[fileLength];
            
            fis = new FileInputStream(send);
            bis = new BufferedInputStream(fis);
            bis.read(byteArray, 0, fileLength);
            
            os = clientSocket.getOutputStream();
            os.write(byteArray, 0, fileLength);
            os.flush();

            clientSocket.close();
        } catch(IOException e) {
            System.err.println(e);
            received.delete();
            send.delete();
            System.exit(-1);
        }
        
        /***********************************************************************
         * Vi tar bort filerna när vi är klara.
         */
        /* XXX På begäran av Olle ligger dessa filer kvar till en början.
        received.delete();
        send.delete();
        */
    }
}
