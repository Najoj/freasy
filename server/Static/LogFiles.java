package Static;

import Files.Log;
import java.io.File;

public class LogFiles 
{

	private static Log requestLog;
	private static Log exceptionLog;
	
	public static void Initialize()
	{
		requestLog = new Log( new File("requestLog") );
		exceptionLog = new Log( new File("exceptionLog") );
	}
	
	public static Log getRequestLog()
	{
		return requestLog;
	}
	
	public static Log getExceptionLog()
	{
		return exceptionLog;
	}
	
}
