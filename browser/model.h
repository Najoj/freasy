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

#ifndef MODEL_H_
#define MODEL_H_

using namespace MAUtil;
using namespace Mtx;

/*****************************************************************************
 * APPLICATION STRUCT
 * used as a container of information about an application
 *****************************************************************************/
struct application {
	const char  * name; 			 /* name of application  					*/
	const char  * author_first_name; /* author of application (first name)	  	*/
	const char  * author_last_name;  /* author of application (last name)       */
	const char  * description;       /* description of the application			*/
	const char  * icon_file_path;    /* file path to icon of the app 		 	*/
	const char  * screen_file_path;  /* file path to screenshot of the app 	  	*/
	const char  * category; 		 /* application category					*/
	const char  * primary_dl_url; 	 /* primary download URL					*/
	const char  * secondary_dl_url;	 /* secondary download URL					*/
	const char ** comments; 		 /* list of comments for the application    */
	int     	  grade; 			 /* application's average grade among users */
	int 		  id; 			     /* unique id of application 				*/
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
		void stop  	 ();
		int parse    (char * data) ;
		application * get_applications ();

		int offset;

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
		bool feed (char * data) ;

		/**************************************************
		 * Variables
		 **************************************************/
		Context 	 context;
		char 	     buffer 	  [1024];
		application  applications [10];
		const char * current_tag;
		int 		 current_application;
		int 		 count;

};



/*****************************************************************************
 * RESOURCE DOWNLOADER CLASS
 * Classed used for downloading different resources
 * such as icons, screenshots, etc.. for different applications
 * extends ImageDownloader, DownloadListener
 *****************************************************************************/
class resource_downloader : public DownloadListener {

	public :
		resource_downloader   ();
		~ resource_downloader ();

		MAHandle * download_resource (const char * url) ;

	private :
		/**************************************************
		 * DownloadListener functions
		 **************************************************/
		void notifyProgress		 (Downloader * downloader, int downloaded_bytes, int total_bytes) ;
		bool outOfMemory		 (Downloader * downloader) ;
		void finishedDownloading (Downloader * downloader, MAHandle data) ;
		void downloadCancelled	 (Downloader * downloader) ;
		void error 				 (Downloader * downloader, int error_code) ;

		/***************************************************************
		 * Variables
		 ****************************************************************/
		ImageDownloader downloader;
		MAHandle   		data;

};




/*****************************************************************************
 * MODEL CLASS
 * main class taking care of interaction with server
 * providing information about applications to other classes
 * extends ConnectionListener
 *****************************************************************************/
//class model : public ConnectionListener {
class model {

	public :
		model   (ConnectionListener * con_listener, DownloadListener * dl_listener) ;
		~ model () ;

		/**************************************************
		 * GET FUNCTIONS
		 **************************************************/
		application * get_applications () ;
		application * get_info		   (const char * app_name) ;

		/**************************************************
		 * SET FUNCTIONS
		 **************************************************/
		int add_comment (String * app_name, String * comment) ;
		int add_grade   (String * app_name, int grade) ;
		int add_runtime_statistics (String * app_name, bool success) ;

		/**************************************************
		 * UTILITY FUNCTIONS
		 **************************************************/
		int	 count; 			 /* number of apps */
		int  connect 		() ;
		void parse 			() ;
		int  send_request   () ;
		int  receive_answer () ;

	private :
		/**************************************************
		 * VARIABLES
		 **************************************************/
		XMLParser	  		parser;
		Connection 	  		connection;
		ImageDownloader *	downloader;
		application     *	applications;
		char 		  		buffer [1024];


		/* home.ohassel.se:8989 */
};

#endif /* MODEL_H_ */
