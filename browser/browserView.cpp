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

browserView::browserView (WidgetSkin * skin) : MainScreen (skin) {

	int height = 30;

	/*************** main layout **************************/
	Layout * main_layout    = new Layout (0, 0, scrWidth, scrHeight, NULL, 1, 2);


	/******************* list box ********************/
	this->list_box = new ListBox (0, 0, scrWidth, scrHeight - height,
								  main_layout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR,
								  true);
	list_box->setPaddingLeft   (5);
	list_box->setPaddingRight  (5);
	list_box->setPaddingTop    (15);
	list_box->setPaddingBottom (15);
	list_box->setSkin		   (skin);

	setMain (main_layout);
}

void browserView::showCategories() {

	/*************** softkeys ********************/
	int height = 30;
	Layout * softkey_layout = new Layout(0, scrHeight, scrWidth, height, NULL, 2, 1);

	Label * softLeft  = new Label (0, 0, scrWidth / 2, height, softkey_layout);
	softLeft->setCaption ("select");
	softLeft->setBackgroundColor (0);
	softLeft->setHorizontalAlignment (Label::HA_LEFT);
	setLabelPadding (softLeft);

	Label * softRight = new Label (0, 0, scrWidth/2, height, softkey_layout);
	softRight->setCaption ("exit");
	softRight->setBackgroundColor (0);
	softRight->setHorizontalAlignment (Label::HA_RIGHT);
	setLabelPadding (softRight);

	this->getMain ()->add (softkey_layout);

	createLabel ("calculate",     list_box);
	createLabel ("entertainment", list_box);
	createLabel ("games", 		  list_box);
	createLabel ("news", 		  list_box);
	createLabel ("productivity",  list_box);
	createLabel ("search tools",  list_box);
	createLabel ("social",    	  list_box);
	createLabel ("sports",    	  list_box);
	createLabel ("travel",    	  list_box);
	createLabel ("utilities", 	  list_box);
	createLabel ("weather",   	  list_box);
}

void browserView::showApplications(application *applications, int count) {
	if(applications[0].name == NULL)
		createInfoLabel ("", "No apps in this category", list_box);

	/*************** softkeys ********************/
	int height = 30;
	Layout * softkey_layout = new Layout(0, scrHeight, scrWidth, height, NULL, 2, 1);

	Label * softLeft  = new Label (0, 0, scrWidth / 2, height, softkey_layout);
	softLeft->setCaption ("select");
	softLeft->setBackgroundColor (0);
	softLeft->setHorizontalAlignment (Label::HA_LEFT);
	setLabelPadding (softLeft);

	Label * softRight = new Label (0, 0, scrWidth/2, height, softkey_layout);
	softRight->setCaption ("back");
	softRight->setBackgroundColor (0);
	softRight->setHorizontalAlignment (Label::HA_RIGHT);
	setLabelPadding (softRight);

	this->getMain ()->add (softkey_layout);

	int i;
	for(i = 0; i < count; i++){
		//printf("%s\n", applications[i].name);
		createLabel (applications [i].name, list_box);
	}
}

void browserView::select_next () {
	list_box->selectNextItem ();
}

void browserView::select_previous () {
	list_box->selectPreviousItem ();
}

