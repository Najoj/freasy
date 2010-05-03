
package xmlParser;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

import java.util.Iterator;
import java.util.Stack;

import java.io.File;
import java.io.IOException;

import Static.ParserConstants;


public class Request // implements InterfaceRequest 
{
	
	File XMLrequest;
	
	private class MatchBy_Object
	{
		String Attribute;
		String Operator;
		String Value;
		
		public MatchBy_Object( String Attribute, String Operator, String Value )
		{
			this.Attribute = Attribute;
			this.Operator = Operator;
			this.Value = Value;
		}
		
		public String getAttribute()
		{
			return Attribute;
		}
		
		public String getOperator()
		{
			return Operator;
		}
		
		public String getValue()
		{
			return Value;
		}
	}
	
	private Stack<MatchBy_Object> MatchByStack;

	// order by. The list will be sorted according to the following attribute.
	private String OrderBy; 
	// order by. Defines wherver the objects are to be ordered ascending or descending to the chosen attribute. Must be one, cannot be both.
	private String OrderByAscDesc; // Defaulted to descending.

	private int Offset;  // answer format. The offset of where in the list to begin collecting objects to return.
	
	private int NumberOfObjects;  // answer format. Maximum number of objects returned.
             
    // Define a "reference PAD object", the answer will include the following attributes.
	//private PAD ReferenceObject;
	private Stack<String> ReferenceObject;
        
        
        
	public Request( File XMLrequest )
	{
		this.XMLrequest = XMLrequest;
		
		MatchByStack = new Stack<MatchBy_Object>();		
		ReferenceObject = new Stack<String>();

	}
		
	private class AttributeParser
	{
	    private Element elementMemory = null;
	    private NodeList nodeListMemory = null;
	    
