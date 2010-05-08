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

#include "viewInterface.h"
//#include "applicationInfoView.h"

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

void AppInfoView::showInfo(application * app) {
	if (app == NULL) return;

	createInfoLabel ("",               app->name,              list_box);
	createInfoLabel ("description : ", app->description,       list_box);
	createInfoLabel ("author : ",      app->author_first_name, list_box);
}

/*
void AppInfoView::keyPressEvent(int keyCode, int nativeCode) {
	switch(keyCode) {
			case MAK_SOFTRIGHT:
				//startApp();
				break;
			case MAK_SOFTLEFT:
			case MAK_LEFT:
				previous->show();
				break;
			case MAK_UP:
				listBox->selectPreviousItem();
				break;
			case MAK_DOWN:
				listBox->selectNextItem();
				break;
	}


}

*/
