import java.io.File;

/**
 * @author olle
 *
 */
public class FileToParse
{
	
	/*
	 * Constructor 
	 * @author Olle Hassel
	 */
	public FileToParse()
	{
		
	}

	
	/*
	 * Inputs a File and recieves a File that answers according to the input.
	 * 
	 * @author Olle Hassel
	 * @param an XML-file instanced as a File object
	 * @return an XML-file answer to the request, or an exception-xml file if unable to parse
	 */
	public File parseFile( File XMLrequest )
	{
		Request request = new Request( XMLrequest );
		
		System.out.println(request.toString());
		System.out.println(request.toSQL());
		
		return null;
	}

}
