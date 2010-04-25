#ifndef INPUTCONTROLLER_H_
#define INPUTCONTROLLER_H_

#include <conprint.h>
#include <MAUI/InputManager.h>


using namespace MAUtil;
using namespace MAUI;

//I guess the name is pretty self-explanitory
class InputController : public InputManager {

	public:

        InputController   ();
		~ InputController ();

		//Key funcions
		void keyPressed		(int keyCode);
		void keyReleased	(int keyCode);

		//Pointer functions (For phones with stylus/touchscreen)
		void pointerPressed	 (int x, int y);
		void pointerMoved	 (int x, int y);
		void pointerReleased (int x, int y);


};

#endif //INPUTCONTROLLER_H_