		private boolean existsAttribute( Element element, String attribute ) // attribute and lnie is sent to reuse the memory space.
		{
			nodeListMemory = element.getElementsByTagName(attribute);
			if ( nodeListMemory.getLength() != 0 )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	    
		private String extractAttribute( Element element, String attribute, String superTag ) throws XMLNotAttributeException, XMLAttributeNotFoundException // attribute and lnie is sent to reuse the memory space.
		{
			nodeListMemory = element.getElementsByTagName(attribute);
			if ( nodeListMemory.getLength() == 0 )
			{ throw new XMLAttributeNotFoundException( ExceptionMessages.XMLAttributeNotFoundExceptionMessage(superTag, attribute), superTag, attribute); }
			
			elementMemory = (Element) nodeListMemory.item(0);
		    String extractedAttribute = getCharacterDataFromElement(elementMemory);
		    
	    	if ( isLegalAttribute( extractedAttribute ) )
	    	{
	    		return extractedAttribute;
	    	}
	    	else
	    	{
	    		throw new XMLNotAttributeException( ExceptionMessages.XMLNotAttributeExceptionMessage(superTag, attribute, extractedAttribute), superTag, attribute ,extractedAttribute );
	    	}
		}
		
		private String extractOperator( Element element, String attribute, String superTag ) throws XMLNotLegalValueException, XMLAttributeNotFoundException // attribute and lnie is sent to reuse the memory space.
		{
			nodeListMemory = element.getElementsByTagName(attribute);
			if ( nodeListMemory.getLength() == 0 )
			{ throw new XMLAttributeNotFoundException( ExceptionMessages.XMLAttributeNotFoundExceptionMessage(superTag, attribute), superTag, attribute); }
			
			elementMemory = (Element) nodeListMemory.item(0);
		    String extracted = getCharacterDataFromElement(elementMemory);
		    
	    	if ( isLegalOperator( extracted ) )
	    	{
	    		return extracted;
	    	}
	    	else
	    	{
	    		throw new XMLNotLegalValueException( ExceptionMessages.XMLNotLegalOperatorExceptionMessage(superTag, attribute, extracted),superTag, attribute ,extracted );
	    	}
		}
		
		private int extractInteger( Element element, String attribute, String superTag ) throws XMLNotLegalValueException, XMLAttributeNotFoundException // attribute and lnie is sent to reuse the memory space.
		{
			nodeListMemory = element.getElementsByTagName(attribute);
			if ( nodeListMemory.getLength() == 0 )
			{ throw new XMLAttributeNotFoundException( ExceptionMessages.XMLAttributeNotFoundExceptionMessage(superTag, attribute), superTag, attribute); }
			
			elementMemory = (Element) nodeListMemory.item(0);
		    String extracted = getCharacterDataFromElement(elementMemory);
		    
	    	if ( isLegalInteger( extracted ) )
	    	{
	    		return Integer.parseInt(extracted);
	    	}
	    	else
	    	{
	    		throw new XMLNotLegalValueException( ExceptionMessages.XMLNotLegalIntegerExceptionMessage(superTag, attribute, extracted), superTag, attribute ,extracted );
	    	}
		}
		
		private String extractMatchesValue( Element element, String attribute, String superTag ) throws XMLNotLegalValueException, XMLAttributeNotFoundException // attribute and lnie is sent to reuse the memory space.
		{
			nodeListMemory = element.getElementsByTagName(attribute);
			if ( nodeListMemory.getLength() == 0 )
			{ throw new XMLAttributeNotFoundException( ExceptionMessages.XMLAttributeNotFoundExceptionMessage(superTag, attribute), superTag, attribute); }
			
			elementMemory = (Element) nodeListMemory.item(0);
		    String extracted = getCharacterDataFromElement(elementMemory);
		    
	    	if ( isLegalMatchedValue( extracted ) )
	    	{
	    		return extracted;
	    	}
	    	else
	    	{
	    		throw new XMLNotLegalValueException( ExceptionMessages.XMLNotLegalMatchesValueExceptionMessage(superTag, attribute, extracted), superTag, attribute ,extracted );
	    	}
		}
		
		private String extractOptionalASC_DESC( Element element, String attribute, String superTag ) throws XMLNotLegalValueException // attribute and lnie is sent to reuse the memory space.
		{
			nodeListMemory = element.getElementsByTagName(attribute);
			if ( nodeListMemory.getLength() == 0 )
			{
				return "DESC";
			}
			elementMemory = (Element) nodeListMemory.item(0);
		    String extracted = getCharacterDataFromElement(elementMemory);
		    
	    	if ( isLegalASC_DESC( extracted ) )
	    	{
	    		return extracted;
	    	}
	    	else
	    	{
	    		throw new XMLNotLegalValueException(  ExceptionMessages.XMLNotLegalASC_DESCExceptionMessage(superTag, attribute, extracted), superTag, attribute ,extracted );
	    	}
		}
		
		
		private boolean isLegalASC_DESC( String ASC_DESC )
		{
			return ( (ASC_DESC.equals("ASC")) || (ASC_DESC.equals("DESC")) );
		}
		
		private boolean isLegalAttribute( String attribute )
		{
			return ParserConstants.allowedAttribute(attribute);
		}
		
		private boolean isLegalOperator( String operator )
		{
			return ParserConstants.allowedOperators( operator );
		}
		
		private boolean isLegalInteger( String integer )
		{
			try
			{
				Integer.parseInt( integer );
			}
			catch (NumberFormatException e)
			{
				return false;
			}
			return true;
		}
		
		private boolean isLegalMatchedValue( String match )
		{
			return ParserConstants.allowedMatchByFilter(match);
		}
	}
	
			
	/*
	 * Transfers the data from the XML-file to the request-object.
	 * 
	 * @author Olle Hassel
	 * @param The XML-file whose data is to be transferred.
	 */
	public void parseXML() throws XMLParseException, SAXParseException, IOException, ParserConfigurationException, SAXException
	{
		try {
				DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
			    Document doc = builder.parse(XMLrequest);
			    
			    NodeList root;
			    
			    AttributeParser attributeParser = new AttributeParser();
    
			    Element element = null;	    
			    String currentTag;
			    

		    	currentTag = "match_by";	// read <match_by> tag
			    root = doc.getElementsByTagName( currentTag );
			    for (int i = 0; i < root.getLength(); i++) 
			    {
			    	element = (Element) root.item(i);
			    		
			    	addMatchByTag( 
			    			attributeParser.extractAttribute( element, "attribute", currentTag ),
			    			attributeParser.extractOperator( element, "operator", currentTag),
			    			attributeParser.extractMatchesValue( element, "value", currentTag) );

			    }
			    
			    currentTag = "order_by";	// read <order_by> tag
			    root = doc.getElementsByTagName( currentTag );
			    if (root.getLength()==0)  {throw new XMLTagNotFoundException( ExceptionMessages.XMLTagNotFoundExceptionMessage(currentTag), currentTag );}
			    
			    element = (Element) root.item(0);

			    setSortAttribute( attributeParser.extractAttribute( element, "attribute", currentTag ) );
			    setSortDirection( attributeParser.extractOptionalASC_DESC( element, "direction", currentTag ) );
			  
			    
			    currentTag = "answer_format"; // read <answer_format> tag
			    root = doc.getElementsByTagName( currentTag );
			    if (root.getLength()==0)  {throw new XMLTagNotFoundException( ExceptionMessages.XMLTagNotFoundExceptionMessage(currentTag), currentTag );}
			    
			    element = (Element) root.item(0);

			    setOffset( attributeParser.extractInteger( element, "offset", currentTag ) );
			    setNumberOfObjects( attributeParser.extractInteger( element, "number_of_objects", currentTag ) );
			    
			    
			    currentTag = "pad_reference_object"; // read <pad_reference_object> tag
			    root = doc.getElementsByTagName(currentTag);
			    if (root.getLength()==0)  {throw new XMLTagNotFoundException( ExceptionMessages.XMLTagNotFoundExceptionMessage(currentTag), currentTag );}

			    element = (Element) root.item(0);
			       
			       Iterator<String> iter = ParserConstants.attributesIterator();
			       
			       String attributeTag;
			       
					while ( iter.hasNext() )
					{
						attributeTag = iter.next();
						if (attributeParser.existsAttribute(element, attributeTag))
					    {
					     addPADAttribute( attributeTag );
					    }
					    
					}  
					if (ReferenceObject.isEmpty())
					{
						throw new XMLParseException( ExceptionMessages.XMLParseNoPADAttributesFoundExceptionMessage(currentTag), currentTag);
					}
   
			}
			catch (XMLParseException e)
			{
				throw e;
			}
			catch (SAXParseException e)
			{
				throw e;
			}
			catch (IOException e)
			{
				throw e;
			}
			catch (ParserConfigurationException e)
			{
				throw e;
			}
			catch (SAXException e)
			{
				throw e;
			}

	}
		

