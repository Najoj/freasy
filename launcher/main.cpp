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

//static const char* browserURL = "http://www.csc.kth.se/~jacobnor/browser.comb";
//static const char* browserURL = "http://www.csc.kth.se/~ohassel/freasy/CharlieTheUnicornSoundboard/application.comb";
static const char* browserURL = "http://freasy.googlecode.com/files/program.comb";
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
	String programID;//here the program identity is stored
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

		//Draws "exit" on the screen
		maSetColor(0x000000); //white
		maDrawText(w-28, h- 14, "Exit");
		maWait(3000);
		state = Idle;
		checkExitGracefully();//check exitGracefully
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
		if (keyCode == MAK_SOFTRIGHT){
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
			if (first == -1) {
				//printf("lastChance");
				//urls[i].resize(programURLs.size());
				//urls[i] = programURLs;
				programID.resize(programURLs.size());
				programID = programURLs;
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
		String app = "application.comb";
		urls[0].append(app.c_str(), app.length());
		//printf("%s", urls[0].c_str());
		/*maWait(4000);
		 MAHandle data = PlaceholderPool::alloc();
		 maCreateData(data, urls[0].length());
		 maWriteData(data, urls[0].c_str(), 0, urls[0].length());
		 MAHandle store = maOpenStore("tmpURL.txt", MAS_CREATE_IF_NECESSARY);
		 maWriteStore(store, data);
		 maCloseStore(store, 0);
		 PlaceholderPool::put(data);*/
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
				maWait(1000);//debug purpose
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
				maCloseStore(store, -1);//-1
				//exitGracefully file write
				MAHandle data = PlaceholderPool::alloc();
				maCreateData(data, programID.length());
				maWriteData(data, programID.c_str(), 0, programID.length());
				MAHandle store = maOpenStore(exitGracefullyFile,
						MAS_CREATE_IF_NECESSARY);
				maWriteStore(store, data);
				maCloseStore(store, 0);
				PlaceholderPool::put(data);

				//Clears background
				maSetColor(0x000000);
				MAFrameBufferInfo info;
				maFrameBufferGetInfo(&info);
				maFillRect(0, 0, info.width, info.height);

				maLoadProgram(program, 1);/*start the program*/
				/*MAHandle data1 = PlaceholderPool::alloc();
				 maCreateData(data1, urls[0].length());
				 maWriteData(data1, urls[0].c_str(), 0, urls[0].length());
				 MAHandle store1 = maOpenStore("tmpURLLP.txt", MAS_CREATE_IF_NECESSARY);
				 maWriteStore(store1, data1);
				 maCloseStore(store1, 0);
				 PlaceholderPool::put(data1);*/
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
				maWait(3000);
				maExit(0);
			} else {
				//printf("Downloading from %s\n", urls[urlIterator].c_str());
				download.beginDownloading(urls[urlIterator].c_str(), 0);
			}
		} else {
//			printf("error %i\n", errorCode);
			printf("error Connecting, check your connection");

			printf("Exit");
			maWait(5000);
			maExit(0);
		}
		return;
	}

	virtual void httpFinished(HttpConnection* c, int res) {
		if (res >= 200 && res <= 299) { //ok
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
		}else{
			/** DISPLAYS ERROR SCREEN!**/
			//printf("ERROR: %i\n",res);
			maSetColor(0xffffff);
			MAExtent e = maGetScrSize();
			maFillRect(0,0,EXTENT_X(e),EXTENT_Y(e));
			maSetColor(0x000000);
			//I dont know if this buffer, should perhaps be  larger.
			char str[10];
//			sprintf(str,"ERROR: %i",res);
			sprintf(str,"Connection error",res);
			maDrawText((EXTENT_X(e)/2)-46,(EXTENT_Y(e)/2),str);
			maDrawText(EXTENT_X(e)-28, EXTENT_Y(e)- 14, "Exit");
			maUpdateScreen();
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

	void checkExitGracefully() {
		MAHandle store;
		if ((store = maOpenStore(exitGracefullyFile, 0)) == STERR_NONEXISTENT) {
			return;/*no exit gracefully*/
		}
		MAHandle data = PlaceholderPool::alloc();
		maReadStore(store, data);
		maCloseStore(store, -1);
		String tmp;
		int size = maGetDataSize(data);
		if (size > 0) {
			//read data from exit gracefully
			tmp.resize(size);
			maReadData(data, tmp.pointer(), 0, size);
			PlaceholderPool::put(data);
		}
		int first = tmp.findFirstOf('#', 0);
		String tid = "";/*temporary ID*/
		tid.resize(first);
		tid = tmp.substr(0, first);
		if (first == -1) {
			/*didn't exit gracefully*/
			printf("didn't exit gracefully");
			maWait(4000);
			//TODO : report to server
			return;
		} else {
			printf("ID; %s\nExited gracefully", tid.c_str());
			/*MAHandle data = PlaceholderPool::alloc();
			 maCreateData(data, tid.length());
			 maWriteData(data, tid.c_str(), 0, tid.length());
			 store = maOpenStore("tmpEG.txt",
			 MAS_CREATE_IF_NECESSARY);
			 maWriteStore(store, data);
			 maCloseStore(store, 0);
			 PlaceholderPool::put(data);*/
			maWait(4000);
			//TODO : report to server
		}
		return;
	}
};

extern "C" int MAMain() {
	Moblet::run(new Launcher());
	return 0;
}
;
