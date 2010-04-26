/*
 * freasy.cpp
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#include "freasy.h"

Freasy::Freasy () {

	/* Initiate broswer view at start up */
	current_view  = BROWSER_VIEW;
	browser_view  = new browserView ();

	view = browser_view;
	view->show ();

	/* Initiate input controller to listen for user input */
	new InputControllerX (this);

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


extern "C" int MAMain() {
//	Freasy freasy = new Freasy();
	Moblet::run(new Freasy());
	return 0;
}
