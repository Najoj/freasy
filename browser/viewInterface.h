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
#include <MAUtil/String.h>

#include "model.h"

#define BROWSER_VIEW 			0
#define APPLICATION_EDIT_VIEW 	1
#define APPLICATION_INFO_VIEW 	2
#define CATEGORY_VIEW 			3

using namespace MAUI;
using namespace MAUtil;

/* FUNCTION AND VAR DEFINITIONS */
#define PADDING 5


/* CLASS DEFINITIONS */
class MainScreen : public Screen, public WidgetListener {
public:
	//MainScreen();
	//~MainScreen();
/*
	void setLabelPadding(Widget *w);
	Label* createLabel(const char *str, int height=32);
	Widget* createSoftKeyBar(int height, const char *left, const char *right);
	Layout* createMainLayout(const char *left, const char *right);


	//void keyPressEvent(int keyCode, int nativeCode);
	Vector<Screen*> screens;
	ListBox* listBox;
	Layout* layout;
	*/


private:


	//Widget* createSoftKeyBar(int height, char *left, char *right);

};

class browserView : public MainScreen {

public :

	browserView (ListBox *listBox);
	~ browserView ();

	/**************************************************
	 * GET FUNCTIONS
	 **************************************************/
	char* getAppName(int index);
	char* getSelected();

	/**************************************************
	 * SET FUNCTIONS
	 **************************************************/
	void putApp(const char*); //The freasy class can add apps to the list via this function

	/**************************************************
	 * MISC FUNCTIONS
	 **************************************************/
	void listApplications(application *application, int numApps);
	void listCategories();
	void clearApps(); // remove all apps from the list
	bool browserView::alreadyCategorized(const char* category); // check if a category has been shown

	ListBox *listBox;

private :
	Vector<char*> appNames;
	Vector<const char*> categorized;
//	static char *categories[] = {"calculate", "entertainment", "games", "news", "productivity", "search tools", "social", "sports", "travel", "utilities", "weather"};
	char ** categories;
	//AppInfoView *currentScreen;
};

class AppInfoView : public MainScreen {
public:
	AppInfoView(ListBox *listBox);
	~AppInfoView();
	//void keyPressEvent(int keyCode, int nativeCode);
	int addInfo(char*);

	ListBox *listBox;
private:
	Screen *previous;
	Layout *mainLayout;
};

/**
 *  The screen class used for demonstrating how to
 *  use \a EditBoxes and their different modes.
 */
class AppEditView : public MainScreen {
public:
	/**
	 * Constructor
	 * Sets up the UI hierarchy for this screen, filling
	 * it with a number of \a EditBoxes.
	 * @param previous a pointer to the screen to return to
	 */
	AppEditView(Screen *previous);
	/**
	 * Destructor
	 */
	~AppEditView();
	/**
	 * Recieves key presses and performs appropriate interaction
	 * with the UI.
	 */
	//void keyPressEvent(int keyCode, int nativeCode);
	/**
	 * Implementation of a \a WidgetListener callback, which
	 * is notified whenever the selection state of a \a widget
	 * it's listeting to changes. I our case, we make sure that
	 * whenever a widget is selected, we make its first child
	 * selected instead.
	 */
	void selectionChanged(Widget *widget, bool selected);
	/**
	 * Overload of MAUI::Screen::show().
	 */
	void show();

	ListBox* listBox;

private:

	Screen *previous;
	Layout* mainLayout;
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

class ViewContainer {
public:
	ViewContainer();
	~ViewContainer();

	/**************************************************
	 * GET FUNCTIONS
	 **************************************************/
	char* getSelected();

	/**************************************************
	 * SET FUNCTIONS
	 **************************************************/
	void setView(int view);
	void changeSoftBarText(char *left, char *right);

	/**************************************************
	 * MISC FUNCTIONS
	 **************************************************/
	void showCategories();
	void showApplications(application *applications, int count);
	void showInfo(application * app);

	void prevItem();
	void nextItem();

	void setLabelPadding(Widget *w);
	Label* createLabel(const char *str, int height);
	Label* createLabel(const char *str);
	Label* createInfoLabel(const char *pre, const char *str); //a label for app_info_view
	Layout* createMainLayout(const char *left, const char *right);
	Layout* createSoftKeyBar(int height, const char *left, const char *right);
	ListBox* createListBox();

	ListBox *listBox;

	browserView *browser_view;
	AppInfoView *app_info_view;
	AppEditView *app_edit_view;

private:
	Font *gFont;
	WidgetSkin *gSkin;

	int current_view;

	int scrWidth;
	int scrHeight;

	Widget *softKeys;

	Label *softLeft;
	Label *softRight;
	Layout *mainLayout;

	char **categories;
};

#endif /* _VIEWINTERFACE_H_ */
