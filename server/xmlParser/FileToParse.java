package xmlParser;

import java.sql.SQLException;
import java.util.Date;

import Static.LogFiles;

import org.xml.sax.SAXParseException;

import Database.PADSQL;
import Files.RequestAnswer;

/**
 * @author olle
 * 
 */
public class FileToParse {

	/*
	 * Inputs a File and recieves a File that answers according to the input.
	 * 
	 * @author Olle Hassel
	 * 
	 * @param an XML-file instanced as a File object
	 * 
	 * @return an XML-file answer to the request, or an exception-xml file if
	 * unable to parse
	 */
	public void parseFile(RequestAnswer files) {
		// File XMLrequest = files.getRequest();
		// File XMLanswer = files.getAnswer();
		String req = files.getRequest();

		// FilePrinter.printFileToTerminal(XMLrequest);
		Request request = new Request(req);

		String answerString = null;

		try {

			request.parseXML();

			// System.out.println("Request: "+ request.toString());

			System.out.println("Försöker öppna databaskopplingen");
			PADSQL database = new PADSQL();
			database.Initialize();
			
			Answer answer = new Answer(database.SendQuery(request.toSQL(),
					request.getNumberOfObjects()), request.getOffset(), database
					.getQueryListLength(request.getSQLLength()));
			
			System.out.println("Korrekta svar från databasen");
			
			database.Close();
			System.out.println("Databaskopplingen korrekt stängd");

			// Answer answer = new Answer();

			answerString = answer.exportXML();

			LogFiles.getRequestLog().appendToLog(new Date() + " - Korrekt forumlerad request. Inga fel.");

			// System.out.println("Answer: "+ answer.toString() );
			System.out.println("Korrekt formulerad request.");

		} catch (XMLParseException e) {
			ExceptionParser error = new ExceptionParser();
			answerString = error.parseException(e);

			LogFiles.getRequestLog().appendToLog(new Date() + " - Requesten har genrererat ett XMLParseException.");
			
			appendExceptionLog( files );
			
			System.err.println("Requesten har genrererat ett XMLParseException.");

		} catch (SAXParseException e) {
			ExceptionParser error = new ExceptionParser();
			answerString = error.parseException(e);

			LogFiles.getRequestLog().appendToLog(new Date() + " - Requesten har genrererat ett SAXParseException.");
			
			appendExceptionLog( files );
			
			System.err.println("Requesten har genrererat ett SAXParseException.");
		} catch (SQLException e) {

			answerString = new ExceptionParser()
					.parseMessageToXML("Fel innuti servern!");

			LogFiles.getRequestLog().appendToLog(new Date() + " - Requesten har genererat ett SQLException.");

			appendExceptionLog( files );
			
			System.err.println("Requesten har genererat ett SQLException.");
			System.err.println("Exception: " + e.getMessage());
			e.printStackTrace();
		} catch (Exception e) {
			// Major error, probably bug in the server code.

			// Spara undan requesten, kolla varför felet inträffade!

			LogFiles.getRequestLog().appendToLog(new Date() + " !!- Requesten har genrererat ett ofångat fel, vad har dom gjort?!? -!!");
			
			appendExceptionLog( files );
			
		}
		/**
		 * CLASSIC JAKE HAX!!!
		 */
		if (answerString == null) {
			answerString = "JAKEHAX!";
		}

		files.setAnswer(answerString);

	}
	
	private void appendExceptionLog( RequestAnswer files )
	{
		LogFiles.getExceptionLog().appendToLog(new Date() + " - Requesten har genererat ett Exception."+"\n\n"+
				files.getRequest()+"\n\n"+files.getAnswer()+"\n\n"+"\n\n"+"\n\n");
	}
}
