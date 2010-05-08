#include "model.h"


model::model (ConnectionListener * con_listener, DownloadListener * dl_listener) :
	connection (con_listener)
{
	downloader = new ImageDownloader ();
	downloader->addDownloadListener  (dl_listener);

	parser = new XMLParser (& this->count, & this->offset, & this->applications, & this->done_parsing, & this->buffer);
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

application * model::get_info (char * app_name) {

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
}


int model::connect () {
	if (connection.isOpen ()) return -1; /* we're already connected!! */
	int result = connection.connect ("socket://home.ohassel.se:8989");
	//int result = connection.connect ("socket://130.237.81.39:8989");
	//int result = connection.connect ("socket://picturelogin.dyndns.org:8989");
	if (result < 0) printf ("connecting failed\n");

	return result;
}


int model::close () {
	connection.close ();
	return 0;
}


int model::send_request (String request) {
	if (applications != NULL) free (applications); /* free memory for new data */

	applications = new application [10]; /* make a fresh array ready for the data */
	connection.write (request.c_str (), request.length ());

	return 0;
}

int model::receive_answer () {
	connection.recv (buffer, BUFFERSIZE - parser->remaining_data - 1);
	return 0;
}

int model::search_by_category (char * category) {
	String request = String ("<request><match_by><attribute>category</attribute><operator>ILIKE</operator><value>%");
	request += category;
	request += "%</value></match_by><order_by><attribute>app_name</attribute></order_by>";
	request += "<answer_format><offset>0</offset><number_of_objects>10</number_of_objects></answer_format><pad_reference_object><app_id/><app_name/><short_description/><category/><primary_download_url/><author_first_name/><author_last_name/></pad_reference_object></request>";

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

void model::download_icon (int index) {
	String url = String (applications [index].primary_dl_url);
	url += "/icon/32/icon.png";
	downloader->beginDownloading (url.c_str (), icon);
}



