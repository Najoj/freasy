package Static;

import Database.PADSQL;

public class Initializer 
{
	
	public static void initialize()
	{
		ParserConstants.Initialize();
		
		//FilePrinter.setRequestLog( new File("requestLog") );
		
		
		PADSQL.Initialize();
		LogFiles.Initialize();
		/**try	{ PADSQL.Initialize(); }
		catch (Exception e)	
		{ 
			System.err.println("Error att database initialization.");	
			System.err.println(e.getMessage());
		}*/
	}

}
