/*
 * freasy.cpp
 *
 *  Created on: Apr 22, 2010
 *      Author: alx
 */

#include "freasy.h"

Freasy::Freasy(){
//	settings = fopen(settings_file_name, "r");
//	favorites = fopen(favorites_file_name, "r");
//	fclose(settings);
//	fclose(favorites);

	//printf ("tjena!\n");
	view = new browserView ();
	view->show();
}

Freasy::~Freasy(){

}

extern "C" int MAMain() {
//	Freasy freasy = new Freasy();
	Moblet::run(new Freasy());
	return 0;
}
