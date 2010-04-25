/*
 * freasy.h
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#ifndef FREASY_H_
#define FREASY_H_

#include <MAFS/File.h>
#include "model.h"
#include "browserView.h"
#include "applicationEditView.h"
#include "applicationInfoView.h"
#include "InputController2.h"
#include <MAUtil/Moblet.h>

/*
 * CLASS DEFINITIONS
 */
class Freasy : public Moblet{
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

	InputControllerX controller;
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



#endif /* FREASY_H_ */
