/*
 * InputController2.cpp
 *
 *  Created on: 25 apr 2010
 *      Author: Ximon
 */

#include "freasy.h"

InputControllerX::InputControllerX (Freasy * freasy) {
	this->freasy = freasy;
	this->freasy->addKeyListener     (this);
	this->freasy->addPointerListener (this);
}

InputControllerX::~InputControllerX () {

}

/**************************************************************
 * KeyListener Functions
 **************************************************************/
void InputControllerX::keyPressEvent (int key_code, int native_code) {

	switch (key_code) {

		case MAK_UP :
			freasy->handle_key_up ();
			break;

		case MAK_DOWN :
			freasy->handle_key_down ();
			break;

		case MAK_LEFT :
			freasy->handle_key_left ();
			break;

		case MAK_RIGHT :
			freasy->handle_key_right ();
			break;

		case MAK_SOFTLEFT :
			freasy->handle_key_softleft();
			break;

		case MAK_SOFTRIGHT :
			freasy->handle_key_softright();
			break;


	}


}



void InputControllerX::keyReleaseEvent (int key_code, int native_code) {
	//printf ("key : %d released\n", key_code);
}

/**************************************************************
 * PointerListener Functions
 **************************************************************/
void InputControllerX::pointerMoveEvent (MAPoint2d point) {

}

void InputControllerX::pointerReleaseEvent (MAPoint2d point) {

}
void InputControllerX::pointerPressEvent (MAPoint2d point) {

}
