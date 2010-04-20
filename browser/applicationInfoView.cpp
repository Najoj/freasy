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
#include "applicationInfoView.h"

AppScreen::AppScreen(Screen *previous, char *title, char *descr) : previous(previous) {
	mainLayout = createMainLayout("see comments", "run");
	listBox = (ListBox*) mainLayout->getChildren()[0];

	Label *label;
//	label = createLabel("BottomRight", 64);
//	label->setHorizontalAlignment(Label::HA_RIGHT);
//	label->setVerticalAlignment(Label::VA_BOTTOM);
//	label->setSkin(gSkin);
//	listBox->add(label);

	label = createLabel
	(
		title,
		32
	);
	label->setAutoSizeY();
	label->setSkin(NULL); // no skin
	label->setMultiLine(true);
	listBox->add(label);

	label = createLabel
	(
		descr,
		32
	);
	label->setAutoSizeY();
	label->setSkin(NULL); // no skin
	label->setMultiLine(true);
	listBox->add(label);

	label = createLabel
	(
		"Rating:",
		32
	);
	label->setAutoSizeY();
	label->setSkin(NULL); // no skin
	label->setMultiLine(true);
	listBox->add(label);

	label = createLabel("automatic resizing", 32);
	label->setAutoSizeX();
	label->setSkin(gSkin);
//	listBox->add(label);

	this->setMain(mainLayout);
}

AppScreen::~AppScreen() {
	delete mainLayout;
}

void AppScreen::keyPressEvent(int keyCode, int nativeCode) {
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