	private void addMatchByTag( String attribute, String operator, String matchesValue )
	{
		MatchByStack.add( new MatchBy_Object( attribute, operator, matchesValue) );
	}		
		
	private void setSortAttribute( String attribute )
	{
		this.OrderBy = attribute;
	}
	
	private void setSortDirection( String direction)
	{
		OrderByAscDesc = direction;
	}
	
	private void setOffset( int offset )
	{
		this.Offset = offset;
	}
	
	private void setNumberOfObjects( int numberOfObjects)
	{
		this.NumberOfObjects = numberOfObjects;
	}
	
	public int getNumberOfObjects()
	{
		return NumberOfObjects;
	}
	
	public int getOffset()
	{
		return Offset;
	}
	
	private void addPADAttribute( String attribute )
	{
		ReferenceObject.push( attribute );
	}
		
	private static String getCharacterDataFromElement(Element e) 
	{
		Node child = e.getFirstChild();
		if (child instanceof CharacterData) 
		{
			CharacterData cd = (CharacterData) child;
			return cd.getData();
		}
		return "?";
	}
	
	
	/*
	 * Converts the request-object data into an SQL statement.
	 * IllegalArgumentException
	 * @author Olle Hassel
	 * @return String SQL statement
	 */
	//public String 
	

	/*
	 * Converts the request-object data into an SQL statement.
	 * IllegalArgumentException
	 * @author Olle Hassel
	 * @return String SQL statement
	 */
	public String toSQL( boolean listCounter )
	{
		StringBuilder sb = new StringBuilder();
		sb.append("SELECT");
		sb.append(" ");
		
		if ( listCounter ) // used when calculating the total number of posts, even those that isn't collected.
		{
			sb.append("count(app_id)");
		}
		else
		{
			Iterator<String> PADiter = ReferenceObject.iterator();
			
			sb.append(PADiter.next());
			
			while ( PADiter.hasNext() )
			{
				sb.append(", ");
				sb.append(PADiter.next());
			}
		}

		
		sb.append(" ");
		sb.append("FROM");
		sb.append(" ");
		
		sb.append( ParserConstants.getPadTableName() );
		
		Iterator<MatchBy_Object> matchIter = MatchByStack.iterator();
		MatchBy_Object tmp;
		
		if ( !MatchByStack.isEmpty() )
		{
			
			sb.append(" ");
			sb.append("WHERE");
			sb.append(" ");
			
			while ( matchIter.hasNext() )
			{
				tmp = matchIter.next();
								
				sb.append(tmp.getAttribute()+" "+tmp.getOperator()+" '"+tmp.getValue()+"'");
				
				if ( matchIter.hasNext() )
				{
					sb.append(" AND ");
				}
				
			}
			
		}
		
		sb.append(" ");
		sb.append("ORDER BY");
		sb.append(" ");
		sb.append(OrderBy);
		sb.append(" ");
		if ( OrderByAscDesc != null )
		{
			sb.append(OrderByAscDesc);
		}
		else
		{
			sb.append("DESC");
		}
		
		sb.append(" ");
		sb.append("LIMIT");
		sb.append(" ");
		sb.append(NumberOfObjects);
		sb.append(" ");
		sb.append("OFFSET");
		sb.append(" ");
		sb.append(Offset);
		
		sb.append(";");
		
		return sb.toString();
	}
	
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		
		
		
		Iterator<MatchBy_Object> matchIter = MatchByStack.iterator();
		MatchBy_Object tmp;
		if ( !MatchByStack.isEmpty() )
		{
			
			while ( matchIter.hasNext() )
			{
				tmp = matchIter.next();
								
				sb.append("-match by");
				sb.append("\n");
				sb.append("   attribute: " + tmp.getAttribute() );
				sb.append("\n");
				sb.append("   operator: " + tmp.getOperator() );
				sb.append("\n");
				sb.append("   direction: " + tmp.getValue() );
				sb.append("\n");
			}
			
		}

		sb.append("-order by");
		sb.append("\n");
		sb.append("   attribute: " + OrderBy );
		sb.append("\n");
		sb.append("   direction: " + OrderByAscDesc );
		sb.append("\n");
		
		sb.append("-answer_format");
		sb.append("\n");
		sb.append("   offset: " + Offset );
		sb.append("\n");
		sb.append("   number_of_objects: " + NumberOfObjects );
		sb.append("\n");
		
		sb.append("-pad_reference_object");
		sb.append("\n");
		
		Iterator<String> PADiter = ReferenceObject.iterator();
		
		while ( PADiter.hasNext() )
		{
			sb.append("   "+PADiter.next());
			sb.append("\n");
		}
		
		return sb.toString();
	}
	
}
