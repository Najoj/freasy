/*
 * exitGracefully.cpp
 *
 *  Created on: 19 apr 2010
 *      Author: Staffan
 */
#include "exitGracefully.h"
#include <ma.h>
#include <conprint.h>

#include <MAP/DateTime.h>
#include <MAUtil/PlaceholderPool.h>
#include <MAUtil/String.h>

using namespace MAPUtil;
using namespace MAUtil;

void gracefullExit() {
	//filnamn
	const char* FILE = "ExitGracefully.sav";
	//text som ska skrivas in i filen
	String text("#");

	// öppna filen om den existerar, avsluta om ej
	MAHandle store;
	if ((store = maOpenStore(FILE, 0))==STERR_NONEXISTENT) {
		return;
	}

	//hämta gamla filens innehåll
	MAHandle oldData = PlaceholderPool::alloc();
	maReadStore(store, oldData);
	int oldFileSize = maGetDataSize(oldData);
	//läs in gamla filens innehåll
	char * tmp = new char[oldFileSize];
	maReadData(oldData,tmp,0,oldFileSize);
	String oldText(tmp);

	//skapa data och lägg till den som mosync resurs
	MAHandle data = PlaceholderPool::alloc();
	//skapa data med textens längd + gamla filens längd som storlek
	maCreateData(data, text.length() + oldFileSize);

	//skriv gammal filens innehåll till data
	maWriteData(data, oldText.c_str(), 0, oldFileSize);
	//skriv OK-text till slutet av data
	maWriteData(data, text.c_str(), oldFileSize, text.length());

	//skriv data (text) till store(filen)
	int res = maWriteStore(store, data);
	//kollar om det gick
	if (res < 0) {
		printf("ERROR: %i\n", res);
	}
	//stäng utfilen
	maCloseStore(store, 0);
	//förstör objektet data och oldData från minnet
	PlaceholderPool::put(oldData);
	PlaceholderPool::put(data);
}
