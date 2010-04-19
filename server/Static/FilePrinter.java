package Static;

import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;

public class FilePrinter 
{
	
	private static File RequestLog;
	
	public static void setRequestLog( File file )
	{
		RequestLog = file;
	}
	
	public static File getRequestLog()
	{
		return RequestLog;
	}

	public static void printToFile( File file, String s )
	{
		
		//System.out.println(s);
        try 
        {
        	BufferedOutputStream outputFile = new BufferedOutputStream( new FileOutputStream( file ) );
        	// Print string
            outputFile.write( s.getBytes() );
            outputFile.flush();
        }
        catch (IOException e)  
        {
        	// Exception!
        }
        
	}
	
	public static void appendToFile( File file, String s )
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
