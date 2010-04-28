#include "model.h"


model::model (ConnectionListener * con_listener, DownloadListener * dl_listener) :
	connection (con_listener)
{
	downloader = new ImageDownloader ();
	downloader->addDownloadListener (dl_listener);
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

void model::parse () {
	parser.process (buffer);
	count = parser.parse (buffer);
	applications = parser.get_applications ();

//	for (int i = 0; i < count; i ++) {
//		printf (" ******** APPLICATION %d ********** \n", i);
//		printf ("name : %s\n", applications [i].name);
//		printf ("id : %d\n", applications [i].id);
//		printf ("author : %s %s\n", applications [i].author_first_name, applications [i].author_last_name);
//		printf ("description : %s\n", applications [i].description);
//		printf ("category : %s\n", applications [i].category);
//		printf ("primary_dl_url : %s\n", applications [i].primary_dl_url);
//	}
}


int model::connect () {
	//int result = connection.connect ("socket://home.ohassel.se:8989");
	int result = connection.connect ("socket://83.176.229.151:8989");
	if (result < 0) printf ("connecting failed\n");

	return result;
}


int model::send_request () {
	String req = String ("        <request><order_by><attribute>app_name</attribute><direction>DESC</direction></order_by><answer_format><offset>0</offset><number_of_objects>5</number_of_objects></answer_format><pad_reference_object><app_id/><app_name/><description/><category/><primary_download_url/></pad_reference_object></request>");
	connection.write (req.c_str (), req.length());
	return 0;
}

int model::receive_answer () {
	connection.recv (buffer, 1024);
	return 0;
}
