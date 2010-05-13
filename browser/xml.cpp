#include "model.h"

XMLParser::XMLParser (int * count, 				   int * offset,
		              application ** applications, bool * done,
		              char ** buffer)
{
	context.init (this, this);

	this->offset 	   	 = offset;
	this->count  	     = count;
	this->applications   = applications;
	this->done			 = done;
	* done 				 = false;
	remaining_data		 = 0;

	this->buffer_pointer   = buffer;
	* this->buffer_pointer = this->buffer;

	this->length = 0;
	memset (data, 0, 30);
	//this->data   = NULL;


}

XMLParser::~ XMLParser () {
	this->~XmlListener ();
	this->~MtxListener ();
}

int XMLParser::process () {
	return context.process (buffer);
}

void XMLParser::stop () {
	context.stop ();
}

bool XMLParser::parse () {
	* done = false;
	//printf ("buffer : %s\n", buffer);
	return context.feed (buffer);
}


/**************************************************
 * XmlListener functions
 **************************************************/
void XMLParser::mtxEncoding (const char * value) {

}

void XMLParser::mtxTagStart (const char * name, int len) {
	//printf ("current tag : %s\n", current_tag);
	if (strcmp (name, "exception") == 0) { printf ("exception in answer!\n"); stop (); }
}

void XMLParser::mtxTagAttr (const char * attribute_name, const char * attribute_value) {
	if (strcmp (attribute_name, "element") == 0) {
		index = atoi (attribute_value);
		//printf ("current application %d\n", index);
	}
}

void XMLParser::mtxTagStartEnd () {

}

void XMLParser::mtxTagData (const char * tag_data, int length) {
	/* ignore whitespace */
	if (strcmp (tag_data, "\n") == 0 || strcmp (tag_data, " ") == 0) return;

	//printf ("tag_data %s, length : %d\n", tag_data, length);

	/* if no data from previous parse alloc new data array */
	if (this->length == 0) {
//		data = (char *) malloc (30);
//		memset (data, 0, 30),
		memcpy (data, tag_data, length + 1);
		//data = (char *) memcpy (new char [length + 1], tag_data, length + 1);
		//data = (char *) memcpy (malloc (length + 1), tag_data, length + 1);
		this->length = length;
	}
	/* else append to previous data */
	else {
		memcpy (data + this->length, tag_data, length + 1);
		this->length += length;
	}

	//printf ("data : %s\n", data);
}

