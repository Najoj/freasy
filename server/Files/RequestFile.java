package Files;

import java.util.Date;

import Static.FilePrinter;

public class RequestFile {

	private String request;
	private String answer;

	private StringBuilder log;

	private boolean Save;

	public RequestFile(String request, String answer, String fileName) {
		this.request = request;
		this.answer = answer;
		Save = false;
		log = new StringBuilder();
		log.append(new Date().toString() + " : " + fileName + " : ");
	}

	public void appendToLog(String s) {
		log.append(s);
	}

	public void setSave(boolean save) {
		this.Save = save;
	}

	public String getRequest() {
		return request;
	}

	public void setRequest(String request) {
		this.request = request;
	}

	public String getAnswer() {
		return answer;
	}
	
	public void setAnswer(String answer) {
		this.answer = answer;
	}

	private void writeLogEntry() {
		FilePrinter.appendToFile(FilePrinter.getRequestLog(), log.toString());
	}

	public void delete() {
		/**
		 * writeLogEntry();
		 * 
		 * if (!Save) { Request.delete(); Answer.delete(); } else { appendToLog(
		 * Request.getName() + " - " + Answer.getName() );
		 * 
		 * Answer.delete(); }
		 **/
	}

}
