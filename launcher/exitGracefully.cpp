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

	// �ppna filen om den existerar, avsluta om ej
	MAHandle store;
	if ((store = maOpenStore(FILE, 0))==STERR_NONEXISTENT) {
		return;
	}

	//h�mta gamla filens inneh�ll
	MAHandle oldData = PlaceholderPool::alloc();
	maReadStore(store, oldData);
	int oldFileSize = maGetDataSize(oldData);
	//l�s in gamla filens inneh�ll
	char * tmp = new char[oldFileSize];
	maReadData(oldData,tmp,0,oldFileSize);
	String oldText(tmp);

	//skapa data och l�gg till den som mosync resurs
	MAHandle data = PlaceholderPool::alloc();
	//skapa data med textens l�ngd + gamla filens l�ngd som storlek
	maCreateData(data, text.length() + oldFileSize);

	//skriv gammal filens inneh�ll till data
	maWriteData(data, oldText.c_str(), 0, oldFileSize);
	//skriv OK-text till slutet av data
	maWriteData(data, text.c_str(), oldFileSize, text.length());

	//skriv data (text) till store(filen)
	int res = maWriteStore(store, data);
	//kollar om det gick
	if (res < 0) {
		printf("ERROR: %i\n", res);
	}
	//st�ng utfilen
	maCloseStore(store, 0);
	//f�rst�r objektet data och oldData fr�n minnet
	PlaceholderPool::put(oldData);
	PlaceholderPool::put(data);
}
