
package xmlParser;

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
		
	  public String getWhichAttribute()
	  {
		  return WhichAttribute;
	  }
	
}
