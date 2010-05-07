/*
 * viewContainer.cpp
 *
 *  Created on: May 4, 2010
 *      Author: alx
 */

#include "viewInterface.h"

char *CATEGORIES[] = {"calculate", "entertainment", "games", "news", "productivity", "search tools", "social", "sports", "travel", "utilities", "weather"};

ViewContainer::ViewContainer() {

	//do some skin and stuff
	gFont = new MAUI::Font(RES_FONT);
	gSkin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, true, true);
	Engine& engine = Engine::getSingleton();
	engine.setDefaultFont(gFont);
	engine.setDefaultSkin(gSkin);

	this->categories = CATEGORIES;

	MAExtent screenSize = maGetScrSize();
	scrWidth  = EXTENT_X(screenSize);
	scrHeight = EXTENT_Y(screenSize);

	createMainLayout("select", "exit");
	listBox = createListBox();
	mainLayout->add(softKeys);

	browser_view = new browserView(listBox);
	browser_view->setMain(mainLayout);


	createMainLayout("run", "back");
	mainLayout->add (softKeys);
	app_info_view = new AppInfoView(listBox);
	app_info_view->setMain(mainLayout);



	this->showCategories();

	browser_view->show();

//	app_info_view->show();

}

void ViewContainer::showCategories() {

	if (listBox->getChildren().size() != 0) {
		free (listBox);
		listBox = createListBox ();
	}

	listBox->add(createLabel  ("calculate"));
	listBox->add(createLabel  ("entertainment"));
	listBox->add(createLabel  ("games"));
	listBox->add(createLabel  ("news"));
	listBox->add(createLabel  ("productivity"));
	listBox->add(createLabel  ("search tools"));
	listBox->add(createLabel  ("social"));
	listBox->add(createLabel  ("sports"));
	listBox->add(createLabel  ("travel"));
	listBox->add(createLabel  ("utilities"));
	listBox->add(createLabel  ("weather"));

}

void ViewContainer::showApplications(application *applications, int count) {
	free (listBox);

	listBox = createListBox ();

	if(applications[0].name == NULL)
		listBox->add(createInfoLabel("", "No apps in this category"));

	int i;
	for(i = 0; i < count; i++){
		//printf("%s\n", applications[i].name);
		listBox->add(createLabel (applications[i].name));
	}
	browser_view->show();
}

void ViewContainer::showInfo(application * app) {
	if (app == NULL) return;

	createSoftKeyBar(30, "run", "back");

	free (listBox);


//	printf("showinfo : %s\n", app->author_first_name);
	listBox = createListBox ();

	listBox->add(createInfoLabel ("", app->name));
//	listBox->add(createInfoLabel (app->description));
	listBox->add(createInfoLabel ("description: ", app->description));
	listBox->add(createInfoLabel ("author: ", app->author_first_name));

//	app_info_view->show();


	browser_view->show ();

}

void ViewContainer::setView(int view) {

	current_view = view;

//	switch(view){
//	case CATEGORY_VIEW:
//		this->showCategories();
//		break;
//	case BROWSER_VIEW:
//		this->showApplications();
//		break;
//	case APPLICATION_INFO_VIEW:
//		this->showInfo();
//		break;
//	case APPLICATION_EDIT_VIEW:
//		break;
//	}

}

/********************************************************
 * NAVIGATION FUNCTIONS
 ********************************************************/
void ViewContainer::nextItem(){
	switch(current_view){
	case CATEGORY_VIEW:
	case BROWSER_VIEW:
		browser_view->listBox->selectNextItem();
		break;
	case APPLICATION_INFO_VIEW:
		app_info_view->listBox->selectNextItem();
		break;
	case APPLICATION_EDIT_VIEW:
		app_edit_view->listBox->selectNextItem();
		break;
	}
}

void ViewContainer::prevItem(){
	switch(current_view){
	case CATEGORY_VIEW:
	case BROWSER_VIEW:
		browser_view->listBox->selectPreviousItem();
		break;
	case APPLICATION_INFO_VIEW:
		app_info_view->listBox->selectPreviousItem();
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
	switch (current_view) {
	case CATEGORY_VIEW :
		return categories [listBox->getSelectedIndex ()];
		break;

	case BROWSER_VIEW :
		Widget * fitta = listBox->getChildren()[listBox->getSelectedIndex()];
		//printf ("kuk %s\n", (char *)((Label *) fitta)->getCaption ().c_str());

		return (char *) ((Label *) fitta)->getCaption ().c_str();
	}
}

void ViewContainer::setLabelPadding(Widget *w) {
	w->setPaddingLeft(PADDING);
	w->setPaddingBottom(PADDING);
	w->setPaddingRight(PADDING);
	w->setPaddingTop(PADDING);
}

Label* ViewContainer::createLabel(const char *str, int height) {
	Label *label;
	label = new Label(0,0, scrWidth-PADDING*2, height, NULL, str, 0, gFont);
	label->setSkin(gSkin);
	setLabelPadding(label);
	return label;
}

Label* ViewContainer::createLabel(const char *str) {
	int height = 32;
	Label *label;
	label = new Label(0,0, scrWidth-PADDING*2, height, NULL, str, 0, gFont);
	label->setSkin(gSkin);
	setLabelPadding(label);
	return label;
}

Label* ViewContainer::createInfoLabel(const char *pre, const char *str) {
	int height = 32;
	Label *label;

	String *new_str = new String(pre);
	new_str->append(str, strlen(str));

	label = new Label(0,0, scrWidth-PADDING*2, height, NULL, new_str->c_str(), 0, gFont);
	label->setSkin(NULL);
	label->setAutoSizeY();
	label->setMultiLine(true);
	setLabelPadding(label);
	return label;
}

Layout* ViewContainer::createSoftKeyBar(int height, const char *left, const char *right) {
	Layout *layout = new Layout(0, 0, scrWidth, height, NULL, 2, 1);

	softLeft = new Label(0,0, scrWidth/2, height, NULL, left, 0, gFont);
	softLeft->setHorizontalAlignment(Label::HA_LEFT);
	setLabelPadding(softLeft);
	layout->add(softLeft);

	softRight = new Label(0,0, scrWidth/2, height, NULL, right, 0, gFont);
	softRight->setHorizontalAlignment(Label::HA_RIGHT);
	setLabelPadding(softRight);
	layout->add(softRight);

	return layout;
}

void ViewContainer::changeSoftBarText(char *left, char *right) {
	softLeft->setCaption (String (left));
	softRight->setCaption (String (right));
}

Layout* ViewContainer::createMainLayout(const char *left, const char *right) {
	mainLayout = new Layout(0, 0, scrWidth, scrHeight, NULL, 1, 2);

	softKeys = createSoftKeyBar(30, left, right);

	//mainLayout->add(softKeys);

	return mainLayout;
}

ListBox* ViewContainer::createListBox() {
	ListBox *listBox = new ListBox(0, 0, scrWidth, scrHeight-softKeys->getHeight(), mainLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setSkin(gSkin);
	listBox->setPaddingLeft(5);
	listBox->setPaddingRight(5);
	listBox->setPaddingTop(15);
	listBox->setPaddingBottom(15);

	return listBox;
}
