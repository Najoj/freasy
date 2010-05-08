/******************************************************************************\
 *  
 *  Send aNd Only Recive THrEAD     (SNORTHEAD)
 *
 *  Writtend by Johan Öhlin     and Olle Hassel
 *              johanohl@kth.se     ohassel@kth.se
 *
 *  License:  GNU General Public License, version 2
 *
 *  Version:  2010.04.23
 *  
 *  Description:  The thread which is in charge to recive XML files, send the to
 *                the XML parser and then send an XML file back.
 *  
\******************************************************************************/

package snor;

/*******************************************************************************
 *  Java library imports.
 */
//import java.io.BufferedInputStream;
//import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;

import xmlParser.FileToParse;
import Files.RequestFile;


/*******************************************************************************
 * The thread which is in charge to recive XML files, send the to the XML parser
 * and then send an XML file back.
 * @brief   Thread
 * @author  Johan Öhlin <johanohl@kth.se>
 * @author  Olle Hassel <ohassel@kth.se>
 * @note    "Don't you think that if I was wrong I'd know it?" -- Sheldon Cooper
 */
class snortHead extends Thread {

    private Socket clientSocket;
    RequestFile request;
    
    /***************************************************************************
     * The constructor that calls the Thread class, saves the clients socket and
     * constructs the fileNames standard part.
     * @author  Johan Öhlin <johanohl@kth.se>
     * @author  Olle Hassel <ohassel@kth.se>
     * @note    Change the filenames if you want to.
     */
    snortHead(Socket clientSocket, long time, int random) {
        super("snortHead");
        this.clientSocket = clientSocket;
       
        /***********************************************************************
         * File name format: (seconds since January 1, 1970)_(a pseudo random
         * hexadecimal integer)_("request" or "answer").xml
         */
        String fileName = time + "_" + Integer.toHexString(random);
        request = new RequestFile(
                    "",
                    "",
                    fileName);
          
    }
    
    /***************************************************************************
     * @brief   Let the receiving and sending begin!
     * @author  Johan Öhlin <johanohl@kth.se>
     * @author  Olle Hassel <ohassel@kth.se>
     */
    public void run() {
        try {
        	
        	System.out.print("Anslutning skapad.");
        	System.out.print("Thread ID: " + this.getId() );
        	System.out.println();
        	
                /***************************************************************
                 *  Start the receiving
                 */
                // Expected maximal file length.
            	int maxFileLength = 5*1024;
                byte[] byteArray = new byte[maxFileLength];
                
                
                InputStream in = clientSocket.getInputStream();              	
                int requestFileLength = in.read(byteArray);
                String string_request = new String(byteArray);
                
                int pos = string_request.indexOf("<");
                if(pos != 0) {
                	String substring = string_request.substring(pos);
                	string_request = "<request>" + substring;
                }
    
                //DEBUG
                System.out.println(string_request); 
            	
             	/***************************************************************
             	*  Convert input byte[] to request file
             	*/
            	
            	//FilePrinter.printArrayToFile(byteArray, request.getRequest(), requestFileLength);
            	request.setRequest(string_request);
                
            	/***************************************************************
             	* Call parser.
             	*/
            	new FileToParse().parseFile( request );
            	
             	/***************************************************************
             	*  Convert answer file to byte[]
             	*/
            	
             	//int answerFileLength = (int)request.getAnswer().length();
            	//byteArray = new byte[answerFileLength];
            	
            	//FilePrinter.printFileToArray(byteArray, request.getAnswer(), answerFileLength);
            
             	/***************************************************************
             	*  Start the sending of file
             	*/
            	
            	OutputStream out = clientSocket.getOutputStream();
            	//out.write(byteArray, 0, answerFileLength);
            	out.write(request.getAnswer().getBytes());
            	
            	out.flush();
          		
                /***************************************************************
                 * Closes connection
                 */
                in.close();
                out.close();
            	clientSocket.close();

        } 
        catch (SocketException e) 
        {
        	System.err.println( e.getMessage() );
        }
        
        catch(IOException e) 
        {
            System.err.println(e);
            request.delete();
            System.exit(-1);
        }
        

        /***********************************************************************
         * Remove files when finished.
         */
        request.delete();

    }
}
