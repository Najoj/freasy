import java.io.File;

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
		
		String SQLstatement = request.toSQL();
		
		Answer answer = new Answer();
		
		//System.out.println(request.toString());
		//System.out.println(request.toSQL());		
		//System.out.println( answer.toString() );
		
		answer.exportXML( XMLanswer );
	}

}
