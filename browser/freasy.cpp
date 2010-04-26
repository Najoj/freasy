/*
 *  freasy.cpp
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#include "freasy.h"

Freasy::Freasy () {

	/* Initiate input controller to listen for user input */
	new InputControllerX (this);

	/* Initiate model to communicate with servers */
	new model (dataModel);

	/* Initiate browser view at start up */
	current_view  = BROWSER_VIEW;
	browser_view  = new browserView ();
	//browser_view->putApp(dataModel.get_applications()->name);
	int i;
	for(i = 0; i < 1; i++){
		browser_view->putApp("dummy app");
		browser_view->putInfoScreen("dummy app", "kebab");
	}

	view = browser_view;
	view->show ();

}

Freasy::~Freasy(){

}


void Freasy::handle_key_down () {

	switch (current_view) { /* Behave according to our current view */

		case BROWSER_VIEW :
			view->listBox->selectNextItem();
			break;
	}

}

void Freasy::handle_key_up () {

	switch (current_view) { /* Behave according to our current view */

		case BROWSER_VIEW :
			view->listBox->selectPreviousItem();
			break;

	}
}

void Freasy::handle_key_right () {

}

void Freasy::handle_key_left () {

}

void Freasy::handle_key_softleft () {

}

void Freasy::handle_key_softright () {

	switch (current_view) { /* Behave according to our current view */

		case BROWSER_VIEW :
			this->closeEvent();
			this->close();
			break;

	}

}


extern "C" int MAMain() {
//	Freasy freasy = new Freasy();
	Moblet::run(new Freasy());
	return 0;
}
