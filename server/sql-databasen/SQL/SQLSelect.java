package SQL;

import java.sql.Connection;

public class SQLSelect extends SQLQuery {
	
	public SQLSelect(String tab, Connection db) {
		super(tab, db);
	}
	
	public String toString() {
		return "SELECT * FROM " + super.table + super.toString();
	}
}
