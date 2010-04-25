#ifndef INPUTCONTROLLER_H_
#define INPUTCONTROLLER_H_

#include <conprint.h>
#include <MAUtil/Environment.h>


using namespace MAUtil;


/**
 * INPUTCONTROLLERX CLASS
 * new input controller for handling input from user
 * extends : KeyListener, PointerListener
 */
class InputControllerX : public KeyListener, public PointerListener {

	public:

        InputControllerX   ();
		~ InputControllerX ();

		/**************************************************************
		 * KeyListener Functions
		 **************************************************************/
		void keyPressEvent   (int keyCode, int nativeCode);
		void keyReleaseEvent (int keyCode, int nativeCode);

		/**************************************************************
		 * PointerListener Functions
		 **************************************************************/
		void pointerPressEvent  (MAPoint2d point) ;
		void pointerMoveEvent   (MAPoint2d point) ;
		void pointerReleaseEvent (MAPoint2d point) ;

};

#endif //INPUTCONTROLLER_H_
