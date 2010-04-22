/*
 * resource_downloader.cpp
 *
 *  Created on: 22 apr 2010
 *      Author: Ximon
 */

#include "model.h"

resource_downloader::resource_downloader () {

}

resource_downloader::~ resource_downloader() {

}

MAHandle * resource_downloader::download_resource (const char * url) {
	return & data;
}


/*********************************************************************
 * DownloadListner functions
 *********************************************************************/

void resource_downloader::notifyProgress (Downloader * downloader, int downloaded_bytes, int total_bytes) {

}

bool resource_downloader::outOfMemory (Downloader * downloader) {

}

void resource_downloader::finishedDownloading (Downloader * downloader, MAHandle data) {

}

void resource_downloader::downloadCancelled (Downloader * downloader) {

}

void resource_downloader::error (Downloader * downloader, int error_code) {

}

/*********************************************************************
 * ConnectionListner functions
 *********************************************************************/

void resource_downloader::connReadFinished (Connection * connection, int result) {
	if (result < 0) printf ("failed to read!\n");
}

void resource_downloader::connWriteFinished (Connection * connection, int result) {
	if (result < 0) printf ("failed to write!\n");
}

void resource_downloader::connectFinished (Connection * connection, int result) {
	if (result < 0) printf ("failed to connect!\n");
}
