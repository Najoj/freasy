package SQL;

import java.sql.*;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Scanner;

import Users.Customer;
import Users.Staff;

	public class SQL
	{
		
		private static Connection db;
		
	    public static void main (String[] args) throws Exception {
	        Class.forName ("org.postgresql.Driver");
	        Properties settings = new Properties ();
	        settings.setProperty ("user", System.getProperty ("user.name"));
	        String url = "jdbc:postgresql://localhost/pjanse";
	        db = DriverManager.getConnection (url, settings);

	        System.out.println("Are you a staff member ? (y/n)");
	        Scanner keyboard = new Scanner(System.in);
	        char answer = keyboard.next().charAt(0);
	        
	        boolean staff = (answer == 'y');
	        
	        if(staff)
	        	new Staff(db);
	        else
	        	new Customer("customerView", db);
	    }
	    
	    public static ArrayList<String> SendQuery( SQLQuery query ) {
	    	System.out.println("Sending query: " + query.toString());
	    	try {
	    		if((query instanceof SQLInsert) || query instanceof SQLUpdate) {
	    			db.createStatement().executeUpdate(query.toString());
	    			return null;
	    		} else if(query instanceof SQLSelect) {
	    			ResultSet rs = db.createStatement().executeQuery(query.toString());
					int nCols = rs.getMetaData().getColumnCount();
					ArrayList<String> result = new ArrayList<String>(0);
					while (rs.next ()) {
						for (int i = 1; i <= nCols; i++) {
							result.add(rs.getString(i));
							System.out.print(result.get(i-1) + ", ");
						}
						System.out.println();
					}
					return result;
	    		} else {
	    			System.out.println("CREE CETTE PUTAIN DE CLAUSE!!!");
					return null;
	    		}
	    	} catch(SQLException e) {
	    		System.err.println("Prout");
	    		e.printStackTrace();
	    		return null;
	    	}
	    }   
}

