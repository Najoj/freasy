/******************************************************************************\
 *  
 *  Send aNd Only Recive    (SNOR)
 *
 *  Writtend by Johan Öhlin     and Olle Hassel
 *              johanohl@kth.se     ohassel@kth.se
 *
 *  License:  GNU General Public License, version 2
 *
 *  Version:  2010.04.23
 *  
 *  Description:  Server. Listens to a socket for a connection to come which
 *                then is passed on to snortHead.java. See Java's API on Socket
 *                and ServerSocket for more understanding.
 *  
\******************************************************************************/

package snor;

/*******************************************************************************
 *  Java library imports.
 */
import java.io.IOException;
import java.net.ServerSocket;
import java.util.Date;
import java.util.Random;

import Static.Initializer;

/*******************************************************************************
 * Listens to a socket for a connection to come which then is passed on to
 * snortHead.java class. See Java's API on Socket and ServerSocket for in-depth
 * understanding.
 * @brief   Server
 * @author  Johan Öhlin <johanohl@kth.se>
 * @author  Olle Hassel <ohassel@kth.se>
 * @note    Remember to change \c PORT.
 */
public class SNOR {
    /***************************************************************************
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX XXX XXX XXX
     *  XXX Remember to change for you own purpose! XXX
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX XXX XXX XXX
     */
    private final static int PORT = 80;
    private final static Random random = new Random();

    private static ServerSocket serverSocket;
    /***************************************************************************
     * @author  Johan Öhlin <johanohl@kth.se>
     * @author  Olle Hassel <ohassel@kth.se>
     * @brief   Waits for a handshake.
     * @arg     No arguments what so ever.
     */
    public static void main(String args[]) {
        /***********************************************************************
         * Initializes the Static classes.
         */		
        Initializer.initialize();
                
        /***********************************************************************
         * Attempts to create a ServerSocket on given port.
         */
        try {
            serverSocket = new ServerSocket(PORT);
        } catch(IOException e) {
            System.err.println(new Date() + ": Fel vid försök av att skapa en" + 
                " ServerSocket: " + e);
            System.exit(-1);
        }
        
        /***********************************************************************
         * Accepts all clients coming, unless something bad happens.
         */
        while(true) 
        {
            try {
                System.out.println(new Date() + ": Väntar på svar via port " + PORT);
                new SnortHead( serverSocket.accept(), new Date().getTime(), random.nextInt() ).start();
                System.out.println(" Tråd skapad.");
            } catch(IOException e) {
                System.err.println(new Date() + ": " + e);
            }
            catch ( Exception e )
            {
            	System.err.println(new Date() + ": " + e);
        		System.err.println("error!");
        		System.err.println("Exception: "+e.getMessage());
        		e.printStackTrace();
            }
                        
        }
    }
}
