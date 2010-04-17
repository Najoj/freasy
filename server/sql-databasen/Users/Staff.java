package Users;
import java.sql.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;

import SQL.*;

public class Staff {
	private Connection db;
	private boolean stop;
	private static Scanner keyboard = new Scanner(System.in);
	
	private static final int SUBYEAR = 0;
	private static final int SUBMONTH = 1;
	private static final int SUBDAY = 0;
	
	private static final int RETYEAR = 0;
	private static final int RETMONTH = 2;
	private static final int RETDAY = 0;
	
	private static final double discount = 0.17;
	
	public Staff(Connection db) {
		this.db = db;
		this.stop = false;
		
		while(!stop) {
			switch(printMenu()) {
			case 1:
				sell();
				break;
			case 2:
				rent();
				break;
			case 3:
				returnMovie();
				break;
			case 4:
				sellMembership();
				break;
			case 0:
				exit();
				break;
			}
		}
	}
	
	private void sell() {
		double price = 0.0;
		int productID = askForProductID();
		int copiesLeft = Integer.parseInt(getFieldNr(3, productID, "Sale"));
		if(copiesLeft > 0) {
			int pnr = askForCustomerID();
			if(!isCustomer(pnr)) {
				addCustomer(pnr);
			}
			price = Integer.parseInt(getFieldNr(2, productID, "Sale"));
			if(isMember(pnr)) {
				price *= (1-discount);
			}
			changeCopiesLeft(productID, copiesLeft-1, true);
			System.out.println("Movie sold for " + price);

			SQLInsert query = new SQLInsert("Buys", db);
			query.addValue("" + pnr);
			query.addValue("" + productID);
			query.addValue("'" + getFieldNr(1, productID, "Sale") + "'");
			query.addValue("'" + getDate() + "'");
			SQL.SendQuery(query);
			
		} else
			System.out.println("No more copies left !");
	}
	
	public int askForProductID() {
		System.out.print("Enter the product ID : ");
		return keyboard.nextInt();
	}
	
	public String getFieldNr(int field, int productID, String table) {
		SQLSelect query = new SQLSelect(table, db);
		query.addWhereClause("ID = " + productID);
		ArrayList<String> rs = SQL.SendQuery(query);
		return rs.get(field);
	}
	
	public void changeCopiesLeft(int productID, int newValue, boolean sale) {
		SQLUpdate query = null;
		if(sale) {
			query = new SQLUpdate("Sale", db);
			query.addValue("scopies=" + newValue);
		} else {
			query = new SQLUpdate("Rent", db);
			query.addValue("rcopies=" + newValue);
		}
		query.addWhereClause("ID=" + productID);
		SQL.SendQuery(query);
	}
		
	private void rent() {
		double price = 0.0;
		int productID = askForProductID();
		int copiesLeft = Integer.parseInt(getFieldNr(3, productID, "Rent"));
		if(copiesLeft > 0) {
			int pnr = askForCustomerID();
			if(!isCustomer(pnr)) {
				addCustomer(pnr);
			}
			price = Integer.parseInt(getFieldNr(2, productID, "Rent"));
			if(isMember(pnr)) {
				price *= (1-discount);
			}
			changeCopiesLeft(productID, copiesLeft-1, false);
			System.out.println("Movie rented for " + price);

			SQLInsert query = new SQLInsert("Rents", db);
			query.addValue(pnr + "");
			query.addValue(productID + "");
			query.addValue("'" + getFieldNr(1, productID, "Rent") + "'");
			query.addValue("'" + getDate() + "'");
			int year = Calendar.getInstance().get(Calendar.YEAR) + RETYEAR;
			int month = Calendar.getInstance().get(Calendar.MONTH) + RETMONTH;
			int day = Calendar.getInstance().get(Calendar.DAY_OF_MONTH) + RETDAY;
			String date = "" + year + "-" + month + "-" + day;  
			query.addValue("'" + date + "'");
			SQL.SendQuery(query);
			
		} else
			System.out.println("No more copies left !");
	}
	
	private void returnMovie() {
		int productID = askForProductID();
		int copiesLeft = Integer.parseInt(getFieldNr(3, productID, "Rent"));
		changeCopiesLeft(productID, copiesLeft+1, false);
	}
	
	private void sellMembership() {
		// Ask for customer ID
		int pnr = askForCustomerID();
		
		// Check if customer is already a customer
		if(!isCustomer(pnr)) {
			System.out.println("Customer not found! Creating an entry for this customer");
			addCustomer(pnr);
			int year = Calendar.getInstance().get(Calendar.YEAR) + SUBYEAR;
			int month = Calendar.getInstance().get(Calendar.MONTH) + SUBMONTH;
			int day = Calendar.getInstance().get(Calendar.DAY_OF_MONTH) + SUBDAY;
			String date = "" + year + "-" + month + "-" + day;  
			SQLInsert query = new SQLInsert("membership", db);
			query.addValue("" + pnr);
			query.addValue("'" + date + "'");
			
			SQL.SendQuery(query);
		} else {
			// TODO update the membership exp. date
		}
	}
	
	private void addCustomer(int pnr) {
		SQLInsert query = new SQLInsert("customer", db);
		System.out.print("Name: ");
			String name = keyboard.next();
		System.out.print("Phone: ");
			String phone = keyboard.next();
			query.addValue("" + pnr);
		query.addValue("'" + name + "'");
		query.addValue("'" + phone + "'");
		
		SQL.SendQuery(query);
	}
	
	private void exit() {
		System.out.println("Good bye");
		stop = true;
	}
				
	private int printMenu() {
		int answer = -1;
		do {
			System.out.println("Welcome, staff, choose an option");
			System.out.println("--------------------------------");
			System.out.println("1. Sell a movie");
			System.out.println("2. Rent a movie");
			System.out.println("3. Return a movie");
			System.out.println("4. Sell a membership");
			System.out.println();
			System.out.println("0. Exit");
			answer = keyboard.nextInt();
		} while(answer < 0 || answer > 4);
		return answer;
	}
	
	private int askForCustomerID() {
		System.out.println("Enter the customer ID: ");
		return keyboard.nextInt();
	}
	
	private boolean isCustomer(int pnr) {
		SQLSelect query = new SQLSelect("customer", db);
		query.addWhereClause("pnr=" + pnr);
		
		ArrayList<String> result = SQL.SendQuery(query);
		return !result.isEmpty();
	}
	
	private boolean isMember(int pnr) {
		SQLSelect query = new SQLSelect("membership", db);
		query.addWhereClause("pnr=" + pnr);
		
		ArrayList<String> result = SQL.SendQuery(query);
		return !result.isEmpty();
	}
	
	private String getDate() {
		return Calendar.getInstance().get(Calendar.YEAR) + "-" + Calendar.getInstance().get(Calendar.MONTH) + "-" + Calendar.getInstance().get(Calendar.DAY_OF_MONTH);
	}
}