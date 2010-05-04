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
	dataModel = new model (this, this);

	//dataModel->connect ();

	views = new ViewContainer();

	/* Initiate browser view at start up */
	current_view  = CATEGORY_VIEW;
}

Freasy::~Freasy(){

}


/************************************************************************
 * Key event functions
 ************************************************************************/

void Freasy::handle_key_down () {

	views->nextItem();
//	printf("key_down pressed");

}

void Freasy::handle_key_up () {

	views->prevItem();

}

void Freasy::handle_key_right () {

}

void Freasy::handle_key_left () {

}

void Freasy::handle_key_softleft () {

	dataModel->connect();

}

void Freasy::handle_key_softright () {

}

/****************************************************************************
 * Connection listnener functions
 ****************************************************************************/

void Freasy::connectFinished (Connection * connection, int result) {
	if (result < 0) printf ("connection failed!\n");
	else dataModel->search_by_category (views->getSelected());
}

void Freasy::connWriteFinished (Connection * connection, int result) {
	if (result < 0) printf ("writing failed!\n");
	else dataModel->receive_answer ();
}

void Freasy::connRecvFinished (Connection * connection, int result) {
	if (result < 0) printf ("receiving data failed!\n");
	else {
		if (dataModel->parse ()) {
			if (dataModel->done_parsing) {
				views->showApplications (dataModel->get_applications(), dataModel->count);
				views->setView(BROWSER_VIEW);
//				current_view = BROWSER_VIEW;
				dataModel->close ();
			}
			else { printf ("stopped parsing\n"); return; }
		}
		else dataModel->receive_answer ();

//		app_info_view = new AppInfoView (browser_view, "dummy app", "dummy desc");
	}
}

void Freasy::connReadFinished (Connection * connection, int result) {
	//if (result < 0) printf ("reading data failed!\n");
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
