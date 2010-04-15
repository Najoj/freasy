
import java.io.File;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub

		Constants.Initialize();
		Request request = new Request(new File("/home/olle/workspace/MvkServer-XML/src/testrequest.xml") );
		System.out.println(request.toString());
		System.out.println(request.toSQL());
		
	}

}
