
package xmlParser;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import org.xml.sax.SAXParseException;

import Database.PADSQL;

//import SQL.PADSQL;


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
						
			Answer answer = new Answer( PADSQL.SendQuery(request.toSQL(), request.getNumberOfObjects()),
					request.getOffset() );
			
			//Answer answer = new Answer();
			
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
			// Major error, probably bug in the server code.
			
			// Spara undan requesten, kolla varför felet inträffade!
		}
		
		printStringToFile( XMLanswer, answerFile );

	}

	
	private void printStringToFile( File XMLfile, String s )
	{
		
		//System.out.println(s);
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
