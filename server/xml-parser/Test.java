
import java.io.File;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		
		// TODO Auto-generated method stub

		ParserConstants.Initialize();	// Körs en gång i början av programmet, är statisk.	
		
		File input = new File("/home/olle/workspace/MvkServer-XML/src/testrequest.xml");
		
		FileToParse parser = new FileToParse();		
		File output = parser.parseFile( input );
		
		
	}

}
