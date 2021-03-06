/*
 * freasy.h
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#ifndef FREASY_H_
#define FREASY_H_

#include <MAFS/File.h>
#include <MAUtil/Environment.h>
#include <MAUtil/Moblet.h>

#include "model.h"
#include "viewInterface.h"


/*
 * CLASS DEFINITIONS
 */
class Freasy : public Moblet, public ConnectionListener, public DownloadListener {
public:
	Freasy ();
	~Freasy();

	/*
	 * HUMAN INTERFACE
	 */
	void handle_key_down  	 ();
	void handle_key_right 	 ();
	void handle_key_left  	 ();
	void handle_key_up    	 ();
	void handle_key_softleft ();
	void handle_key_softright();


private :

	/****************************************************************
	 * ConnectionListener functions
	 ****************************************************************/
	void connectFinished   (Connection * connection, int result) ;
	void connRecvFinished  (Connection * connection, int result) ;
	void connWriteFinished (Connection * connection, int result) ;
	void connReadFinished  (Connection * connection, int result) ;

	/****************************************************************
	 * DownloadListener functions
	 ****************************************************************/
	void notifyProgress		 (Downloader * downloader, int downloaded_bytes, int total_bytes) ;
	bool outOfMemory		 (Downloader * downloader) ;
	void finishedDownloading (Downloader * downloader, MAHandle data) ;
	void downloadCancelled	 (Downloader * downloader) ;
	void error 				 (Downloader * downloader, int error_code) ;

	ViewContainer * views;

	/*
	 * DATA
	 */
	//FILE *settings;
	//FILE *favorites;
	model * dataModel;
	FILE  * app2download_file;
	//const char* settings_file_name;
	//const char* favorites_file_name;
	//Screen *currentScreen; //The active screen, named View in the ADD 1.2

	/*
	 * SETTERS
	 */
	void setView			(Screen view);
	int saveSettings		(char* filePath);
	int saveFavorites		(char* filePath);
	int saveBrowserState	();

	/*
	 * GETTERS
	 */
	int loadSettings	(char* filePath);
	int loadFavorites	(char* filePath);

	int current_view;
	int viewed_app;
};



/**
 * INPUTCONTROLLERX CLASS
 * new input controller for handling input from user
 * extends : KeyListener, PointerListener
 */
class InputControllerX : public KeyListener, public PointerListener {

	public:

        InputControllerX   (Freasy * freasy);
		~ InputControllerX ();

	private :

		/**************************************************************
		 * KeyListener Functions
		 **************************************************************/
		void keyPressEvent   (int keyCode, int nativeCode);
		void keyReleaseEvent (int keyCode, int nativeCode);

		/**************************************************************
		 * PointerListener Functions
		 **************************************************************/
		void pointerPressEvent   (MAPoint2d point) ;
		void pointerMoveEvent    (MAPoint2d point) ;
		void pointerReleaseEvent (MAPoint2d point) ;

		Freasy * freasy;

};





#endif /* FREASY_H_ */
