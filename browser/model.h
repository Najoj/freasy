/*
 * model.h
 *
 *  Created on: 1 apr 2010
 *      Author: Ximon
 */
#include <MAUtil/String.h>
#include <MAUtil/util.h>
#include <ma.h>
#include <MAUtil/PlaceholderPool.h>
#include <conprint.h>
#include <MTXml/MTXml.h>
#include <mastdlib.h>
#include <MAUtil/Connection.h>
#include <MAUtil/Downloader.h>
#include <maheap.h>

#ifndef MODEL_H_
#define MODEL_H_

#define BUFFERSIZE 1024

using namespace MAUtil;
using namespace Mtx;


/*****************************************************************************
 * APPLICATION STRUCT
 * used as a container of information about an application
 *****************************************************************************/
typedef struct application {
	bool icon;						/* tells if there's an icon available 		*/
	int  id;						/* unique id of application 				*/
	char name 				[100];	/* name of application  					*/
	char author_first_name 	[100];	/* author of application (first name)	  	*/
	char author_last_name 	[100];	/* author of application (last name)        */
	char description 		[500];	/* description of the application			*/ // used to be 100
	char primary_dl_url 	[100];  /* primary download URL						*/
	char secondary_dl_url 	[100];	/* secondary download URL					*/
	char category 			[100];	/* application category						*/

} application;


//typedef struct application {
//	char  * name; 			 	 /* name of application  					*/
//	char  * author_first_name; 	 /* author of application (first name)	  	*/
//	char  * author_last_name;  	 /* author of application (last name)       */
//	char  * description;       	 /* description of the application			*/
//	char  * category; 		 	 /* application category					*/
//	char  * primary_dl_url; 	 /* primary download URL					*/
//	char  * secondary_dl_url;	 /* secondary download URL					*/
//	int     id; 			 	 /* unique id of application 				*/
//	bool	icon;				 /* tells if there's an icon available 		*/
//} application;


/*****************************************************************************
 * XML PARSER CLASS
 * used for parsing xml data received from server
 * extends XmlListener and MtxListener
 *****************************************************************************/
class XMLParser : public XmlListener, public MtxListener {

	public :
		XMLParser   (int * count, int * offset, application ** applications, bool * done, char ** buffer) ;
		~ XMLParser () ;

		int  process () ;
		void stop  	 () ;
		bool parse   () ;

		int remaining_data;

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

		/**************************************************
		 * Variables
		 **************************************************/
		application ** applications;
		char 		   data [500];	//changed from 100,
		char 	    ** buffer_pointer;
		int 		   index;
		int 	     * count;
		int 		 * offset;
		int			   length;
		bool 		 * done;
		char 	       buffer [BUFFERSIZE];
		Context 	   context;

};


/*****************************************************************************
 * MODEL CLASS
 * main class taking care of interaction with server
 * providing information about applications to other classes
 *****************************************************************************/
class model {

	public :
		model   (ConnectionListener * con_listener, DownloadListener * dl_listener) ;
		~ model () ;

		/********************************************************************
		 * GET FUNCTIONS
		 ********************************************************************/
		application * get_applications () ;
		application * get_info		   (char * app_name) ;

		/********************************************************************
		 * SET FUNCTIONS
		 ********************************************************************/
		int add_comment (String * app_name, String * comment) ;
		int add_grade   (String * app_name, int grade) ;
		int add_runtime_statistics (String * app_name, bool success) ;

		/********************************************************************
		 * UTILITY FUNCTIONS
		 ********************************************************************/
		int  connect 			() ;
		int  close				() ;
		bool parse 				() ;
		int  send_request   	(String * request) ;
		int  receive_answer 	() ;
		int  search_by_category (char * category) ;
		int  search_by_name     (char * name) ;
		void download_icon		(int index) ;

		int	 	 count; 			 /* number of apps */
		bool 	 done_parsing;
		MAHandle icon;

	private :
		/**************************************************
		 * VARIABLES
		 **************************************************/
		char 		    * buffer;
		int 			  offset;
		XMLParser	  	* parser;
		ImageDownloader * downloader;
		application     * applications;
		Connection 	  	  connection;
		String			* request;

};

#endif /* MODEL_H_ */
