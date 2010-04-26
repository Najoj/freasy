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

#include <MAUI/Label.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include "viewInterface.h"
/*
Font *gFont;
WidgetSkin *gSkin;
int scrWidth;
int scrHeight;
*/
void MainScreen::setLabelPadding(Widget *w) {
	w->setPaddingLeft(PADDING);
	w->setPaddingBottom(PADDING);
	w->setPaddingRight(PADDING);
	w->setPaddingTop(PADDING);
}

Label* MainScreen::createLabel(const char *str, int height) {
	Label *label;
	label = new Label(0,0, scrWidth-PADDING*2, height, NULL, str, 0, gFont);
	label->setSkin(gSkin);
	setLabelPadding(label);
	return label;
}

Widget* MainScreen::createSoftKeyBar(int height, const char *left, const char *right) {
	Layout *layout = new Layout(0, 0, scrWidth, height, NULL, 2, 1);
	Label *label;

	label = new Label(0,0, scrWidth/2, height, NULL, left, 0, gFont);
	label->setHorizontalAlignment(Label::HA_LEFT);
	setLabelPadding(label);
	layout->add(label);

	label = new Label(0,0, scrWidth/2, height, NULL, right, 0, gFont);
	label->setHorizontalAlignment(Label::HA_RIGHT);
	setLabelPadding(label);
	layout->add(label);

	return layout;
}

// first child is listbox
Layout* MainScreen::createMainLayout(const char *left, const char *right) {
	//gFont = new MAUI::Font(RES_FONT);
	gSkin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, true, true);
	Engine& engine = Engine::getSingleton();
	engine.setDefaultFont(gFont);
	engine.setDefaultSkin(gSkin);

	Layout *mainLayout = new Layout(0, 0, scrWidth, scrHeight, NULL, 1, 2);

	Widget *softKeys = createSoftKeyBar(30, left, right);
	ListBox* listBox = new ListBox(0, 0, scrWidth, scrHeight-softKeys->getHeight(), mainLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setSkin(gSkin);
	listBox->setPaddingLeft(5);
	listBox->setPaddingRight(5);
	listBox->setPaddingTop(15);
	listBox->setPaddingBottom(15);

	mainLayout->add(softKeys);

	return mainLayout;
}
