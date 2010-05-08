
package Testing;

import java.io.File;
import xmlParser.FileToParse;
import Files.RequestFile;
//import Static.FilePrinter;
import Static.Initializer;

public class MainTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		
		Initializer.initialize();
		
		//FilePrinter.printFileToTerminal(new File("/home/olle/workspace/Freasy/src/testanswer.xml"));
		/*		
		new FileToParse().parseFile( new RequestFile( new File("/home/olle/workspace/Freasy/src/testrequest.xml"),
				new File("/home/olle/workspace/Freasy/src/testanswer.xml"),"TEST" ) );
*/
	}

}
