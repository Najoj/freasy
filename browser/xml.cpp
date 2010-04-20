#include "model.h"

XMLParser::XMLParser () {
	context.init (this, this);
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

}

/**************************************************
 * XmlListener functions
 **************************************************/
void XMLParser::mtxEncoding (const char * value) {

}

void XMLParser::mtxTagStart (const char * name, int len) {
	printf ("tag start : <%s>\n", name);
}

void XMLParser::mtxTagAttr (const char * attribute_name, const char * attribute_value) {
	printf ("tag attribute : %s = %s\n", attribute_name, attribute_value);
}

void XMLParser::mtxTagStartEnd () {
	//printf ("tag start end\n");
}

void XMLParser::mtxTagData (const char * data, int len) {
	printf ("tag data : %s\n", data);
}

void XMLParser::mtxTagEnd (const char * name, int len) {
	printf ("tag end : <%s />\n", name);
}

void XMLParser::mtxParseError () {
	printf ("*** ERROOOOR PARSING ***\n");
}

void XMLParser::mtxEmptyTagEnd () {
	printf ("empty tag end\n");
}

unsigned char XMLParser::mtxUnicodeCharacter (int unicode) {

}

/**************************************************
 * MtxListener functions
 **************************************************/
void XMLParser::mtxDataRemains (const char * data, int len) {
	printf ("data remaining : \n%s\n", data);
}



















