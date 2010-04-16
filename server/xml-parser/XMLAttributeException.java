
public class XMLAttributeException extends XMLParseException
{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -928996669994749150L;
	String WhichAttribute;
	String WhatValue;


	  public XMLAttributeException(String message, String WhichTag , String WhichAttribute, String WhatValue)
	  {
		  super(message, WhichTag);
		  this.WhichAttribute = WhichAttribute;
		  this.WhatValue = WhatValue;
	  }
	  
	  public XMLAttributeException(String message, String WhichTag , String WhichAttribute)
	  {
		  super(message, WhichTag);
		  this.WhichAttribute = WhichAttribute;
		  this.WhatValue = null;
	  }
	  
	  public String getWhichAttribute()
	  {
		  return WhichAttribute;
	  }
	
	  public String getWhatValue()
	  {
		  return WhatValue;
	  }
}
