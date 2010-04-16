import java.io.File;

import org.xml.sax.SAXParseException;


public class ExceptionParser 
{
	
	File XMLexception;

	public String parseException( File XMLexception, XMLParseException e )
	{
		this.XMLexception = XMLexception;
		
		return parseMessageToXML( e.getMessage() );
	}
	
	public String parseException( File XMLexception, SAXParseException e )
	{
		this.XMLexception = XMLexception;
		
		return parseMessageToXML( e.getMessage() );
	}
	
	private String parseMessageToXML( String message )
	{
		return message;
		
	}
	
}
