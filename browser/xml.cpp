#include "model.h"

XMLParser::XMLParser () {
	context.init (this, this);
	offset = 0;
}

XMLParser::~ XMLParser () {

}

int XMLParser::process (char * data) {
	return context.process (data);
}

bool XMLParser::feed (char * data) {
	return context.feed (data);
}

void XMLParser::stop () {
	context.stop ();
}

int XMLParser::parse (char * data) {
	printf ("data\n%s\n", data);
	printf ("\n\n\n\n");
	feed (data);
	return count;
}

application * XMLParser::get_applications () {
	return applications;
}


/**************************************************
 * XmlListener functions
 **************************************************/
void XMLParser::mtxEncoding (const char * value) {

}

void XMLParser::mtxTagStart (const char * name, int len) {
	current_tag = name;
	//printf ("current tag : %s\n", current_tag);
	if (strcmp (name, "exception") == 0) stop ();
}

void XMLParser::mtxTagAttr (const char * attribute_name, const char * attribute_value) {
	if (strcmp (attribute_name, "element") == 0)
		current_application = atoi (attribute_value);
}

void XMLParser::mtxTagStartEnd () {

}

void XMLParser::mtxTagData (const char * data, int len) {

	if (strcmp (data,"\n") == 0 || strcmp (data, " ") == 0) return;

	if (strcmp (current_tag, "number_of_objects") == 0)
		//printf ("data : %s\n", data);
		count = atoi (data);

	else if (strcmp (current_tag, "offset") == 0) {
		//printf ("data : %s\n", data);
		offset = atoi (data);
	}

	else if (strcmp (current_tag, "app_id") == 0) {
		applications [current_application].id = atoi (data);
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "app_name") == 0) {
		applications [current_application].name = data;
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "category") == 0) {
		applications [current_application].category = data;
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "author_first_name") == 0) {
		applications [current_application].author_first_name = data;
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "author_last_name") == 0) {
		applications [current_application].author_last_name = data;
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "description") == 0) {
		applications [current_application].description = data;
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "primary_download_url") == 0) {
		applications [current_application].primary_dl_url = data;
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "secondary_download_url") == 0) {
		applications [current_application].secondary_dl_url = data;
		//printf ("data : %s\n", data);
	}
}

void XMLParser::mtxTagEnd (const char * name, int len) {

}

void XMLParser::mtxParseError () {
	printf ("*** ERROOOOR PARSING ***\n");
}

void XMLParser::mtxEmptyTagEnd () {
	//printf ("empty tag end\n");
}

unsigned char XMLParser::mtxUnicodeCharacter (int unicode) {
	printf ("LOL?\n");
}

/**************************************************
 * MtxListener functions
 **************************************************/
void XMLParser::mtxDataRemains (const char * data, int len) {
	printf ("data remaining : \n%s\n", data);
}



















