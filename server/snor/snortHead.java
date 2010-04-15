/******************************************************************************\
 *  
 *  Send aNd Only Recive THrEAD     (SNORTHEAD)
 *
 *  Skriven av Johan Öhlin
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.16
 *  
 *  Beskrivning:  Trådklass som laddar ner XML-filen, skickar till en behandlare
 *                som i sin tur skickar tillbaka en fil efter kommunikation med
 *                server.
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
import java.util.Date;
import java.util.Random;

class snortHead extends Thread {
    private static int fileLength;
    private static int i;
    
    private static byte[] byteArray = null;
    private static Socket clientSocket = null;
    
    private static FileOutputStream fos = null;
    private static InputStream is = null;
    private static FileInputStream fis = null;
    private static OutputStream os = null;
    
    /**
     * Filnamnet är på formatet "(sekunder sedan 01/01/1970)_(pseudoslumpat
     * hexadecimalt värde).xml". Gäller inte toSend, eventuellt. Det namnet
     * bestämmer Olle.
     */
    private File received = new File( new Date().getTime() + "_" +
                            Integer.toHexString(new Random().nextInt()) +
                            ".xml");
    private File toSend = new File("SKICKA");
    
    snortHead(Socket clientSocket) {
        super();
        this.clientSocket = clientSocket;
    }
    
    public void start() {    
        /**
         * Det viktigaste. Ta emot filen, skicka vidare filen och skicka
         * tillbaka filen.
         */
        receive();
        //toSend = OlleXML.translator(received, toSend);   // Något i den här stilen.
        send();
        
        /**
         * Vi tar bort filerna när vi är klara.
         */
        received.delete();
        toSend.delete();
        
        /**
         * Försöker stänga socket.
         */
        try {
            clientSocket.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        System.exit(0);
    }
    
    /**
     * Tar emot en fil.
     */
    private void receive() {
        // Förväntad maximal filstorlek på 1 MB, vilket är generöst.
        fileLength = 1024*1024*1024;
        byteArray = new byte[fileLength];
        
        /**
         * Skapar InputStream för att hämta strömmen vi tar emot. Den sparas i
         * byteArray.
         */
        try {
            is = clientSocket.getInputStream();
            i = 0;
            while( (byteArray[i] = (byte) is.read()) != -1 )
                i++;
            is.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        /**
         * Skapar FileOutputStream för att skriva vår byteArray till fil.
         */
        try {
            fos = new FileOutputStream(received);
        } catch(FileNotFoundException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        try {
            fos.write(byteArray, 0, (i-1));
            fos.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
    }
    
    /**
     * Skickar tillbaka en behandlad XML-fil
     */
    private void send() {
        // Filens storlek.
        fileLength = (int) toSend.length();
        byteArray = new byte[fileLength];
        /**
         * Läser in filen som ska skickas med FileInputStream.
         */
        try {
            fis = new FileInputStream(toSend);
        } catch(FileNotFoundException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        try {
            fis.read(byteArray);
            fis.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        /**
         * Med en OutputStream skickar vi iväg vår fil på äventyr i stora världen.
         */
        try {
            os = clientSocket.getOutputStream();
            os.write(byteArray);
            os.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
    }
}
