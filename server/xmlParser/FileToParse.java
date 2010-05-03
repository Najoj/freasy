
package xmlParser;
import java.io.File;
import java.sql.SQLException;

import org.xml.sax.SAXParseException;
import Database.PADSQL;
import Files.RequestFile;
import Static.FilePrinter;


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
	public void parseFile( RequestFile files )
	{
		File XMLrequest = files.getRequest();
		File XMLanswer = files.getAnswer();
		
		Request request = new Request( XMLrequest );
		
		String answerString = null;
		
		try
		{
			request.parseXML();

			//System.out.println(request.toString());
				
			Answer answer = new Answer( PADSQL.SendQuery(request.toSQL( false ), request.getNumberOfObjects()),
					request.getOffset(), PADSQL.getQueryListLength( request.toSQL( true ) ) );

			//Answer answer = new Answer();
			
			answerString = answer.exportXML();
		
			files.appendToLog( "Korrekt forumlerad request. Inga fel." );
			
			//System.out.println( answer.toString() );
			
		}
		catch ( XMLParseException e )
		{
			ExceptionParser error = new ExceptionParser();
			answerString = error.parseException( XMLanswer, e );
			
			files.appendToLog( "Requesten har genrererat ett XMLParseException." );
			
			files.setSave(true);
			
		}
		catch ( SAXParseException e )
		{
			ExceptionParser error = new ExceptionParser();
			answerString = error.parseException( XMLanswer, e );
			
			files.appendToLog( "Requesten har genrererat ett SAXParseException." );
			
			files.setSave(true);
		}
		catch(SQLException e) 
		{
    		System.err.println("error!");
    		System.err.println("Exception: "+e.getMessage());
    		e.printStackTrace();
		}
		catch ( Exception e )
		{
			// Major error, probably bug in the server code.
			
			// Spara undan requesten, kolla varför felet inträffade!
			
			files.appendToLog( "!!- Requesten har genrererat ett ofångat fel, vad har dom gjort?!? -!!" );
			
			files.setSave(true);
		}
		
		FilePrinter.printToFile(XMLanswer, answerString);

	}
}
