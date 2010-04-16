import java.io.File;

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
		
		try
		{
			request.parseXML();
		}
		catch ( XMLAttributeException e )
		{
			// Anropa exception-klassen som parsar exception-xml-filen!
			
			System.out.println("XMLAttributeParseException! \n\n"+e.getMessage()+"\n\n"+e.getWhichTag() + " -> "+ e.getWhichAttribute() + " = " +e.getWhatValue());
		}
		catch ( XMLParseException e )
		{
			System.out.println(e.getMessage()+"\n"+e.getWhichTag());
		}
		catch ( SAXParseException e )
		{
			System.out.println(e.getMessage());
		}
		catch ( Exception e )
		{
			
		}
		
		System.out.println(request.toString());
		//System.out.println(request.toSQL());		
		
		
		//String SQLstatement = request.toSQL();
		
		//Answer answer = new Answer();
		

		//System.out.println( answer.toString() );
		
		//answer.exportXML( XMLanswer );
	}

}
