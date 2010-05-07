#include <MAUtil/Moblet.h>
#include <MAUtil/Downloader.h>
#include <MAUtil/Connection.h>
#include <MAUtil/PlaceholderPool.h>
#include <MAUtil/String.h>
#include <conprint.h>

#include <MAUtil/Geometry.h>
#include <maassert.h>
#include <mastdlib.h>
#include <maapi.h>
#include "MAHeaders.h"

using namespace MAUtil;

static const char* browserURL = "http://www.csc.kth.se/~cjanson/default2.comb";
static const char* browserSave = "browser.sav";
static const char* browserVSave = "browserVersion.sav";
static const char* exitGracefullyFile = "ExitGracefully.sav";
static const char* browserchoice = "browserChoice.sav";

class Launcher: public Moblet,
		public DownloadListener,
		public HttpConnectionListener {
private:
	enum State {
		DownBrowser, DownProgram, Ready, Idle
	} state;
	MAHandle browser;//browser to run (comb file)
	MAHandle program;//program to run (comb file)
	Downloader download;//downloader
	HttpConnection http;//http connection
	String browserVersion;//version of browser on server
	String programURLs;//used to temporary store the urls
	String urls[4];//here the urls are stored
	int urlIterator;//used to iterate over the urls
public:
	Launcher() :
		http(this) {
		http.close();
		MAExtent e = maGetScrSize();
		int w = EXTENT_X(e);
		int h = EXTENT_Y(e);
		maSetColor(0xffffff); //white
		maFillRect(0, 0, w, h);
		maSetColor(0xff0f0f); //white
		MAExtent logoExtents = maGetImageSize(LOG);
		if ((h / 2.5 - EXTENT_Y(logoExtents) / 2) > 0) {
			maDrawImage(LOG, (w >> 1) - (EXTENT_X(logoExtents) >> 1), h / 2.5
					- EXTENT_Y(logoExtents) / 2);
		} else {
			maDrawImage(LOG, (w >> 1) - (EXTENT_X(logoExtents) >> 1), 0);
		}
		maWait(5000);
		state = Idle;
		//TODO kolla exitGracefully
		download.addDownloadListener(this);
		//Check if a application have been selected
		if (checkApplication()) {
			urlIterator = 0;//set iterator to zero
			downloadProgram();//start downloading the program
		}
		//start downloading the browser
		browser = PlaceholderPool::alloc();
		if (!download.isDownloading()) {
			http.create(browserURL, HTTP_GET);
			http.finish();
		}
	}

	void keyPressEvent(int keyCode, int nativeCode) {
		// handle key presses
		if (keyCode == MAK_0) {
			if (download.isDownloading()) {
				download.cancelDownloading();
			}
			maExit(0);
		}
	}

	void keyReleaseEvent(int keyCode, int nativeCode) {
		// handle key releases
	}

	/*
	 * Returns the data stored in browserVersion.sav as a String
	 */
	String getVersion() {
		MAHandle store = maOpenStore(browserVSave, 0);
		String tmp = "";
		if (store > 0) {
			MAHandle data = PlaceholderPool::alloc();
			maReadStore(store, data);
			int size = maGetDataSize(data);
			if (size > 0) {
				//read current version of the browser on device to tmp
				tmp.resize(size);
				maReadData(data, tmp.pointer(), 0, size);
				PlaceholderPool::put(data);
				return tmp;
			}
		}
		//No previous version stored
		return "";
	}

	void downloadProgram() {
		state = DownProgram;
		bool validAdress = false;
		int i = 0;
		//printf("Downloading program\n");
		while (!validAdress) {
			int first = programURLs.findFirstOf('@', 0);
			//printf("\n%i\n", first);
			if (first == -1) {
				//printf("lastChance");
				urls[i].resize(programURLs.size());
				urls[i] = programURLs;
				validAdress = true;
			}
			String url = "";
			url.resize(first);
			url = programURLs.substr(0, first);
			String newUrls = programURLs.substr(first + 1, programURLs.size()
					- first - 1);
			programURLs.resize(newUrls.size());
			programURLs = newUrls;
			//printf("%i\n%s\n", i, url.c_str());
			urls[i].resize(url.size());
			urls[i] = url;
			i++;
		}
		download.beginDownloading(urls[0].c_str(), 0);
	}

	/*
	 * start the download of the browser
	 */
	void downloadBrowser() {
		state = DownBrowser;
		maDestroyObject(browser);// destroy the old browser
		download.beginDownloading(browserURL, 0);// begin downloading the browser
	}

	/*
	 * checkApplication examine the data in browserchoise and returns
	 * true if the file exists and it dosn't contain the exit command.
	 */
	bool checkApplication() {
		MAHandle store = maOpenStore(browserchoice, 0);
		if (store > 0) {
			MAHandle data = PlaceholderPool::alloc();
			maReadStore(store, data);
			int size = maGetDataSize(data);
			if (size > 0) {
				String str;
				str.resize(size);
				maReadData(data, str.pointer(), 0, size);
				PlaceholderPool::put(data);
				maCloseStore(store, -1);
				if (str == "EXIT") {
					maExit(0);
				} else {
					programURLs.resize(size);
					programURLs = str;
				}
				return true;
			}
		} else {
			return false;
		}
	}

	void finishedDownloading(Downloader* downloader, MAHandle downloadedData) {
		if (state == DownBrowser) {
			int size = maGetDataSize(downloadedData);
			//store browser program in browser.sav
			MAHandle store = maOpenStore(browserSave, MAS_CREATE_IF_NECESSARY);
			int res = maWriteStore(store, downloadedData);
			if (res != STERR_FULL) {
				maReadStore(store, browser);
				maCloseStore(store, 0);
				// store last-modified header in browserVersion.sav
				MAHandle data = PlaceholderPool::alloc();
				maCreateData(data, browserVersion.length());
				maWriteData(data, browserVersion.c_str(), 0,
						browserVersion.length());
				MAHandle vStore = maOpenStore(browserVSave,
						MAS_CREATE_IF_NECESSARY);
				maWriteStore(vStore, data);
				maCloseStore(vStore, 0);
				PlaceholderPool::put(data);//remove data from memory
				// load program
				maWait(7000);//debug purpose
				http.close();//close http connection to save money
				maLoadProgram(browser, 1);
			} else {
				printf("Out of system memory. Press 0 to exit.");
			}
		} else if (state == DownProgram) {
			MAHandle program = PlaceholderPool::alloc();
			int size = maGetDataSize(downloadedData);
			MAHandle store = maOpenStore("tmp.sav", MAS_CREATE_IF_NECESSARY);
			int res = maWriteStore(store, downloadedData);
			if (res != STERR_FULL) {
				maReadStore(store, program);
				maCloseStore(store, -1);
				maLoadProgram(program, 1);
			} else {
				printf("Out of system memory. Press 0 to exit.");
			}
		}
	}

	void notifyProgress(Downloader* down, int downloadedBytes, int totalBytes) {
		drawProgressbar(downloadedBytes, totalBytes, 1.2);
	}

	void downloadCancelled(Downloader* down) {
		printf("Cancelled");
		return;
	}

	void error(Downloader* down, int errorCode) {
		//printf("error %i\n", errorCode);
		if (state == DownProgram) {
			urlIterator++;
			if (urlIterator > 3) {
				printf("There are no valid addresses to download ");
				printf("this program from\n");
				//todo: vad ska jag göra om det inte finns några adresser att ladda ner programmet från?
			} else {
				//printf("Downloading from %s\n", urls[urlIterator].c_str());
				download.beginDownloading(urls[urlIterator].c_str(), 0);
			}
		}
		return;
	}

	virtual void httpFinished(HttpConnection* c, int res) {
		http.getResponseHeader("last-modified", &browserVersion);// get last-modified header and stroe it in browserversion
		//printf("server browser version\n%s\n", browserVersion.c_str());
		if (browserVersion == "") {
			maExit(0);
		}
		if (getVersion() == browserVersion) {
			//load saved browser
			MAHandle store = maOpenStore(browserSave, 0);
			if (store > 0) {
				int result = maReadStore(store, browser);
				maCloseStore(store, 0);
				if (result < 0) {
					//error: could not read
					printf("Can't read file\n");
					printf("Restart Freasy!\n");
					//todo: delete old files to remove error?
					maExit(0);
				}
				maLoadProgram(browser, 1);
			}
		} else {
			downloadBrowser();
		}
		return;
	}

	virtual void connReadFinished(Connection* c, int res) {
		printf("connread\n");
		printf("The program can't go here\n");
		printf("or should not go here is more accurate\n");
		return;
	}

	void drawProgressbar(int downloadedBytes, int totalBytes, double test) {
		MAFrameBufferInfo info;
		maFrameBufferGetInfo(&info);
		int bredd = info.width;
		int hojd = info.height;
		int a = bredd / 20;//justera proportioner här
		int b = a * 8 / 5;
		int xpos = a;
		int ypos = hojd / test - b / 2;
		int oldColor = maSetColor(0x000000);
		maFillRect(xpos - 2, ypos - 2, (bredd - 2 * a) + 4, b + 4);
		maSetColor(0xffffff);
		maFillRect(xpos - 1, ypos - 1, (bredd - 2 * a) + 2, b + 2);
		maSetColor(0x00ff00);
		maFillRect(xpos, ypos, (bredd - 2 * a) * downloadedBytes / totalBytes,
				b);
		//maSetColor(0x000000);
		//maDrawText(bredd/2-8,ypos,""+(downloadedBytes*100/totalBytes));
		maSetColor(oldColor);
		maUpdateScreen();
	}
};

extern "C" int MAMain() {
	Moblet::run(new Launcher());
	return 0;
}
;
