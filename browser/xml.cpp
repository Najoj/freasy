#include "model.h"

XMLParser::XMLParser (int * count, int * offset, application * applications, bool * done, char ** buffer) {
	context.init (this, this);

	this->offset 	   	 = offset;
	this->count  	     = count;
	this->applications   = applications;
	this->done			 = done;
	* done 				 = false;
	remaining_data		 = 0;

	this->buffer_pointer   = buffer;
	* this->buffer_pointer = this->buffer;
}

XMLParser::~ XMLParser () {

}

int XMLParser::process () {
	return context.process (buffer);
}

bool XMLParser::feed (char * data) {
	//printf ("data : \n%s\n", data);
	return context.feed (data);
}

void XMLParser::stop () {
	context.stop ();
}

bool XMLParser::parse () {
	* done = false;
	return feed (buffer);
}


/**************************************************
 * XmlListener functions
 **************************************************/
void XMLParser::mtxEncoding (const char * value) {

}

void XMLParser::mtxTagStart (const char * name, int len) {
	current_tag = name;
	//printf ("current tag : %s\n", current_tag);
	if (strcmp (name, "exception") == 0) { printf ("exception in answer!\n"); stop (); }
}

void XMLParser::mtxTagAttr (const char * attribute_name, const char * attribute_value) {
	if (strcmp (attribute_name, "element") == 0) {
		current_application = atoi (attribute_value);
		//printf ("current application %d\n", current_application);
	}
}

void XMLParser::mtxTagStartEnd () {

}

void XMLParser::mtxTagData (const char * data, int length) {

	if (strcmp (data,"\n") == 0 || strcmp (data, " ") == 0) return;

	length ++; /* increment for a null terminated string */

	if (strcmp (current_tag, "number_of_objects") == 0)
		//printf ("data : %s\n", data);
		* count = atoi (data);

	else if (strcmp (current_tag, "offset") == 0) {
		//printf ("data : %s\n", data);
		* offset = atoi (data);
	}

	else if (strcmp (current_tag, "app_id") == 0) {
		applications [current_application].id = atoi (data);
		//applications->id = atoi (data);
		//printf ("data : %s\n", data);
	}

	else if (strcmp (current_tag, "app_name") == 0) {
		applications [current_application].name = (char *) memcpy (new char [length], data, length);
		//applications [current_application].name [length] = 0;
		//printf ("current application (%d) name : %s\n", current_application, data);
	}

	else if (strcmp (current_tag, "category") == 0) {
		//applications [current_application].category = data;
		//applications->category = data;
		//printf ("data : %s\n", data);
		applications [current_application].category = (char *) memcpy (new char [length], data, length);
	}

	else if (strcmp (current_tag, "author_first_name") == 0) {
		//applications [current_application].author_first_name = data;
		//applications->author_first_name = data;
		//printf ("data : %s\n", data);
		applications [current_application].author_first_name = (char *) memcpy (new char [length], data, length);
	}

	else if (strcmp (current_tag, "author_last_name") == 0) {
		//applications [current_application].author_last_name = data;
		//applications->author_last_name = data;
		//printf ("data : %s\n", data);
		applications [current_application].author_last_name = (char *) memcpy (new char [length], data, length);

	}

	else if (strcmp (current_tag, "description") == 0) {
		//applications [current_application].description = data;
		//applications->description = data;
		//printf ("data : %s\n", data);
		applications [current_application].description = (char *) memcpy (new char [length], data, length);
	}

	else if (strcmp (current_tag, "primary_download_url") == 0) {
		//applications [current_application].primary_dl_url = data;
		//applications->primary_dl_url = data;
		//printf ("data : %s\n", data);
		applications [current_application].primary_dl_url = (char *) memcpy (new char [length], data, length);
	}

	else if (strcmp (current_tag, "secondary_download_url") == 0) {
		//applications [current_application].secondary_dl_url = data;
		//applications->secondary_dl_url = data;
		//printf ("data : %s\n", data);
		applications [current_application].secondary_dl_url = (char *) memcpy (new char [length], data, length);
	}
}

void XMLParser::mtxTagEnd (const char * name, int len) {
	if (strcmp (name, "answer") == 0) {
		* done 		   = true;
		remaining_data = 0;
		stop (); /* this is the last tag, stop so we dont process trailing characters */
	}
}

void XMLParser::mtxParseError () {
	printf ("*** ERROOOOR PARSING ***\n");
	stop ();
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
	//printf ("data remaining : \n%s\n", data);

	memcpy (buffer, data, len);      /* copy remaining data 							  */
	* buffer_pointer = buffer + len; /* move writing pointer to the end of remaining data */

	remaining_data = len;
}



















