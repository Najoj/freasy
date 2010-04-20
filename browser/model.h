/*
 * model.h
 *
 *  Created on: 1 apr 2010
 *      Author: Ximon
 */
#include <MAUtil/String.h>
#include <ma.h>
#include <MAUtil/PlaceholderPool.h>
#include <conprint.h>
#include <MTXml/MTXml.h>

#ifndef MODEL_H_
#define MODEL_H_

using namespace MAUtil;
using namespace Mtx;

/*****************************************************************************
 * APPLICATION STRUCT
 * used as a container of information about an application
 *****************************************************************************/
struct application {
	char  * name; 			  /* name of application  					 */
	char  * author; 		  /* author of application 					 */
	char  * icon_file_path;   /* file path to icon of the app 		 	 */
	char  * screen_file_path; /* file path to screenshot of the app 	 */
	char ** comments; 		  /* list of comments for the application    */
	int     grade; 			  /* application's average grade among users */
	int 	id; 			  /* unique id of application 				 */
};

/*****************************************************************************
 * XML PARSER CLASS
 * used for parsing xml data
 * extends XmlListener and MtxListener
 *****************************************************************************/
class XMLParser : public XmlListener, MtxListener {

	public :
		XMLParser   () ;
		~ XMLParser () ;

		int  process (char * data) ;
		bool feed    (char * data) ;
		void stop  	 ();

	private :
		/**************************************************
		 * XmlListener functions
		 **************************************************/
		void mtxEncoding  	(const char * value) ;
		void mtxTagStart  	(const char * name, int len) ;
		void mtxTagAttr   	(const char * attribute_name, const char * attribute_value) ;
		void mtxTagStartEnd () ;
		void mtxTagData 	(const char * data, int len) ;
		void mtxTagEnd 		(const char * name, int len) ;
		void mtxParseError 	() ;
		void mtxEmptyTagEnd () ;
		unsigned char mtxUnicodeCharacter (int unicode) ;

		/**************************************************
		 * MtxListener functions
		 **************************************************/
		void mtxDataRemains (const char * data, int len) ;

		Context context;
};

/*****************************************************************************
 * MODEL CLASS
 * main class taking care of interaction with server
 * providing information about applications to other classes
 * extends ConnectionListener
 *****************************************************************************/
class model {

	public :
		model   ();
		~ model ();

		XMLParser parser;

		/**************************************************
		 * GET FUNCTIONS
		 **************************************************/
		application ** get_applications (String * filter);
		String *  get_icon 		  (String * app_name);
		String *  get_description (String * app_name);
		String *  get_screenshot  (String * app_name);
		String *  get_author 	  (String * app_name);
		String ** get_comments    (String * app_name);
		int       get_grade		  (String * app_name);

		/**************************************************
		 * SET FUNCTIONS
		 **************************************************/
		int add_comment (String * app_name, String * comment);
		int add_grade   (String * app_name, int grade);
		int add_runtime_statistics (String * app_name, bool success);

		/**************************************************
		 * UTILITY FUNCTIONS
		 **************************************************/
		application * download_app (String * app_name);

	private :
		/**************************************************
		 * UTILITY FUNCTIONS
		 **************************************************/
		int send_request   ();
		int receive_answer ();

};

#endif /* MODEL_H_ */
