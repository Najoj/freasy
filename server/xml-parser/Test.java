
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
		File output = new File("/home/olle/workspace/MvkServer-XML/src/testanswer.xml");
		
		FileToParse parser = new FileToParse();		
		parser.parseFile( input, output );
			
		
	}

}
