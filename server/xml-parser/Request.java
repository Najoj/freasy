

import javax.xml.parsers.*;
import org.w3c.dom.*;
import java.util.Iterator;
import java.util.Stack;

import java.io.File;


public class Request // implements InterfaceRequest 
{
	
	File XMLrequest;
	
	
	// select -> match by. The list will be filtered according to the following attribute.
	private String SoughtAttribute; // Can be null.
	
	// The filter will use the following operator to compare the attribute with the value. Possible choices are: =, <>, >, >=, <, <=, LIKE, Between. See SQL for defenition.
	private String SoughtOperator; // Can be null.
	
	// select -> match by. The sought attribute is matched against this value.
	private String SoughtValue; // Can be n enull.
	
	private boolean matching;

	// order by. The list will be sorted according to the following attribute.
	private String OrderBy; 
	// order by. Defines wherver the objects are to be ordered ascending or descending to the chosen attribute. Must be one, cannot be both.
	private String OrderByAscDesc; // Defaulted to descending.

	// answer format. The offset of where in the list to begin collecting objects to return.
	private int Offset;
	// answer format. Maximum number of objects returned.
	private int NumberOfObjects;
             
    // Define a "reference PAD object", the answer will include the following attributes.
	//private PAD ReferenceObject;
	private Stack<String> ReferenceObject;
        
        
        
	public Request( File XMLrequest )
	{
		this.XMLrequest = XMLrequest;
		//SoughtAttribute = null;
		//SoughtOperator = null;
		//SoughtValue = null;
		//OrderByAscDesc = null;
		
		ReferenceObject = new Stack<String>();
		
		importXML();
		
		matching = false;		
		if ( ( SoughtAttribute != null ) && ( SoughtValue != null ) )
		{
			matching = true;
		}
	}
		
	
	/*
	 * Transfers the data from the XML-file to the request-object.
	 * 
	 * @author Olle Hassel
	 * @param The XML-file whose data is to be transferred.
	 */
	private void importXML() throws IllegalArgumentException
	{
		try {
				DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
			    Document doc = builder.parse(XMLrequest);
			    
  
			    NodeList root;
			    Element line = null;
			    NodeList attribute = null;
			    Element element = null;
			
			    
			    root = doc.getElementsByTagName("match_by");
			    for (int i = 0; i < root.getLength(); i++) 
			    {
			       element = (Element) root.item(i);
			      
			       setSoughtAttribute( extractAttribute( element, "attribute", attribute, line ) );
			       setSoughtOperator( extractAttribute( element, "operator", attribute, line ) );
			       setSoughtValue( extractAttribute( element, "value", attribute, line ) );
			     }
			    
			    root = doc.getElementsByTagName("order_by");
			    for (int i = 0; i < root.getLength(); i++) 
			    {
			       element = (Element) root.item(i);
			       
			       setSortAttribute( extractAttribute( element, "attribute", attribute, line ) );
			       setSortDirection( extractOptionalAttribute( element, "direction", attribute, line ) );
			     }
			    
			    if ( OrderByAscDesc == null ) { OrderByAscDesc = "DESC"; }
			    
			    root = doc.getElementsByTagName("answer_format");
			    for (int i = 0; i < root.getLength(); i++) 
			    {
			       element = (Element) root.item(i);
			       
			       setOffset( Integer.parseInt( extractAttribute( element, "offset", attribute, line ) ) );
			       setNumberOfObjects( Integer.parseInt( extractAttribute( element, "number_of_objects", attribute, line ) ) );
			     }
			    
			    root = doc.getElementsByTagName("pad_reference_object");
			    for (int i = 0; i < root.getLength(); i++) 
			    {
			       element = (Element) root.item(i);
			       
			       Iterator<String> iter = ParserConstants.attributesIterator();
			       String attributeTag;
			       
					while ( iter.hasNext() )
					{
						attributeTag = iter.next();
					    if ( existsAttribute( element, attributeTag, attribute ) )
					    {
					     addPADAttribute( attributeTag );
					    }
					}  
			       
			    }
			    
			    
			   }
			catch (Exception e) 
			{
				 e.printStackTrace();
			}
	}
	
	private boolean existsAttribute( Element element, String tag, NodeList attribute) // attribute and lnie is sent to reuse the memory space.
	{
		attribute = element.getElementsByTagName(tag);
		if ( attribute.getLength() != 0 )
		{
			return true;
		}
		else
		{
			// Kasta exception!
			return false;
		}
	}
	
	private String extractAttribute( Element element, String tag, NodeList attribute, Element line ) // attribute and lnie is sent to reuse the memory space.
	{
		attribute = element.getElementsByTagName(tag);
		line = (Element) attribute.item(0);
	    return getCharacterDataFromElement(line);
	}
	
	private String extractOptionalAttribute( Element element, String tag, NodeList attribute, Element line ) // attribute and lnie is sent to reuse the memory space.
	{
		attribute = element.getElementsByTagName(tag);
		if ( attribute.getLength() == 0 )
		{
			return null;
		}
		else
		{
			line = (Element) attribute.item(0);
		    return getCharacterDataFromElement(line);
		}
	}
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		
		if ( matching )
		{
			sb.append("-match by");
			sb.append("\n");
			sb.append("   attribute: " + SoughtAttribute );
			sb.append("\n");
			sb.append("   operator: " + SoughtOperator );
			sb.append("\n");
			sb.append("   direction: " + SoughtValue );
			sb.append("\n");
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
		
		sb.append("-PAD_reference_object");
		sb.append("\n");
		
		Iterator<String> iter = ReferenceObject.iterator();
		
		while ( iter.hasNext() )
		{
			sb.append("   "+iter.next());
			sb.append("\n");
		}
		
		return sb.toString();
	}
	
	private void setSoughtAttribute( String attribute )
	{
		this.SoughtAttribute = attribute;
	}
	
	private void setSoughtOperator( String operator )
	{
		this.SoughtOperator = operator;
	}
	
	private void setSoughtValue( String value )
	{
		this.SoughtValue = value; 
	}
	
	private void setSortAttribute( String attribute )
	{
		this.OrderBy = attribute;
	}
	
	private void setSortDirection( String direction)
	{
		assert ( ( direction == "ASC") || ( direction == "DESC") ); // throws exception
		
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
	public String toSQL()
	{
		StringBuilder sb = new StringBuilder();
		sb.append("SELECT");
		sb.append(" ");
		
		//Iterator<Attribute> iter = ReferenceObject.containsAttributes();
		Iterator<String> iter = ReferenceObject.iterator();
		//Attribute tmpA;
		
		sb.append(iter.next());
		
		while ( iter.hasNext() )
		{
			//tmpA = iter.next();
			//sb.append( tmpA.getName() );
			sb.append(", ");
			sb.append(iter.next());
		}
		
		sb.append(" ");
		sb.append("FROM");
		sb.append(" ");
		
		sb.append( ParserConstants.getPadTableName() );
		
		if ( matching )
		{
			sb.append(" ");
			sb.append("WHERE");
			sb.append(" ");
			sb.append(SoughtAttribute+" "+SoughtOperator+" \""+SoughtValue+"\"");
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
		
		return sb.toString();
	}
	
	
	
}
