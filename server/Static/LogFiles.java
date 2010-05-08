package Static;

import Files.Log;
import java.io.File;

public class LogFiles 
{

	private static Log requestLog;
	
	public static void Initialize()
	{
		requestLog = new Log( new File("requestLog") );
	}
	
	public static Log getRequestLog()
	{
		return requestLog;
	}
	
}
