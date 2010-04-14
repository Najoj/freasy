/******************************************************************************\
 *  
 *  Send aNd Only Recive THrEAD     (SNORTHEAD)
 *
 *  Skriven av Johan Öhlin, 2010.
 *             johanohl@kth.se
 *
 *  Licens:   GNU General Public License, version 2
 *
 *  Version:  2010.04.14
 *  
 *  Beskrivning:  Kommer senare.
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
    private int fileLength = 1024^3;    // Förväntad maximal filstorlek på 1 MB.
    private int i;
    
    private byte[] byteArray = null;
    private Socket clientSocket = null;
    private FileOutputStream fos = null;
    private InputStream instream = null;
    private FileInputStream fis = null;
    
    /**
     * Filnamnet är på formatet "(sekunder sedan 01/01/1970)_(pseudoslumpat
     * hexadecimalt värde).xml". Gäller inte toSend, eventuellt. Det namnet
     * bestämmer OlleXML.
     */
    private File recived = new File( new Date().getTime() + "_" +
                            Integer.toHexString(new Random().nextInt()) +
                            ".xml");
    private File toSend;
    
    snortHead(Socket clientSocket) {
    	super();
        this.clientSocket = clientSocket;
        
        /**
         * Det viktigaste. Ta emot filen, skicka vidare filen och skicka
         * tillbaka filen.
         */
        receive();
        //toSend = OlleXML.translator(recived);   // Något i den här stilen.
        send();
        /**
         * Vi tar bort filerna när vi är klara.
         */
        recived.delete();
        toSend.delete();
        
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
        /**
         * Vi använder InputStream för att ta emot en ström.
         */
        byteArray = new byte[fileLength];
        i = 0;
        try {
            instream = clientSocket.getInputStream();
            while((byteArray[++i] = (byte) instream.read()) > -1 && i < fileLength) {
            }
            instream.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        
        /**
         * Här har vi byte:arna i filen. Nu ska vi skriva den till filen, vilket
         * görs med FileOutputStream.
         */
        try {
            fos = new FileOutputStream(recived);
            fos.write(byteArray, 0, i);
            fos.close();
        } catch(FileNotFoundException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
    }
    
    /**
     * Skickar tillbaka en behandlad XML-fil
     */
    private void send() {
        /**
         * Gör en File till en byte[].
         */
        byteArray  = new byte[(int)toSend.length()];
        fileLength = (int) toSend.length();
        i = 0;
        try {
            fis = new FileInputStream(toSend);
            while((byteArray[++i] = (byte)fis.read()) > -1 && i < fileLength) {}
            fis.close();
        } catch(FileNotFoundException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }
        
        /**
         * Får en OutputStream av vår socket, och skickar byte[].
         */
        try {
            OutputStream os = clientSocket.getOutputStream();
            os.write(byteArray);
            os.flush();
            os.close();
        } catch(IOException e) {
            System.err.println(new Date() + ": " + e);
            System.exit(-1);
        }        
    }
    
}
