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

package snor;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

import xmlParser.FileToParse;
import Files.RequestFile;


class snortHead extends Thread {

    private Socket clientSocket       = null;
    RequestFile request;
    
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
        String fileName = time + "_" + Integer.toHexString(random);
        request = new RequestFile( new File( fileName + "_received.xml" ),
    			new File( fileName + "_send.xml" ) );
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
            int fileLength = 1024*1024;
            byte[] byteArray = new byte[fileLength];
            
            InputStream is = clientSocket.getInputStream();
            int readBytes = is.read(byteArray);
            
            BufferedOutputStream bos = new BufferedOutputStream( new FileOutputStream( request.getRequest() ) );
            bos.write(byteArray, 0, readBytes);
            bos.flush();
            
            /*******************************************************************
             * Anropar parser.
             */
             new FileToParse().parseFile( request );
            
            /*******************************************************************
             * Skickar filen.
             */
            fileLength = (int)request.getAnswer().length();
            byteArray = new byte[fileLength];
            
            BufferedInputStream bis = new BufferedInputStream( new FileInputStream( request.getAnswer() ) );
            bis.read(byteArray, 0, fileLength);
            
            OutputStream os = clientSocket.getOutputStream();
            os.write(byteArray, 0, fileLength);
            os.flush();

            clientSocket.close();
        } catch(IOException e) {
            System.err.println(e);
            
            request.delete();
            
            System.exit(-1);
        }
        
        /***********************************************************************
         * Vi tar bort filerna när vi är klara.
         */

        request.delete();
        
    }
}
