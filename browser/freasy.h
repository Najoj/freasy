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
#include "browserView.h"
#include "applicationEditView.h"
#include "applicationInfoView.h"



/*
 * CLASS DEFINITIONS
 */
class Freasy : public Moblet {
public:
	Freasy ();
	~Freasy();

	/*
	 * HUMAN INTERFACE
	 */
	void handleKeyPressed		(int keyCode);
	void handleKeyReleased		(int keyCode);
	void handlePointerPressed	(MAPoint2d keyCode);
	void handlePointerReleased	(MAPoint2d keyCode);
	void handlePointerMoved		(MAPoint2d keyCode);


private :

	browserView * view;

	/*
	 * DATA
	 */
	FILE *settings;
	FILE *favorites;
	//model dataModel;
	const char* settings_file_name;
	const char* favorites_file_name;
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
