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

			Answer answer = new Answer(PADSQL.SendQuery(request.toSQL(),
					request.getNumberOfObjects()), request.getOffset(), PADSQL
					.getQueryListLength(request.getSQLLength()));

			// Answer answer = new Answer();

			answerString = answer.exportXML();

			LogFiles.getRequestLog().appendToLog(new Date() + " - Korrekt forumlerad request. Inga fel.");

			// System.out.println("Answer: "+ answer.toString() );
			System.out.println("Korrekt formulerad request.");

		} catch (XMLParseException e) {
			ExceptionParser error = new ExceptionParser();
			answerString = error.parseException(e);

			LogFiles.getRequestLog().appendToLog(new Date() + " - Requesten har genrererat ett XMLParseException.");
			System.err.println("Requesten har genrererat ett XMLParseException.");

		} catch (SAXParseException e) {
			ExceptionParser error = new ExceptionParser();
			answerString = error.parseException(e);

			LogFiles.getRequestLog().appendToLog(new Date() + " - Requesten har genrererat ett SAXParseException.");
			
			System.err.println("Requesten har genrererat ett SAXParseException.");
		} catch (SQLException e) {

			answerString = new ExceptionParser()
					.parseMessageToXML("Fel innuti servern!");

			LogFiles.getRequestLog().appendToLog(new Date() + " - Requesten har genererat ett SQLException.");

			System.err.println("Requesten har genererat ett SQLException.");
			System.err.println("Exception: " + e.getMessage());
			e.printStackTrace();
		} catch (Exception e) {
			// Major error, probably bug in the server code.

			// Spara undan requesten, kolla varför felet inträffade!

			LogFiles.getRequestLog().appendToLog(new Date() + " !!- Requesten har genrererat ett ofångat fel, vad har dom gjort?!? -!!");
		}
		/**
		 * CLASSIC JAKE HAX!!!
		 */
		if (answerString == null) {
			answerString = "JAKEHAX!";
		}

		files.setAnswer(answerString);

	}
}
