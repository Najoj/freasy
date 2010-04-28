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
	dataModel = new model (this);
	dataModel->connect ();

	/* Initiate browser view at start up */
	current_view  = BROWSER_VIEW;
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

	switch (current_view) { /* Behave according to our current view */

		case BROWSER_VIEW :
			current_view  = APPLICATION_INFO_VIEW;
			view = app_info_view;
			view->show ();
			break;

		/* go back to browser screen */
		case APPLICATION_INFO_VIEW:
			current_view  = BROWSER_VIEW;
			view = browser_view;
			view->show();
			break;

	}
}

void Freasy::handle_key_softright () {

	switch (current_view) { /* Behave according to our current view */

		case BROWSER_VIEW :
			this->closeEvent();
			this->close();
			break;

		case APPLICATION_INFO_VIEW :

			break;

	}
}

/****************************************************************************
 * Connection listnener functions
 ****************************************************************************/

void Freasy::connectFinished (Connection * connection, int result) {
	if (result < 0) printf ("connection failed!\n");
	else dataModel->send_request ();
}

void Freasy::connWriteFinished (Connection * connection, int result) {
	if (result < 0) printf ("writing failed!\n");
	else dataModel->receive_answer ();
}

void Freasy::connRecvFinished (Connection * connection, int result) {
	if (result < 0) printf ("receiving data failed!\n");
	else {
		dataModel->parse ();

		browser_view  = new browserView (dataModel->get_applications(), dataModel->count);

		//app_info_view = new AppScreen (browser_view, "dummy app", "dummy desc");

		view = browser_view;
		view->show ();
	}
}

void Freasy::connReadFinished (Connection * connection, int result) {
	if (result < 0) printf ("reading data failed!\n");
}


/****************************************************************************
 * Download listnener functions
 ****************************************************************************/

void Freasy::notifyProgress (Downloader * downloader, int downloaded_bytes, int total_bytes) {

}

bool Freasy::outOfMemory (Downloader * downloader) {

}

void Freasy::finishedDownloading (Downloader * downloader, MAHandle data) {

}

void Freasy::downloadCancelled (Downloader * downloader) {

}

void Freasy::error (Downloader * downloader, int error_code) {

}











extern "C" int MAMain() {
	Moblet::run (new Freasy());
	return 0;
}
