package Users;

import java.sql.Connection;
import java.util.Scanner;

import SQL.*;

public class Customer {

	private static Scanner keyboard = new Scanner(System.in);
	
	private String table;
	private Connection db;
	private boolean stop;
	
	public Customer(String tab, Connection db) {
		this.table = tab;
		this.db = db;
		this.stop = false;
		
		while(!stop) {
			switch(printMenu()) {
			case 1: 
				search();
				break;
			case 0: 
				exit();
				break;
			}
		}
	}
	
	public int printMenu() {
		System.out.println("Choose an option");
		System.out.println("------------------------------");
		System.out.println("1. Search for a movie");
		System.out.println();
		System.out.println("0. Exit");
		return keyboard.nextInt();
	}
	
	public void search() {
		SQLSelect query = new SQLSelect(table, db);
		System.out.println("Search by title? (y/n)");
		char answer = keyboard.next().charAt(0);
		
		if(answer == 'y' || answer == 'Y' ) {
			System.out.println("What title do you want?");
			String title = keyboard.next();
			query.addWhereClause("title=" + title);
		} else if(answer == 'n'  || answer == 'N') {
			System.out.println("Search by category? (y/n)");
			answer = keyboard.next().charAt(0);
			if(answer == 'y' || answer == 'Y') {
				System.out.println("Enter the desired category");
				String category = keyboard.next();
				query.addWhereClause("category=" + category);
			}
		}
		SQL.SendQuery(query);
	}
	
	public void exit() {
		System.out.println("Good bye");
		stop = true;
	}
}
