package Static;

import Database.PADSQL;

public class Initializer 
{
	
	public static void initialize()
	{
		ParserConstants.Initialize();
		
		try	{ PADSQL.Initialize(); }
		catch (Exception e)	
		{ System.err.println("Error att database initialization.");	}
	}

}
