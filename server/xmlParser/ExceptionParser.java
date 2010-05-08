
package xmlParser;

import java.io.StringWriter;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Text;
import org.xml.sax.SAXParseException;


public class ExceptionParser 
{

	public String parseException( XMLParseException e )
	{
		
		return parseMessageToXML( e.getMessage() );
	}
	
	public String parseException( SAXParseException e )
	{
		
		return parseMessageToXML( e.getMessage() );
	}

	public String parseMessageToXML( String sentMessage )
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
            Element root = doc.createElement("exception");
            doc.appendChild(root);


            Element element = doc.createElement( "message" );
            Text text = doc.createTextNode( sentMessage );    
    		element.appendChild(text);
    		
    		root.appendChild( element );
            
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
            
        } 
		catch (Exception e) 
		{
            System.out.println(e);
            return null;
        }
		
	}
	
}
