import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import org.xml.sax.SAXParseException;

/**
 * @author olle
 *
 */
public class FileToParse
{
	
	/*
	 * Inputs a File and recieves a File that answers according to the input.
	 * 
	 * @author Olle Hassel
	 * @param an XML-file instanced as a File object
	 * @return an XML-file answer to the request, or an exception-xml file if unable to parse
	 */
	public void parseFile( File XMLrequest, File XMLanswer )
	{
		Request request = new Request( XMLrequest );
		
		String answerFile = null;
		
		try
		{
			request.parseXML();
			
			//System.out.println(request.toString());
			//System.out.println(request.toSQL());	
			
			Answer answer = new Answer();
			answerFile = answer.exportXML();
			
			//System.out.println( answer.toString() );
			
		}
		catch ( XMLParseException e )
		{
			ExceptionParser error = new ExceptionParser();
			answerFile = error.parseException( XMLanswer, e );
		}
		catch ( SAXParseException e )
		{
			ExceptionParser error = new ExceptionParser();
			answerFile = error.parseException( XMLanswer, e );	
		}
		catch ( Exception e )
		{
			
		}
		
		//printStringToFile( XMLanswer, answerFile );
		System.out.println( answerFile );

	}
	
	private void printStringToFile( File XMLfile, String s )
	{
        try 
        {
        	BufferedOutputStream outputFile = new BufferedOutputStream( new FileOutputStream( XMLfile ) );
        	// Print string
            outputFile.write( s.getBytes() );
            outputFile.flush();
        }
        catch (IOException e)  
        {
        	// Exception!
        }
	}

}
