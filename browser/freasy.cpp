/*
 *  freasy.cpp
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#include "freasy.h"

Freasy::Freasy () {

	setCurrentFileSystem (R_TEST_FILESYSTEM, 0);

	new InputControllerX (this); 			/* Initiate input controller to listen for user input */

	dataModel 	  = new model (this, this); /* Initiate model to communicate with servers 		  */
	views 		  = new ViewContainer (& current_view);	/* Initiate handle for views				  		  */
	current_view  = CATEGORY_VIEW; 			/* Initiate browser view at start up 		  		  */
	viewed_app	  = - 1;					/* We're currently not viewing any app				  */

	views->showCategories ();
}

Freasy::~Freasy(){

}


/************************************************************************
 * Key event functions
 ************************************************************************/

void Freasy::handle_key_down () {
	views->nextItem();
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
			views->selectedItem = views->browser_view->list_box->getSelectedIndex ();

			dataModel->connect();

			break;

		case BROWSER_VIEW :
			if (dataModel->count == 0) break;

			dataModel->download_icon (views->browser_view->list_box->getSelectedIndex ());

			break;

		case APPLICATION_INFO_VIEW :
			app2download_file = fopen ("browserChoice.sav", "w");

			//printf ("download url written to file : %s\n", dataModel->get_applications () [viewed_app].primary_dl_url);

			fputs (dataModel->get_applications () [viewed_app].primary_dl_url, app2download_file);
			fputc ('@', app2download_file);
			fputs (itoa (dataModel->get_applications () [viewed_app].id, new char, 10), app2download_file);

			fclose (app2download_file);

//			app2download_file = fopen ("browserChoice.sav", "r");
//			printf ("%s\n", fgets (new char, 100, app2download_file));
//			fclose (app2download_file);

			//printf ("%s\n", itoa (dataModel->get_applications () [viewed_app].id, new char, 10));
			//printf ("%d\n", dataModel->get_applications () [viewed_app].id);
			close  ();

			break;

	}
}

void Freasy::handle_key_softright () {

	switch (current_view) {

		case APPLICATION_INFO_VIEW :
			viewed_app = - 1;

			views->showApplications (dataModel->get_applications(), dataModel->count);
			current_view = BROWSER_VIEW;

			break;

		case BROWSER_VIEW :
			views->showCategories ();
			current_view = CATEGORY_VIEW;

			break;

		case CATEGORY_VIEW :
			String text = "EXIT";
			MAHandle data = PlaceholderPool::alloc();
			maCreateData(data, text.length());
			maWriteData(data, text.c_str(), 0, text.length());
			MAHandle store = maOpenStore("browserChoice.sav", MAS_CREATE_IF_NECESSARY);
			int res = maWriteStore(store, data);
			if (res < 0) {
				printf("ERROR in EXIT: %i\n", res);
			}
			maCloseStore(store, 0);
			PlaceholderPool::put(data);
			close();

			break;

	}

}

/****************************************************************************
 * Connection listnener functions
 ****************************************************************************/

void Freasy::connectFinished (Connection * connection, int result) {
	if (result < 0) {

		/* show exception screen */
		views->showException("Connection to server failed.");
		views->setView(BROWSER_VIEW);
//		views->current_view = BROWSER_VIEW;
		dataModel->close ();
	}
	else{
		//printf ("selected category %s\n", views->getSelected ());
		dataModel->search_by_category (views->getSelected());
	}
}

void Freasy::connWriteFinished (Connection * connection, int result) {
	if (result < 0) {
		/* show exception screen */
		views->showException("Writing of data to server failed.");
		dataModel->close ();
	}
	else {
		//printf ("finished writing!\n");
		dataModel->receive_answer (); }
}

void Freasy::connRecvFinished (Connection * connection, int result) {
	if (result < 0) {
		/* show exception screen */
		views->showException("Receiving data from server failed.");
		dataModel->close ();
	}
	else {
		//printf ("failed here!\n");
		if (dataModel->parse ()) {
			dataModel->close ();
			if (dataModel->done_parsing) {
				//printf ("done parsing!\n");
				views->showApplications (dataModel->get_applications(), dataModel->count);
//				views->setView(BROWSER_VIEW);
				current_view = BROWSER_VIEW;
			}
			else {
				printf ("stopped parsing\n");
				dataModel->connect ();
				return;
			}
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
	viewed_app = views->browser_view->list_box->getSelectedIndex ();

	//views->showInfo (dataModel->get_info (views->getSelected ()));
	views->showInfo (dataModel->get_info (views->getSelected ()), data);
	current_view = APPLICATION_INFO_VIEW;
}

void Freasy::downloadCancelled (Downloader * downloader) {

}

void Freasy::error (Downloader * downloader, int error_code) {

}


extern "C" int MAMain() {
	Moblet::run (new Freasy());
	return 0;
}
