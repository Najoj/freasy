#include "model.h"

model::model () {

}

model::~ model () {

}

/*********************************************************************
 * GET FUNCTIONS
 *********************************************************************/

application ** model::get_applications (String * filter) {
	return NULL;
}

String * model::get_icon (String * app_name) {
	return NULL;
}

String * model::get_description (String * app_name) {
	return NULL;
}

String * model::get_screenshot (String * app_name) {
	return NULL;
}

String * model::get_author (String * app_name) {
	return NULL;
}

String ** model::get_comments (String * app_name) {
	return NULL;
}

int model::get_grade (String * app_name) {
	return -1;
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

application * model::download_app (String * app_name) {

}

extern "C" int MAMain () {
	model model;
	model.parser.feed (
			"<?xml version=\"1.0\" encoding=\"utf-8\"?><test><name>yarr</name><description>we are testing to parse!</description></test>");
	return 0;
}