void XMLParser::mtxTagEnd (const char * name, int tag_length) {

	length ++;

	//printf ("%s\n", data);

	if (strcmp (name, "answer") == 0) {
		* done 		   = true; /* parser is now done */

		/******* Reset the Parser ******/
		remaining_data = 0;
		memset (buffer, 0, BUFFERSIZE); /* reset our buffer by freeing it from old memory */
		* buffer_pointer = buffer; 		/* start writing at the start of our buffer */

		stop (); /* this is the last tag, stop so we dont process trailing characters */
	}

	if (strcmp (name, "number_of_objects") == 0)
		//printf ("data : %s\n", data);
		* count = atoi (data);

	else if (strcmp (name, "offset") == 0) {
		//printf ("data : %s\n", data);
		* offset = atoi (data);
	}

	else if (strcmp (name, "app_id") == 0) {
		//if (applications [index].id != NULL) free (& applications [index].id);
		(* applications) [index].id = atoi (data);
		//applications->id = atoi (data);
		//printf ("data : %s\n", data);
	}

	else if (strcmp (name, "app_name") == 0) {
		//if (applications [index].name != NULL) {/* printf ("freeing name %s\n", applications[index].name);*/ free (applications [index].name); }
		//(* applications) [index].name = (char *) memcpy (new char [length], data, length);
//		(* applications) [index].name = data;

		//Checks so that we dont overflow the memcpy, model.h for the define
		if (length < APPLICATION_MAX_STR_LEN){
			memcpy ((* applications) [index].name, data, length);
		}else{
			memcpy ((* applications) [index].name, data, APPLICATION_MAX_STR_LEN);
		}
	}

	else if (strcmp (name, "category") == 0) {
		//if (applications [index].category != NULL) free (applications [index].category);
		//applications [index].category = data;
		//applications->category = data;
		//printf ("data : %s\n", data);
		//(* applications) [index].category = (char *) memcpy (new char [length], data, length);
		//(* applications) [index].category = data;

		//Checks so that we dont overflow the memcpy, model.h for the define
		if (length < APPLICATION_MAX_STR_LEN){
			memcpy ((* applications) [index].category,  data, length);
		}else{
			memcpy ((* applications) [index].category,  data, APPLICATION_MAX_STR_LEN);
		}
	}

	else if (strcmp (name, "author_first_name") == 0) {
		//if (applications [index].author_first_name != NULL) free (applications [index].author_first_name);
		//applications [index].author_first_name = data;
		//applications->author_first_name = data;
		//printf ("data : %s\n", data);
		//(* applications) [index].author_first_name = (char *) memcpy (new char [length], data, length);
		//(* applications) [index].author_first_name = data;

		//Checks so that we dont overflow the memcpy, model.h for the define
		if (length < APPLICATION_MAX_STR_LEN){
			memcpy ((* applications) [index].author_first_name,  data, length);
		}else{
			memcpy ((* applications) [index].author_first_name, data, APPLICATION_MAX_STR_LEN);
		}

	}

	else if (strcmp (name, "author_last_name") == 0) {
		//if (applications [index].author_last_name != NULL) free (applications [index].author_last_name);
		//applications [index].author_last_name = data;
		//applications->author_last_name = data;
		//printf ("data : %s\n", data);
		//(* applications) [index].author_last_name = (char *) memcpy (new char [length], data, length);
		//(* applications) [index].author_last_name = data;

		//Checks so that we dont overflow the memcpy, model.h for the define
		if (length < APPLICATION_MAX_STR_LEN){
			memcpy ((* applications) [index].author_last_name, data, length);
		}else{
			memcpy ((* applications) [index].author_last_name, data, APPLICATION_MAX_STR_LEN);
		}
	}

	else if (strcmp (name, "short_description") == 0) {
		//if (applications [index].description != NULL) free (applications [index].description);
		//applications [index].description = data;
		//applications->description = data;
		//printf ("data : %s\n", data);
		//printf ("%s\n",(* applications) [index].description);
		//(* applications) [index].description = (char *) memcpy (new char [length], data, length);
		//(* applications) [index].description = data;

		//Checks so that we dont overflow the memcpy, model.h for the define
		if (length < APPLICATION_DESC_LEN){
				memcpy ((* applications) [index].description, data, length);
			}else{
				memcpy ((* applications) [index].description, data, APPLICATION_MAX_STR_LEN);
			}

	}

	else if (strcmp (name, "primary_download_url") == 0) {
		//if (applications [index].primary_dl_url != NULL) free (applications [index].primary_dl_url);
		//applications [index].primary_dl_url = data;
		//applications->primary_dl_url = data;
		//printf ("data : %s\n", data);
		//(* applications) [index].primary_dl_url = (char *) memcpy (new char [length], data, length);
		//(* applications) [index].primary_dl_url = data;

		//Checks so that we dont overflow the memcpy, model.h for the define
		if (length < APPLICATION_MAX_STR_LEN){
				memcpy ((* applications) [index].primary_dl_url, data, length);
			}else{
				memcpy ((* applications) [index].primary_dl_url, data, APPLICATION_MAX_STR_LEN);
			}

	}

	else if (strcmp (name, "secondary_download_url") == 0) {
		//if (applications [index].secondary_dl_url != NULL) free (applications [index].secondary_dl_url);
		//applications [index].secondary_dl_url = data;
		//applications->secondary_dl_url = data;
		//printf ("data : %s\n", data);
		//(* applications) [index].secondary_dl_url = (char *) memcpy (new char [length], data, length);
		//(* applications) [index].secondary_dl_url = data;
		if (length < APPLICATION_MAX_STR_LEN){
				memcpy ((* applications) [index].secondary_dl_url, data, length);
			}else{
				memcpy ((* applications) [index].secondary_dl_url, data, APPLICATION_MAX_STR_LEN);
			}

	}

	else if (strcmp (name, "icon") == 0) {
		if      (strcmp (data, "f") == 0) (* applications) [index].icon = false;
		else if (strcmp (data, "t") == 0) (* applications) [index].icon = true;
	}

	memset (data, 0, 100);
	length = 0;


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



















