
public class XMLTagNotFoundException extends XMLParseException
{
	
		/**
		 * 
		 */
		private static final long serialVersionUID = 6832219136405216708L;

		public XMLTagNotFoundException(String message, String WhichTag)
		{
			super(message, WhichTag);
		}
		
		public XMLTagNotFoundException(String WhichTag)
		{
			super("The tag <"+WhichTag+"> wasn't found when parsing, is required.", WhichTag);
		}
	  
	
}
