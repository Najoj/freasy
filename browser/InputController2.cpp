/*
 * InputController2.cpp
 *
 *  Created on: 25 apr 2010
 *      Author: Ximon
 */

#include "freasy.h"

InputControllerX::InputControllerX (Freasy * freasy) {
	this->freasy = freasy;
	this->freasy->addKeyListener (this);
}

InputControllerX::~InputControllerX () {

}

/**************************************************************
 * KeyListener Functions
 **************************************************************/
void InputControllerX::keyPressEvent (int key_code, int native_code) {
	printf ("key : %d (%d) pressed\n", key_code, native_code);
}

void InputControllerX::keyReleaseEvent (int key_code, int native_code) {
	printf ("key : %d released\n", key_code);
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
