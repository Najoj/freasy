
import java.io.File;




public interface InterfaceRequest
{
	
	/*
	 * Transfers the data from the XML-file to the request-object.
	 * 
	 * @author Olle Hassel
	 * @param The XML-file whose data is to be transferred.
	 */
	public void importXML( File XMLrequest ) throws IllegalArgumentException;

	
	/*
	 * Converts the request-object data into an SQL statement.
	 * 
	 * @author Olle Hassel
	 * @return String SQL statement
	 */
	public String toSQL();
	
	
	

}
