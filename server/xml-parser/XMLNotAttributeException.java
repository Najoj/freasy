
public class XMLNotAttributeException extends XMLParseException
{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -928996669994749150L;
	String WhichAttribute;
	String WhatValue;


	  public XMLNotAttributeException(String message, String WhichTag , String WhichAttribute, String WhatValue)
	  {
		  super(message, WhichTag);
		  this.WhichAttribute = WhichAttribute;
		  this.WhatValue = WhatValue;
	  }
	  
	  public XMLNotAttributeException(String WhichTag, String WhichAttribute, String WhatValue)
	  {
		  super("The attribute '"+ WhatValue+"' inside tag <"+WhichAttribute+"> at tag <" + WhichTag+"> is not a legal attribute according to spec."+
				  "\n Must be one of the following:\n\n"+ParserConstants.listAllowedAttributes(), WhichTag);
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
