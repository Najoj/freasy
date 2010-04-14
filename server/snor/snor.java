/******************************************************************************\
 *  
 *  Send aNd Only Recive    (SNOR)
 *
 *  Skriven av Johan Öhlin, 2010.
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.14
 *  
 *  Beskrivning:  Server. Lyssnar på socket som server och startar ny tråd.
 *  
\******************************************************************************/

import java.net.ServerSocket;
import java.io.IOException;
import java.util.Date;

/**
 * Lyssnar på ServerSocket för att få enheter som kontaktar.
 */
class snor {
    private static ServerSocket serverSocket;

    /**
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     *  XXX  Kom ihåg att ändra denna!  XXX
     *  XXX XXX XXX XXX XXX XXX XXX XXX XXX
     */
    private static final int PORT = 8989;
    
    /**
     * Huvudmetoden. Startar avlyssningen. Ska _inte_ ha någon indata.
     */
    public static void main(String args[]) {
        /**
         * Kollar längden på indata. Ska vara noll.
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
                new snortHead(serverSocket.accept()).start();
            } catch(IOException e) {
                System.err.println(new Date() + ": " + e);
            }
        }
    }
}
