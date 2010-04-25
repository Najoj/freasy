#ifndef INPUTCONTROLLER_H_
#define INPUTCONTROLLER_H_

#include <conprint.h>
#include <MAUI/InputManager.h>


using namespace MAUtil;
using namespace MAUI;

//I guess the name is pretty self-explanitory
class InputController : public InputManager {

	public:
        	InputController();
		~InputController();


		//Key funcions
		void keyPress		(int keyCode);
		void keyRelease		(int keyCode);

		//Pointer functions (For phones with stylus/touchscreen)
		void pointerPress	(int x, int y);
		void pointerMove	(int x, int y);
		void pointerRelease	(int x, int y);


};

#endif //INPUTCONTROLLER_H_
