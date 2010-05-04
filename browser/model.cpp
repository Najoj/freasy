#include "model.h"


model::model (ConnectionListener * con_listener, DownloadListener * dl_listener) :
	connection (con_listener)
{
	downloader = new ImageDownloader ();
	downloader->addDownloadListener  (dl_listener);

	parser = new XMLParser (& this->count, & this->offset, & this->applications [0], & this->done_parsing, & this->buffer);
}

model::~ model () {
	connection.close ();
}


/*********************************************************************
 * GET FUNCTIONS
 *********************************************************************/

application * model::get_applications () {
	return applications;
}

application * model::get_info (const char * app_name) {
	for (int i = 0; i < count; i ++) {
		if (strcmp (applications [i].name, app_name) == 0)
			return & applications [i];
	}
	return NULL;
}


/*********************************************************************
 * SET FUNCTIONS
 *********************************************************************/

int model::add_comment (String * app_name, String * comment) {
	return -1;
}

int model::add_grade (String * app_name, int grade) {
	return -1;
}

int model::add_runtime_statistics (String * app_name, bool success) {
	return -1;
}


/*********************************************************************
 * UTILITY FUNCTIONS
 *********************************************************************/

bool model::parse () {
	parser->process 	 ();
	return parser->parse ();

	/*
	for (int i = 0; i < count; i ++) {
		printf (" ******** APPLICATION %d ********** \n", i);
		printf ("name : %s\n", applications [i].name);
		printf ("id : %d\n", applications [i].id);
		printf ("author : %s %s\n", applications [i].author_first_name, applications [i].author_last_name);
		printf ("description : %s\n", applications [i].description);
		printf ("category : %s\n", applications [i].category);
		printf ("primary_dl_url : %s\n", applications [i].primary_dl_url);
	}
	*/

}


int model::connect () {
	//int result = connection.connect ("socket://home.ohassel.se:8989");
	int result = connection.connect ("socket://83.176.229.151:8989");
	if (result < 0) printf ("connecting failed\n");

	return result;
}


int model::close () {
	connection.close ();
	return 0;
}


int model::send_request (String request) {
	//String req = String ("        <request><order_by><attribute>app_name</attribute><direction>DESC</direction></order_by><answer_format><offset>0</offset><number_of_objects>10</number_of_objects></answer_format><pad_reference_object><app_id/><app_name/><description/><category/><primary_download_url/></pad_reference_object></request>");
	connection.write (request.c_str (), request.length());
	return 0;
}

int model::receive_answer () {
	connection.recv (buffer, BUFFERSIZE - parser->remaining_data - 1);
	return 0;
}

int model::search_by_category (char * category) {
	//String req = String ("        <request><order_by><attribute>app_name</attribute><direction>DESC</direction></order_by><answer_format><offset>0</offset><number_of_objects>10</number_of_objects></answer_format><pad_reference_object><app_id/><app_name/><description/><category/><primary_download_url/></pad_reference_object></request>");
	String request = String ("<request><match_by><attribute>category</attribute><operator>ILIKE</operator><value>%");
	request += category;
	request += "%</value></match_by><order_by><attribute>app_name</attribute></order_by>";
	request += "<answer_format><offset>0</offset><number_of_objects>10</number_of_objects></answer_format><pad_reference_object><app_id/><app_name/><description/><category/><primary_download_url/></pad_reference_object></request>";

	send_request (request);
	return 0;
}

int model::search_by_name (char * name) {
	String request = String ("<request><match_by><attribute>app_name</attribute><operator>ILIKE</operator><value>%");
	request += name;
	request += "%</value></match_by><order_by><attribute>app_name</attribute></order_by>";
	request += "<answer_format><offset>0</offset><number_of_objects>10</number_of_objects></answer_format><pad_reference_object><app_id/><app_name/><description/><category/><primary_download_url/></pad_reference_object></request>";

	send_request (request);

	return 0;
}




