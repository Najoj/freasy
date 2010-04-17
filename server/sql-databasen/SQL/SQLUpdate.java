package SQL;

import java.sql.Connection;

public class SQLUpdate extends SQLQuery {
	
	private String values;
	
	public SQLUpdate(String tab, Connection db) {
		super(tab, db);
		this.values="";
	}
	
	public void addValue(String value) {
		this.values = this.values + value + "," ;
	}
	
	public String toString() {
			return "UPDATE " + super.table + " SET " + values.substring(0, values.length()-1) + super.toString();
	}
}