package Files;

import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;

public class Log 
{
        
        private File RequestLog;
        
        public Log( File file )
        {
                RequestLog = file;
        }
        

        public void printToFile( String s ) // Replaces contents of file with the output.
        {

                //System.out.println(s);
        try 
        {
                BufferedOutputStream outputFile = new BufferedOutputStream( new FileOutputStream( RequestLog ) );
                // Print string
            outputFile.write( s.getBytes() );
            outputFile.flush();
        }
        catch (IOException e)  
        {
                // Exception!
        }
        
        }
        
        public void appendToLog( String s )
        {
        	appendToFile( RequestLog, s );
        }
         
        private void appendToFile( File file, String s )
        {
                
                BufferedWriter bw = null;
                //System.out.println(s);
        try 
        {
                bw = new BufferedWriter(new FileWriter(file, true));
                bw.write(s);
                bw.newLine();
                bw.flush();
        }
        catch (IOException e)  
        {
                // Exception!
        }
        finally 
        {                       // always close the file
                if (bw != null)
                        try { bw.close(); } 
                        catch (IOException ioe2) 
                        {
                        // just ignore it
                        }
        }
            
        
        }
}