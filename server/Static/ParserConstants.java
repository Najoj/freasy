
package Static;

import java.util.HashSet;
import java.util.Iterator;


public class ParserConstants 
{
	
	final static String LINE_BREAK = "<![CDATA[<br/>]]>";

	private static HashSet<String> AllowedAttributes;
	private static HashSet<String> AllowedOperators;

	final private static String PAD_TABLE_NAME = "PAD";
	
	public static void Initialize()
	{
		
		AllowedAttributes = new HashSet<String>();
		AllowedOperators = new HashSet<String>();
		
	
		AllowedAttributes.add("app_name");  // the name of the application.
		AllowedAttributes.add("app_id");  // a unique identifier for this specific application.
		AllowedAttributes.add("versions");  // version number of the application.
		AllowedAttributes.add("release_date");  // could either be date when it was added to	the server of first released.
		AllowedAttributes.add("size");  // the size of the actual application (the “binary” file).
		AllowedAttributes.add("category");  // specifies which category the application should be stored in.
		AllowedAttributes.add("short_description");  // a string giving a description of the application.
		AllowedAttributes.add("long_description");  // a string that contains an URL with more information about the application..
		AllowedAttributes.add("screenshot");  // a string specifying an URL that points to	where a screenshot of the application can be found.
		AllowedAttributes.add("icon");  // a string specifying an URL that points to where an icon representing the application can be found.
		AllowedAttributes.add("primary_download_url");  // URL that points towards the primary download location.
		AllowedAttributes.add("secondary_download_url");  // URL that points towards the secondary download location.
		AllowedAttributes.add("download_other_url1");  // URL that points towards the primary mirror download location.
		AllowedAttributes.add("download_other_url2");  // URL that points towards the secondary	mirror download location.
		AllowedAttributes.add("company_name");  // name of the company that made the application.
		AllowedAttributes.add("company_address");  // address of that company.
		AllowedAttributes.add("company_url");  // URL to the company’s website.
		AllowedAttributes.add("author_first_name");  // First name of the author.
		AllowedAttributes.add("author_last_name");  // Last name of the author.
		AllowedAttributes.add("author_email");  // Email-adress to the author.
		AllowedAttributes.add("application_hash");  // a calculated checksum of the actual application (i.e. the binary file).
		
		
		AllowedOperators.add("="); // The operators allowed in the match_by tag
		AllowedOperators.add("<>");
		AllowedOperators.add(">");
		AllowedOperators.add(">=");
		AllowedOperators.add("<");
		AllowedOperators.add("<=");
		AllowedOperators.add("ILIKE");

		
	}
	
	public static boolean isTextRegexOperator( String operator )
	{
		return operator.equals("ILIKE");
	}
	
	public static String getLineBreak()
	{
		return LINE_BREAK;
	}
	
	public static String listAllowedAttributes()
	{
		Iterator<String> iter = AllowedAttributes.iterator();
		
		StringBuilder sb = new StringBuilder();
		
		while (iter.hasNext())
		{
			sb.append( iter.next() );
			if (iter.hasNext())
			{
				sb.append(", ");
			}
		}
		return sb.toString();
	}
	
	public static String listAllowedOperators()
	{
		Iterator<String> iter = AllowedOperators.iterator();
		
		StringBuilder sb = new StringBuilder();
		
		while (iter.hasNext())
		{
			sb.append( iter.next() );
			if (iter.hasNext())
			{
				sb.append(", ");
			}
		}
		return sb.toString();
	}
	
	public static String listAllowedMatchByFilters()
	{
		return "";
	}
	
	public static String getPadTableName()
	{
		return PAD_TABLE_NAME;
	}
	
	public static Iterator<String> attributesIterator()
	{
		return AllowedAttributes.iterator();
	}
	
	public static boolean allowedOperators( String s )
	{
		return AllowedOperators.contains( s );
	}
	
	public static boolean allowedAttribute( String s )
	{
		return AllowedAttributes.contains( s );
	}
	
	public static boolean allowedMatchByFilter( String s )
	{
		return true; // TODO
	}
}


//private String appName = null;  // the name of the application.
//private Integer appId = null ;  // a unique identifier for this specific application.
	/*
	private String versions;  // version number of the application.
	private String relaseDate;  // could either be date when it was added to	the server of first released.
	private int size;  // the size of the actual application (the “binary” file).
	private String category;  // specifies which category the application should be stored in.
	private String description;  // a string giving a description of the application.
	private String applicationInfoUrl;  // a string that contains an URL with more information about the application..
	private String screenShotURL;  // a string specifying an URL that points to	where a screenshot of the application can be found.
	private String iconURL;  // a string specifying an URL that points to where an icon representing the application can be found.
	*/
//private String primaryDownloadURL = null;  // URL that points towards the primary download location.
	/*
	private String secondaryDownloadURL;  // URL that points towards the secondary download location.
	private String downloadOtherURL1;  // URL that points towards the primary mirror download location.
	private String downloadOtherURL2;  // URL that points towards the secondary	mirror download location.
	private String companyName;  // name of the company that made the application.
	private String companyAddress;  // address of that company.
	private String companyURL;  // URL to the company’s website.
	private String authorFirstName;  // First name of the author.
	private String authorLastName;  // Last name of the author.
	private String authorEmail;  // Email-adress to the author.
	private int applicationHash;  // a calculated checksum of the actual application (i.e. the binary file).
	*/
