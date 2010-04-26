 /* Copyright (C) 2009 Mobile Sorcery AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

#ifndef _VIEWINTERFACE_H_
#define _VIEWINTERFACE_H_

#include <ma.h>
#include <maheap.h>

#include "MAHeaders.h"

#include <MAUI/Screen.h>
#include <MAUI/Engine.h>
#include <MAUI/Font.h>
#include <MAUI/Label.h>
#include <MAUI/ListBox.h>
#include <MAUI/Image.h>
#include <MAUI/Layout.h>
#include <MAUI/EditBox.h>
#include <MAUtil/Moblet.h>
#include <MAUI/Widget.h>

using namespace MAUI;
using namespace MAUtil;

/* FUNCTION AND VAR DEFINITIONS */
#define PADDING 5


/* CLASS DEFINITIONS */
class MainScreen : public Screen, public WidgetListener {
public:
	//MainScreen();
	//~MainScreen();

	void setLabelPadding(Widget *w);
	Label* createLabel(const char *str, int height=32);
	Widget* createSoftKeyBar(int height, const char *left, const char *right);
	Layout* createMainLayout(const char *left, const char *right);

	Font *gFont;
	WidgetSkin *gSkin;
	int scrWidth;
	int scrHeight;
	//void keyPressEvent(int keyCode, int nativeCode);
	Vector<Screen*> screens;
	ListBox* listBox;
	Layout* layout;


private:


	Widget* createSoftKeyBar(int height, char *left, char *right);

};

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

//class MyMoblet : public Moblet  {
//public:
//	MyMoblet();
//	void keyPressEvent(int keyCode, int nativeCode);
//	void keyReleaseEvent(int keyCode, int nativeCode);
//
//	void closeEvent();
//
//private:
//	Screen *mainScreen;
//};

#endif /* _VIEWINTERFACE_H_ */
