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



browserView::browserView() {

	MAExtent screenSize = maGetScrSize();
	scrWidth  = EXTENT_X(screenSize);
	scrHeight = EXTENT_Y(screenSize);

//	currentScreen = new AppScreen(this, "Detta är en kebabapp!", "Med den kan man köpa kebab :)");
//	screens.add(new AppScreen(this, "Detta är en kebabapp!", "Med den kan man köpa kebab :)"));
//	screens.add(new AppScreen(this, "Tetris", "Pwn da blocks!"));
//	screens.add(new ImageScreen(this));
//	screens.add(new EditBoxScreen(this));
//	screens.add(new LayoutScreen(this));
//	screens.add(new CustomScreen(this));

	layout = createMainLayout("select", "exit");
	listBox = (ListBox*) layout->getChildren()[0];

	int i;
	char *str = "MMORPTetris";
//	for(i = 0; i < 1; i++){ //testing
//		appNames.add(str);
////		screens.add(new AppScreen(this, str, "Pwn da blocks!"));
//	}

	i = 0;
	while(getAppName(i) != NULL){
		//screens.add(new AppScreen(this));
		listBox->add(createLabel(getAppName(i)));
		i++;
	}

	this->setMain(layout);
}

browserView::~browserView () {
	delete layout;
	for (int i = 0; i < screens.size(); i++) delete screens[i];
}

void browserView::putApp(char* name){
	listBox->add(createLabel(name));
}

char* browserView::getAppName(int index) {
	if(appNames.size() < index-1)
		return NULL;
	return appNames[index];
}





/*
void MainScreen::keyPressEvent(int keyCode, int nativeCode) {
	switch(keyCode) {
	case MAK_UP:
		listBox->selectPreviousItem();
		break;
	case MAK_DOWN:
		listBox->selectNextItem();
		break;
	case MAK_FIRE:
	case MAK_SOFTLEFT:
	case MAK_RIGHT:
		{
//			int index = listBox->getSelectedIndex();
//			if(index == screens.size()+1) {
//				moblet->closeEvent();
//				moblet->close();
//			}
//			else{
//				//add the screen here to save mem (one screen saved at the time)
//				screens.add(new AppScreen(this, "Detta är en kebabapp!", "Med den kan man köpa kebab :)"));
//				screens[index]->show();
//			}
			//screens.add(new AppScreen(this, "Detta är en kebabapp!", "Med den kan man köpa kebab :)"));
			screens[0]->show();
		}
		break;
	case MAK_SOFTRIGHT:
		moblet->closeEvent();
		moblet->close();
		//remove the screen here to save mem
		break;
	}
}

void MyMoblet::keyPressEvent(int keyCode, int nativeCode) {
}

void MyMoblet::keyReleaseEvent(int keyCode, int nativeCode) {
}

void MyMoblet::closeEvent() {
	// do destruction here
	delete mainScreen;
}


MyMoblet::MyMoblet() {
	gFont = new MAUI::Font(RES_FONT);
	gSkin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, true, true);
	Engine& engine = Engine::getSingleton();
	engine.setDefaultFont(gFont);
	engine.setDefaultSkin(gSkin);

	MAExtent screenSize = maGetScrSize();
	scrWidth = EXTENT_X(screenSize);
	scrHeight = EXTENT_Y(screenSize);
	mainScreen = new MainScreen();
	mainScreen->show();

}

*/
