
package xmlParser;

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
	
}
