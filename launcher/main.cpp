#include <MAUtil/Moblet.h>
#include <MAUtil/Downloader.h>
#include <MAUtil/Connection.h>
#include <MAUtil/PlaceholderPool.h>
#include <MAUtil/String.h>
#include <conprint.h>

using namespace MAUtil;

static const char* browserURL = "http://www.csc.kth.se/~cjanson/default.comb";
static const char* browserSave = "browser.sav";
static const char* browserVSave = "browserVersion.txt";
static const char* exitGracefullyFile = "ExitGracefully.txt";
static const char* browserchoice = "browserChoice.txt";

class Launcher: public Moblet,
		public DownloadListener,
		public HttpConnectionListener {
private:
	enum State {
		DownBrowser, DownProgram, Ready, Idle
	} state;
	MAHandle browser;
	MAHandle program;
	Downloader download;
	HttpConnection http;
	String browserVersion;
	String programURLs;
	String urls[4];
	int urlIterator;
public:
	Launcher() :
		http(this) {
		http.close();
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
		// todo: handle key presses
		if (download.isDownloading()) {
			download.cancelDownloading();
		}
		maExit(0);
	}

	void keyReleaseEvent(int keyCode, int nativeCode) {
		// handle key releases
	}

	/*
	 * Returns the date stored in browserVersion.sav as a String
	 */
	String getVersion() {
		MAHandle store = maOpenStore(browserVSave, 0);
		String tmp = "";
		if (store > 0) {
			MAHandle data = PlaceholderPool::alloc();
			maReadStore(store, data);
			int size = maGetDataSize(data);
			if (size > 0) {
				tmp.resize(size);
				maReadData(data, tmp.pointer(), 0, size);
				printf("current version \n%s\n", tmp.c_str());
				PlaceholderPool::put(data);
				return tmp;
			}
		}
		printf("No previous version stored\n");//pre graphics
		return "";
	}

	void downloadProgram() {
		state = DownProgram;
		bool validAdress = false;
		int i = 0;
		printf("Downloading program\n");
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
		printf("Downloading the browser\n"); //pre graphics
		maDestroyObject(browser);// destroy the old browser
		download.beginDownloading(browserURL, 0);// begin downloading the browser
	}

	/*
	 * checkApplication examins
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
		printf("finished download\n");
		if (state == DownBrowser) {
			int size = maGetDataSize(downloadedData);
			printf("Size %i Bytes\n", size);
			MAHandle store = maOpenStore(browserSave, MAS_CREATE_IF_NECESSARY);
			maWriteStore(store, downloadedData);
			maReadStore(store, browser);
			maCloseStore(store, 0);
			// store last-modified header in browserVersion.sav
			printf("store modified header\n");//debug purpouse
			printf("%s\n", browserVersion.c_str());//debug purpouse
			MAHandle data = PlaceholderPool::alloc();
			maCreateData(data, browserVersion.length());
			maWriteData(data, browserVersion.c_str(), 0,
					browserVersion.length());
			MAHandle vStore =
					maOpenStore(browserVSave, MAS_CREATE_IF_NECESSARY);
			maWriteStore(vStore, data);
			maCloseStore(vStore, 0);
			PlaceholderPool::put(data);//remove data from memory
			// load program
			maWait(7000);//debug purpouse
			http.close();//close http connection to save mony
			maLoadProgram(browser, 1);
		} else if (state == DownProgram) {
			printf("im here!!!\n");
			MAHandle program = PlaceholderPool::alloc();
			int size = maGetDataSize(downloadedData);
			printf("Size %i Bytes\n", size);
			MAHandle store = maOpenStore("tmp.sav", MAS_CREATE_IF_NECESSARY);
			maWriteStore(store, downloadedData);
			maReadStore(store, program);
			maCloseStore(store, -1);
			//maWait(7000);//for debugg
			maLoadProgram(program, 1);
		}
	}

	void notifyProgress(Downloader* down, int downloadedBytes, int totalBytes) {
		printf("progress %i\%\n", 100 * downloadedBytes / totalBytes);
	}

	void downloadCancelled(Downloader* down) {
		printf("Cancelled");
		return;
	}

	void error(Downloader* down, int errorCode) {
		printf("error %i\n", errorCode);
		if (state == DownProgram) {
			printf("invalid Adress\n");
			urlIterator++;
			if (urlIterator > 3) {
				printf(
						"There are no valid adresses to download this program from\n");
				//todo: vad ska jag göra om det inte finns några adresser att ladda ner programmet från?
			} else {
				printf("Downloading from %s\n", urls[urlIterator].c_str());
				download.beginDownloading(urls[urlIterator].c_str(), 0);
			}
		}
		return;
	}

	virtual void httpFinished(HttpConnection* c, int res) {
		http.getResponseHeader("last-modified", &browserVersion);
		printf("server browser version\n%s\n", browserVersion.c_str());
		if (getVersion() == browserVersion) {
			printf("browser is up to date");
			//load saved browser
			MAHandle store = maOpenStore(browserSave, 0);
			if (store > 0) {
				int result = maReadStore(store, browser);
				maCloseStore(store, 0);
				if (result < 0) {
					//error: could not read
					printf("Can't read file\n");
					//todo: delete old files to remove error?
					maExit(0);
				}
				maWait(5000);//debug purpouse
				maLoadProgram(browser, 1);
			}
		} else {
			printf("Download new browser");
			downloadBrowser();
		}
		return;
	}

	virtual void connReadFinished(Connection* c, int res) {
		printf("connread\n");
		return;
	}
};

extern "C" int MAMain() {
	Moblet::run(new Launcher());
	return 0;
}
;
