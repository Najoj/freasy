/*
 * browserView.h
 *
 *  Created on: Apr 16, 2010
 *      Author: alx
 */

#include <conprint.h>
#include "viewInterface.h"
#include "applicationInfoView.h"
//#include "ImageScreen.h"
//#include "LayoutScreen.h"
//#include "EditBoxScreen.h"
//#include "CustomScreen.h"

#ifndef BROWSERVIEW_H_
#define BROWSERVIEW_H_

class browserView : public MainScreen {

public :

	browserView ();
	~ browserView ();

	/**************************************************
	 * GET FUNCTIONS
	 **************************************************/
	char* getAppName(int index);

	/**************************************************
	 * SET FUNCTIONS
	 **************************************************/
	void putApp(char*); //The freasy class can add apps to the list via this function
	void putInfoScreen(Screen*); //Add info-screens to the view TODO

private :
	Vector<char*> appNames;
	//AppScreen *currentScreen;
};

#endif /* BROWSERVIEW_H_ */
