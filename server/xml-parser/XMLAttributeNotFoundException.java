
public class XMLAttributeNotFoundException extends XMLParseException
{

	/**
	 * 
	 */
	private static final long serialVersionUID = -1922907042255956173L;
	String WhichAttribute;

	public XMLAttributeNotFoundException(String message, String WhichTag, String WhichAttribute)
	{
		super(message, WhichTag);
		this.WhichAttribute = WhichAttribute;
	}
	
	public XMLAttributeNotFoundException(String WhichTag, String WhichAttribute)
	{
		super("The attribute <"+WhichAttribute+"> at tag <"+WhichTag+"> wasn't found when parsing, is required.", WhichTag);
		this.WhichAttribute = WhichAttribute;
	}
	
	  public String getWhichAttribute()
	  {
		  return WhichAttribute;
	  }
	
}
