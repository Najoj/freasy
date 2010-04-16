
public class XMLParseException extends Exception
{

	/**
	 * 
	 */
	private static final long serialVersionUID = 8967332450214734380L;
	
	String WhichTag;


	  public XMLParseException(String message, String WhichTag)
	  {
		  super(message);
		  this.WhichTag = WhichTag;
	  }
	  
	  public String getWhichTag()
	  {
		  return WhichTag;
	  }

}
