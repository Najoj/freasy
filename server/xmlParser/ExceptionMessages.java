
package xmlParser;

import Static.ParserConstants;

public class ExceptionMessages 
{
	
	// All esception messages
	
	public static String XMLAttributeNotFoundExceptionMessage( String superTag, String attribute )
	{
		return "The attribute '"+attribute+"' at tag '"+superTag+"' wasn't found when parsing, is required.";
	}

	public static String XMLNotAttributeExceptionMessage( String superTag, String attribute, String extracted )
	{
		return "The attribute '"+ extracted+"' inside tag '"+attribute+"' at tag '" + superTag+"' is not a legal attribute according to spec."+ 
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		  "Must be one of the following: "+ParserConstants.listAllowedAttributes();
	}
	
	public static String XMLNotLegalOperatorExceptionMessage( String superTag, String attribute, String extracted )
	{
		return "The value "+extracted+" in attribute '"+attribute+"' in tag '"+superTag+"' is not an legal operator"+
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		  "Must be an operator of one of the following types.";
	}
	
	public static String XMLNotLegalIntegerExceptionMessage( String superTag, String attribute, String extracted )
	{
		return "The value "+extracted+" in attribute '"+attribute+"' in tag '"+superTag+"' is not an integer"+
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		  "Must be an integer.";
	}
	
	public static String XMLNotLegalMatchesValueExceptionMessage( String superTag, String attribute, String extracted )
	{
		return "The value "+extracted+" in attribute '"+attribute+"' in tag '"+superTag+"' is not a legal matchby field."+
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		  "Must be an text of one of the following standards."+ParserConstants.listAllowedMatchByFilters();
	}
	
	public static String XMLNotLegalASC_DESCExceptionMessage( String superTag, String attribute, String extracted )
	{
		return "The value "+extracted+" in attribute '"+attribute+"' in tag '"+superTag+"' is not a legal 'direction' field."+
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		  "Must be an 'ASC' or 'DESC'"+
		  ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		  "The attribute is not required, if not included request defaults to 'DESC'";
	}
	
	public static String XMLTagNotFoundExceptionMessage( String superTag)
	{
		return "The tag '"+superTag+"' wasn't found when parsing, is required.";
	}
	
	public static String XMLParseNoPADAttributesFoundExceptionMessage( String superTag)
	{
		return "No legal PAD attributes found at tag '"+superTag+"'"+
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		".Must include atleast one legal attribute."+
		ParserConstants.getLineBreak()+ParserConstants.getLineBreak()+
		"Legal attributes are: "+ParserConstants.listAllowedAttributes();
	}
	
	
}
