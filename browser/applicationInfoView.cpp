
#include "viewInterface.h"

AppInfoView::AppInfoView (WidgetSkin * skin) : MainScreen (skin) {

	int height = 30;

	/*************** main layout **************************/
	Layout * main_layout    = new Layout (0, 0, scrWidth, scrHeight, NULL, 1, 2);


	/*************** softkeys ********************/
	Layout * softkey_layout = new Layout(0, scrHeight, scrWidth, height, NULL, 2, 1);

	Label * softLeft  = new Label (0, 0, scrWidth / 2, height, softkey_layout);
	softLeft->setCaption ("run");
	softLeft->setBackgroundColor (0);
	softLeft->setHorizontalAlignment (Label::HA_LEFT);
	setLabelPadding (softLeft);

	Label * softRight = new Label (0, 0, scrWidth/2, height, softkey_layout);
	softRight->setCaption ("back");
	softRight->setBackgroundColor (0);
	softRight->setHorizontalAlignment (Label::HA_RIGHT);
	setLabelPadding (softRight);


	/******************* list box ********************/
	this->list_box = new ListBox (0, 0, scrWidth, scrHeight - softkey_layout->getHeight(),
								  main_layout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR,
								  true);
	list_box->setPaddingLeft   (5);
	list_box->setPaddingRight  (5);
	list_box->setPaddingTop    (15);
	list_box->setPaddingBottom (15);
	list_box->setSkin		   (skin);

	main_layout->add (softkey_layout);

	setMain (main_layout);
}

void AppInfoView::showInfo(application * app, MAHandle image) {
	if (app == NULL) return;

	createInfoLabel ("",               app->name,              list_box);
	createInfoLabel ("description : ", app->description,       list_box);
	createInfoLabel ("author : ",      app->author_first_name, list_box);

	this->showImage(image);
}

void AppInfoView::showInfo (application * app) {
	if (app == NULL) return;

	createInfoLabel ("",               app->name,              list_box);
	createInfoLabel ("description : ", app->description,       list_box);
	createInfoLabel ("author : ",      app->author_first_name, list_box);
}



void AppInfoView::showImage(MAHandle image) {

	Image *i = new Image(0, 0, 32, 32, list_box, false, false, image);
	this->show();
}

void AppInfoView::showException(const char * msg) {
	createInfoLabel ("Error: ", msg, list_box);
}
