package Static;

import java.io.File;
import Database.PADSQL;

public class Initializer 
{
	
	public static void initialize()
	{
		ParserConstants.Initialize();
		
		FilePrinter.setRequestLog( new File("requestLog") );
		
		try	{ PADSQL.Initialize(); }
		catch (Exception e)	
		{ System.err.println("Error att database initialization.");	}
	}

}
