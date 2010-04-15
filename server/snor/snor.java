/******************************************************************************\
 *  
 *  Send aNd Only Recive    (SNOR)
 *
 *  Skriven av Johan Öhlin
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.16
 *  
 *  Beskrivning:  Server. Lyssnar på socket som server och startar ny tråd som
 *                        tar hand om resten.
 *  
\******************************************************************************/

import java.net.ServerSocket;
import java.io.IOException;
import java.util.Date;

/**
 * Använder Javas ServerSocket-klass som lyssnas för att kunna ta emot en
 * förfrågan som sedan vidarebefodras till trådklassen snortHead.java.
 * @author  Johan Öhlin <johanohl@kth.se>
 * @note    Byt port om du behöver.
 */
class snor {
    /*
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     *  XXX  Kom ihåg att ändra denna!  XXX
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     */
    private static final int PORT = 8989;
    private static ServerSocket serverSocket;    
    /**
     * @author  Johan Öhlin <johanohl@kth.se>
     * @brief   Startar avlyssningen.
     * @param   <Ingenting>
     * @return  <Ingenting>
     */
    public static void main(String args[]) {
        /**
         * Längden av indata ska vara noll, annars antar vi att något är fel.
         */
        if(args.length != 0) {
            System.err.println(new Date() + ": För många argument (" +
                args.length + " stycken) så jag antar att något är fel.");
            /**
             * Eventuellt något onödigt, men kan vara intressant. Får anta att
             * vi inte hamnar här så värst ofta.
             */ 
            for(int i = 0; i < args.length; i++)
                System.err.print(args[i] + " ");
            System.err.println("");
            System.exit(-1);
        }
        
        /**
         * Försöker att skapa en ServerSocket.
         */
        try {
            serverSocket = new ServerSocket(PORT);
        } catch(IOException e) {
            System.err.println(new Date() + ": Fel vid försök av att skapa en" + 
                " ServerSocket: " + e);
            System.exit(-1);
        }
        /**
         * Accepterar klienter som kommer.
         */
        while(true) {
            try {
                System.out.print(new Date() + ": Väntar... ");
                new Thread( new snortHead( serverSocket.accept() ) ).start();
                System.out.println("Ny tråd skapad.");
            } catch(IOException e) {
                System.err.println(new Date() + ": " + e);
            }
        }
    }
}
