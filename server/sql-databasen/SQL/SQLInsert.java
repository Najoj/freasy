package SQL;

import java.sql.Connection;

public class SQLInsert extends SQLQuery {
	
	private String values;
	
	public SQLInsert(String tab, Connection db) {
		super(tab, db);
		this.values="";
	}
	
	public void addValue(String value) {
		this.values = this.values + value + "," ;
	}
	
	public String toString() {
			return "INSERT INTO " + super.table + " VALUES (" + values.substring(0, values.length()-1) + ")" + super.toString() ;
	}
}