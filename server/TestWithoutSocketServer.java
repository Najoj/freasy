
import java.io.File;

import Static.Initializer;
import xmlParser.FileToParse;

public class TestWithoutSocketServer {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		
		// TODO Auto-generated method stub

		Initializer.initialize();	// Körs en gång i början av programmet, är statisk.	
		
		File input = new File("/home/olle/workspace/MvkServer-XML/src/testrequest.xml");
		File output = new File("/home/olle/workspace/MvkServer-XML/src/testanswer.xml");
		
		FileToParse parser = new FileToParse();		
		parser.parseFile( input, output );
			
		
	}

}
