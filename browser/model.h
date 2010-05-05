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
struct application {
	char  * name; 			 	 /* name of application  					*/
	char  * author_first_name; 	 /* author of application (first name)	  	*/
	char  * author_last_name;  	 /* author of application (last name)       */
	char  * description;       	 /* description of the application			*/
	char  * category; 		 	 /* application category					*/
	char  * primary_dl_url; 	 /* primary download URL					*/
	char  * secondary_dl_url;	 /* secondary download URL					*/
	//const char ** comments; 	 /* list of comments for the application    */
	//int     	  grade; 		 /* application's average grade among users */
	int 		  id; 			 /* unique id of application 				*/
};


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
		Context 	  context;
		char 	      buffer [BUFFERSIZE];
		char 	   ** buffer_pointer;
		application ** applications;
		const char  * current_tag;
		int 		  current_application;
		int 	    * count;
		int 		* offset;
		bool 		* done;

};


/*****************************************************************************
 * RESOURCE DOWNLOADER CLASS
 * Classed used for downloading different resources
 * such as icons, screenshots, etc.. for different applications
 * extends ImageDownloader, DownloadListener
 *****************************************************************************
class resource_downloader : public DownloadListener {

	public :
		resource_downloader   ();
		~ resource_downloader ();

		MAHandle * download_resource (const char * url) ;

	private :
		/****************************************************************
		 * DownloadListener functions
		 ****************************************************************
		void notifyProgress		 (Downloader * downloader, int downloaded_bytes, int total_bytes) ;
		bool outOfMemory		 (Downloader * downloader) ;
		void finishedDownloading (Downloader * downloader, MAHandle data) ;
		void downloadCancelled	 (Downloader * downloader) ;
		void error 				 (Downloader * downloader, int error_code) ;

		/****************************************************************
		 * Variables
		 ****************************************************************
		ImageDownloader downloader;
		MAHandle   		data;

};
*/

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
		int close ();
		bool parse 				() ;
		int  send_request   	(String request) ;
		int  receive_answer 	() ;
		int  search_by_category (char * category) ;
		int  search_by_name     (char * name) ;

		int	 count; 			 /* number of apps */
		bool done_parsing;

	private :
		/**************************************************
		 * VARIABLES
		 **************************************************/
		XMLParser	  	* parser;
		Connection 	  	  connection;
		ImageDownloader * downloader;
		int 			  offset;
		application     * applications;
		char 		    * buffer;

		/* home.ohassel.se:8989 */
};

#endif /* MODEL_H_ */
