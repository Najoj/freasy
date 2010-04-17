package SQL;
import java.sql.Connection;
import java.util.Iterator;
import java.util.LinkedList;

public abstract class SQLQuery {
	protected LinkedList<String> conditions;
	protected String table;
	protected Connection db;

	public SQLQuery(String tab, Connection db) {
		this.db = db;
		this.table = tab;
		this.conditions = new LinkedList<String>();
	}
	
	public void addWhereClause(String condition) {
		conditions.add(condition);
	}
	
	public String toString() {
		String ret = "";
		if(!conditions.isEmpty()) {
			ret = " WHERE ";
			Iterator<String> iter = conditions.iterator();
			ret += iter.next();
			while(iter.hasNext()) {
				ret += " AND " + iter.next();
				conditions.remove();
			}
		}
		return ret + ";";
	}
}
