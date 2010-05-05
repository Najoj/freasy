/*
 *  freasy.cpp
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#include "freasy.h"

Freasy::Freasy () {

	setCurrentFileSystem(R_TEST_FILESYSTEM, 0);

	/* Initiate input controller to listen for user input */
	new InputControllerX (this);

	/* Initiate model to communicate with servers */
	dataModel = new model (this, this);

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

	switch (current_view) {

		case CATEGORY_VIEW :
			dataModel->connect();
			break;

		case BROWSER_VIEW :
			views->showInfo (dataModel->get_info (views->getSelected ()));

			views->setView (APPLICATION_INFO_VIEW);
			current_view = APPLICATION_INFO_VIEW;

			break;

		case APPLICATION_INFO_VIEW :
			app2download_file = fopen ("toDownload.txt", "w");
			fputs ("URL", app2download_file);
			close ();

			break;

	}
}

void Freasy::handle_key_softright () {

	switch (current_view) {

		case APPLICATION_INFO_VIEW :
			views->showApplications (dataModel->get_applications(), dataModel->count);
			current_view = BROWSER_VIEW;
			views->setView (BROWSER_VIEW);
			break;

		case BROWSER_VIEW :
			views->showCategories ();
			current_view = CATEGORY_VIEW;
			views->setView(CATEGORY_VIEW);
			break;

		case CATEGORY_VIEW :
			close();
			break;

	}

}

/****************************************************************************
 * Connection listnener functions
 ****************************************************************************/

void Freasy::connectFinished (Connection * connection, int result) {
	if (result < 0) printf ("connection failed!\n");
	else{
		//printf ("selected category %s\n", views->getSelected ());
		dataModel->search_by_category (views->getSelected());
	}
}

void Freasy::connWriteFinished (Connection * connection, int result) {
	if (result < 0) printf ("writing failed!\n");
	else {
		//printf ("finished writing asshole!\n");
		dataModel->receive_answer (); }
}

void Freasy::connRecvFinished (Connection * connection, int result) {
	if (result < 0) printf ("receiving data failed!\n");
	else {
		//printf ("fuck you asshole!\n");
		if (dataModel->parse ()) {
			if (dataModel->done_parsing) {
				//printf ("done parsing asshole!\n");
				views->showApplications (dataModel->get_applications(), dataModel->count);
				views->setView(BROWSER_VIEW);
				current_view = BROWSER_VIEW;
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
