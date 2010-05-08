

package Database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Properties;

	public class PADSQL
	{
		
		private static Connection db;
		
	    //public void main (String[] args) throws Exception 
		public static void Initialize() 
	    {
			try {
				Class.forName ("org.postgresql.Driver");
			} catch (Exception e) {
				System.out.println("Class org.postgresql.Driver not found");
				System.exit(0);
			}
	        Properties settings = new Properties ();
	        settings.setProperty("user","guest");
	        settings.setProperty("password","freasy");
	        String url = "jdbc:postgresql://home.ohassel.se/freasy";
	        //String url = "jdbc:postgresql://localhost/freasy";
	        try {
	        	db = DriverManager.getConnection (url, settings);
	        } catch (Exception e) {
	        	System.out.println("Unable to connect to database server");
	        	System.exit(0);
	        }

	    }
		
		public static int getQueryListLength( String query ) throws SQLException
		{

			ResultSet rs = db.createStatement().executeQuery(query);

			
			//System.out.println("Test: "+ rs.getMetaData().getColumnCount());
			//return rs.getInt(1);
			//System.out.println(rs.next());
			//System.out.println(rs.getInt(1));
			
			rs.next();
			return rs.getInt(1);
			
		}
	    
	    public static ArrayList<HashMap<String,String>> SendQuery( String query, int expectedLength ) throws SQLException
	    {

	    	
	    	//try 
	    	//{
	    		
	    			//System.out.println("Skickar följande SQL-sats:  "+query);

	    			ResultSet rs = db.createStatement().executeQuery(query);

					int numberOfAttributes = rs.getMetaData().getColumnCount();
					ArrayList<HashMap<String,String>> PAD_table = new ArrayList<HashMap<String,String>>(expectedLength);
						
					int index = 0;

					while ( rs.next() ) 
					{
						HashMap<String,String> currentPAD = new HashMap<String,String>();
						
						PAD_table.add(index, currentPAD);
												
						for (int m = 1; m <= numberOfAttributes; m++)
						{
							currentPAD.put( rs.getMetaData().getColumnName(m), rs.getString(m) );
						}
						index++;
					}
					
					PAD_table.trimToSize();

					return PAD_table;
		
	    	//} 
					/*
	    	catch(SQLException e) 
	    	{
	    		System.err.println("error!");
	    		System.err.println("Exception: "+e.getMessage());
	    		e.printStackTrace();
	    		return null;
	    	}
	    	*/
	    	/*catch( Exception e)
	    	{
	    		System.err.println("Något är allvarligt fel!");
	    		System.err.println("Exception: "+e.getMessage());
	    		e.printStackTrace();
	    		return null;
	    	}*/
	}
	}
	
