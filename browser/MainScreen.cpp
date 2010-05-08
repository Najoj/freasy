/*
 * MainScreen.cpp
 *
 *  Created on: May 8, 2010
 *      Author: alx
 */

#include "viewInterface.h"

MainScreen::MainScreen(WidgetSkin * gSkin){

	this->gSkin = gSkin;
	//ListBox *listBox;

	MAExtent screenSize = maGetScrSize();
	scrWidth  = EXTENT_X(screenSize);
	scrHeight = EXTENT_Y(screenSize);

}

MainScreen::~MainScreen (){
//	printf ("fawkyou");
	delete getMain ();
}

void MainScreen::setLabelPadding(Widget *w) {
	w->setPaddingLeft(PADDING);
	w->setPaddingBottom(PADDING);
	w->setPaddingRight(PADDING);
	w->setPaddingTop(PADDING);
}

Label* MainScreen::createLabel(const char *str, int height) {
	Label *label;
	label = new Label (0, 0, scrWidth - PADDING * 2, height, NULL, str, 0, gFont);
//	label->setCaption(str);
	//label->setSkin(gSkin);
	setLabelPadding(label);
	return label;
}

Label* MainScreen::createLabel (const char *str, Widget * parent) {
	int height = 32;
	Label *label;
	label = new Label (0, 0, scrWidth - PADDING * 2, height, parent);
	label->setSkin    (gSkin);
	label->setCaption (str);
	label->setBackgroundColor(0);
	setLabelPadding   (label);
	return label;
}

Label* MainScreen::createInfoLabel (const char * pre, const char * str, Widget * parent) {
	int height = 32;

	Label * label;

	String *new_str = new String (pre);
	new_str->append (str, strlen (str));

	label = new Label (0, 0, scrWidth - PADDING * 2, height, parent);
	label->setCaption 		  (* new_str);
	label->setBackgroundColor (0);

	label->setAutoSizeY ();
	label->setMultiLine (true);
	setLabelPadding     (label);

	return label;
}

Layout* MainScreen::createSoftKeyBar(int height, const char *left, const char *right) {
	Layout *layout = new Layout(0, 0, scrWidth, height, NULL, 2, 1);

	Label *softLeft = new Label(0,0, scrWidth/2, height, NULL, left, 0, gFont);
	softLeft->setHorizontalAlignment(Label::HA_LEFT);
	setLabelPadding(softLeft);
	layout->add(softLeft);

	Label *softRight = new Label(0,0, scrWidth/2, height, NULL, right, 0, gFont);
	softRight->setHorizontalAlignment(Label::HA_RIGHT);
	setLabelPadding(softRight);
	layout->add(softRight);
	return layout;
}

//void MainScreen::changeSoftBarText(char *left, char *right) {
//	softLeft->setCaption (String (left));
//	softRight->setCaption (String (right));
//}

Layout* MainScreen::createMainLayout(const char *left, const char *right) {
	mainLayout = new Layout(0, 0, scrWidth, scrHeight, NULL, 1, 2);

	softKeys = createSoftKeyBar(30, left, right);

	mainLayout->add(softKeys); //que?

	listBox = createListBox ();

	setMain (mainLayout);

	return mainLayout;
}

ListBox* MainScreen::createListBox() {
	ListBox *listBox = new ListBox(0, 0, scrWidth, scrHeight-softKeys->getHeight(), mainLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setSkin(gSkin);
	listBox->setPaddingLeft(5);
	listBox->setPaddingRight(5);
	listBox->setPaddingTop(15);
	listBox->setPaddingBottom(15);

	return listBox;
}

