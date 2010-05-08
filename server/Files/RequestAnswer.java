package Files;


public class RequestAnswer {

	private String request;
	private String answer;

	public RequestAnswer(String fileName) {
		this.request = "";
		this.answer = "";
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

}
