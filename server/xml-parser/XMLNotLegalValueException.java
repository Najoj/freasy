
public class XMLNotLegalValueException extends XMLParseException
{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -3960221332061562911L;
	String WhichAttribute;
	String WhatValue;


	  public XMLNotLegalValueException(String message, String WhichTag , String WhichAttribute, String WhatValue)
	  {
		  super(message, WhichTag);
		  this.WhichAttribute = WhichAttribute;
		  this.WhatValue = WhatValue;
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
