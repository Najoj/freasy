package Files;

import java.io.File;
import java.util.Date;

import Static.FilePrinter;

public class RequestFile 
{

	private File Request;
	private File Answer;

	private StringBuilder log;
	
	private boolean Save;
	
	public RequestFile( File Request, File Answer, String FileName)
	{
		this.Request = Request;
		this.Answer = Answer;
		Save = false;
		log = new StringBuilder();
		log.append( new Date().toString() + " : " + FileName + " : " );
	}
	
	public void appendToLog( String s )
	{
		log.append( s );
	}
	
	public void setSave( boolean save )
	{
		this.Save = save;
	}
	
	public File getRequest()
	{
		return Request;
	}
	
	public File getAnswer()
	{
		return Answer;
	}
	
	private void writeLogEntry()
	{
		FilePrinter.appendToFile( FilePrinter.getRequestLog(), log.toString() );
	}
	
	public void delete()
	{
		writeLogEntry();
		
		if (!Save)
		{
			Request.delete();
			Answer.delete();
		}
		else
		{
			appendToLog( Request.getName() + " - " + Answer.getName() );
			
			Answer.delete();
		}
	}
	
}
