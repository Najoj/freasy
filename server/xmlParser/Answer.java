
package xmlParser;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import java.io.StringWriter;

import org.w3c.dom.*;

import javax.xml.parsers.*;

import javax.xml.transform.*;
import javax.xml.transform.dom.*;
import javax.xml.transform.stream.*;



	/*
	 * Transfers the data from the XML-file to the request-object.
	 * 
	 * @author Olle Hassel
	 */
public class Answer 
{
	
	int NumberOfObjects;
	int Offset;
	int LastOffset;
	int ListLength;
	
	ArrayList<HashMap<String,String>> PAD_Array;
	
	/*
	 * Transfers the data from the XML-file to the request-object.
	 * 
	 * @author Olle Hassel
	 * @param The XML-file whose data is to be transferred.
	 */
	public Answer() // Vet än inte hur datastrukturen från databasen ser ut.
	{
		fillData();
	}
	
	public Answer( ArrayList<HashMap<String,String>> PAD_Array, int offset ) // Vet än inte hur datastrukturen från databasen ser ut.
	{
		this.PAD_Array = PAD_Array;
		this.Offset = offset;
		this.NumberOfObjects = PAD_Array.size();
		this.LastOffset = Offset + NumberOfObjects;
		this.ListLength = 4711;
	}
	
	private Node printElement( String attribute, String value, Document doc , Element element, Text text )
	{
        element = doc.createElement(attribute);
		text = doc.createTextNode(""+value);    
		element.appendChild(text);
		return element;
	}
	
	public String exportXML()
	{
		try {
            /////////////////////////////
            //Creating an empty XML Document

            //We need a Document
            DocumentBuilderFactory dbfac = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = dbfac.newDocumentBuilder();
            Document doc = docBuilder.newDocument();

            ////////////////////////
            //Creating the XML tree

            //create the root element and add it to the document
            Element root = doc.createElement("answer");
            doc.appendChild(root);

            Element element = null;
            Element attribute = null;
            Text text = null;
            
            root.appendChild( printElement( "number_of_objects", ""+NumberOfObjects, doc, element, text  ) );
            root.appendChild( printElement( "offset", ""+Offset, doc, element, text  ) );
            root.appendChild( printElement( "last_offset", ""+LastOffset, doc, element, text  ) );
            root.appendChild( printElement( "list_length", ""+ListLength, doc, element, text  ) );
            
    		Iterator<Map.Entry<String,String>> iter;
    		Map.Entry<String,String> tmp; 
    		
    		for (int i = 0; i < NumberOfObjects; i++)
    		{
    			// Add an PAD element
                element = doc.createElement("pad");
                element.setAttribute("element", ""+i);
                root.appendChild(element);
    			
    			iter = PAD_Array.get( i ).entrySet().iterator();
    			while ( iter.hasNext() )
    			{
    				tmp = iter.next();
    				element.appendChild( printElement( tmp.getKey(), tmp.getValue(), doc, attribute, text  ) );
    			}
    		}	

            /////////////////
            //Output the XML

            //set up a transformer
            TransformerFactory transfac = TransformerFactory.newInstance();
            Transformer trans = transfac.newTransformer();
            trans.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
            trans.setOutputProperty(OutputKeys.INDENT, "yes");

            //create string from xml tree
            StringWriter sw = new StringWriter();
            StreamResult result = new StreamResult(sw);
            DOMSource source = new DOMSource(doc);
            trans.transform(source, result);
            
            return sw.toString();
            
        } catch (Exception e) {
            System.out.println(e);
            return null;
        }
	}
	
	
	/*
	 * Fills the object with data, used when debugging.
	 * 
	 * @author Olle Hassel
	 */
	private void fillData()
	{
		NumberOfObjects = 3;
		Offset = 0;
		LastOffset = Offset+NumberOfObjects;
		ListLength = 4711;
		
		PAD_Array = new ArrayList<HashMap<String,String>>( NumberOfObjects );
		
		HashMap<String,String> tmp;
		
		tmp = new HashMap<String,String>();
		tmp.put("appId", "4711");
		tmp.put("appName", "Tetris");
		PAD_Array.add( 0, tmp );
		
		tmp = new HashMap<String,String>();
		tmp.put("appId", "17");
		tmp.put("appName", "Space Invaders");
		PAD_Array.add( 1, tmp );
		
		tmp = new HashMap<String,String>();
		tmp.put("appId", "666");
		tmp.put("appName", "Hello Kitty Offline");
		PAD_Array.add( 2, tmp );
		
	}
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		
		sb.append(NumberOfObjects+"\n");
		sb.append(Offset+"\n");
		sb.append(LastOffset+"\n");
		sb.append(ListLength+"\n");
		
		Iterator<Map.Entry<String,String>> iter;
		Map.Entry<String,String> tmp; 
		
		for (int i = 0; i < NumberOfObjects; i++)
		{
			sb.append("PAD element " +i +"\n" );
			iter = PAD_Array.get( i ).entrySet().iterator();
			while ( iter.hasNext() )
			{
				tmp = iter.next();
				sb.append( tmp.getKey() + " = " + tmp.getValue() +"\n" );
			}
		}	
		return sb.toString();
		
	}


}
