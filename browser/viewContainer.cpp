/*
 * viewContainer.cpp
 *
 *  Created on: May 4, 2010
 *      Author: alx
 */

#include "viewInterface.h"

char *CATEGORIES[] = {"calculate", "entertainment", "games", "news", "productivity", "search tools", "social", "sports", "travel", "utilities", "weather"};

ViewContainer::ViewContainer(int * current_view) {

	this->current_view = current_view;

	//do some skin and stuff
	gFont = new MAUI::Font (RES_FONT);
	gSkin = new WidgetSkin (RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, true, true);

	Engine& engine = Engine::getSingleton ();
	engine.setDefaultFont (gFont);
	engine.setDefaultSkin (gSkin);

	this->categories = CATEGORIES;
	selectedItem = 0;
}

void ViewContainer::setView(int view) {

	* current_view = view;

}

/********************************************************
 * NAVIGATION FUNCTIONS
 ********************************************************/
void ViewContainer::nextItem(){
	switch(* current_view){
		case CATEGORY_VIEW:

		case BROWSER_VIEW:
			browser_view->select_next ();
			break;

		case APPLICATION_INFO_VIEW:
			break;

		case APPLICATION_EDIT_VIEW:
			app_edit_view->listBox->selectNextItem();
			break;
	}
}

void ViewContainer::prevItem(){
	switch (* current_view) {
		case CATEGORY_VIEW:
		case BROWSER_VIEW:
			browser_view->select_previous ();
			break;

		case APPLICATION_INFO_VIEW:
			break;

		case APPLICATION_EDIT_VIEW:
			app_edit_view->listBox->selectPreviousItem();
			break;
	}
}

/********************************************************
 * UTILITY FUNCTIONS
 ********************************************************/

char* ViewContainer::getSelected(){
	switch (* current_view) {
		case CATEGORY_VIEW :
			return categories [browser_view->list_box->getSelectedIndex ()];
			break;

		case BROWSER_VIEW :
			Widget * fitta = browser_view->list_box->getChildren () [browser_view->list_box->getSelectedIndex ()];
			//printf ("kuk %s\n", (char *)((Label *) fitta)->getCaption ().c_str());

			return (char *) ((Label *) fitta)->getCaption ().c_str ();

			break;
	}
}

void ViewContainer::showApplications (application * applications, int count) {

	switch (* current_view) {

		case CATEGORY_VIEW :
			delete browser_view;
			break;

		case APPLICATION_INFO_VIEW :
			delete app_info_view;
			break;

	}

	browser_view = new browserView (gSkin);
	//Set the previous category
	printf("selected index %d", selectedItem);

	browser_view->showApplications (applications, count);

	browser_view->show ();
}

void ViewContainer::showInfo (application * app) {
	delete browser_view;

	app_info_view = new AppInfoView (gSkin);
	app_info_view->showInfo (app);
	app_info_view->show ();
}

void ViewContainer::showCategories () {
	if (browser_view != NULL) delete browser_view;

	browser_view = new browserView (gSkin);
	browser_view->showCategories ();
	browser_view->list_box->setSelectedIndex(selectedItem);
	browser_view->show ();
}

void ViewContainer::showException (const char * msg) {

	switch (* current_view) {

		case CATEGORY_VIEW :
			delete browser_view;
			break;

		case APPLICATION_INFO_VIEW :
			delete app_info_view;
			break;

	}

	app_info_view = new AppInfoView (gSkin);
	app_info_view->showException (msg) ;
	app_info_view->show ();

}

//void ViewContainer::setCategoryChoosen(int i){
	//browser_view ->selectedItem = i;
//}
