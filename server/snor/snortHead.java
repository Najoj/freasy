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

import java.net.SocketException;

import xmlParser.FileToParse;
import Files.RequestFile;
import Static.FilePrinter;


class snortHead extends Thread {

    private Socket clientSocket;
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
        request = new RequestFile( new File( fileName + "_request.xml" ), new File( fileName + "_answer.xml" ) , fileName);
    }
    
    /**
     * Startas av Thread
     */
    public void start() {
        try {  	
        	
        	System.out.println("Connection gjord!");
        	
            /*******************************************************************
             * Tar emot filen.
             */
            // Uppskattad maximal filstorlek, 5 KB.
        	
            
            try
            {
            	InputStream is = clientSocket.getInputStream();              	

            	int maxFileLength = 5*1024;
                byte[] byteArray = new byte[ maxFileLength ];
                
                int requestFileLength = is.read(byteArray);
   
            	BufferedOutputStream bos = new BufferedOutputStream( new FileOutputStream( request.getRequest() ) );
            	bos.write(byteArray, 0, requestFileLength);
            	bos.flush();
            	
            	FilePrinter.printFileToTerminal( request.getRequest() ); // Debug
	
            	/*******************************************************************
             	* Anropar parser.
             	*/
            	new FileToParse().parseFile( request );
            
             	/*******************************************************************
             	* Skickar filen.
             	*/
             	int answerFileLength = (int)request.getAnswer().length();
            	byteArray = new byte[answerFileLength];
            
            	BufferedInputStream bis = new BufferedInputStream( new FileInputStream( request.getAnswer() ) );
            	bis.read(byteArray, 0, answerFileLength);
            
            	OutputStream os = clientSocket.getOutputStream();
            	os.write(byteArray, 0, answerFileLength);
           		os.flush();
          		
            	clientSocket.close();
            
            }
            catch ( SocketException e )
            {
            	System.out.println( e.getMessage() );
            }

            
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
