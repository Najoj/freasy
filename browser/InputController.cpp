#include <conprint.h>
#include <MAUI/InputManager.h>


using namespace MAUtil;
using namespace MAUI;

class InputController : public InputManager {
public:
	InputController() {
	}

	void keyPress(int keyCode) {
		if(keyCode == 12){
			maExit(0);
		}
		printf("KeyCode: %d \n", keyCode);
	}

	void keyRelease(int keyCode) {
	}

	void pointerPress(int x, int y) {
//		printf("Pressing %d %d\n", point.x, point.y);
		}
	void pointerMove(int x, int y){
//		printf("Moving %d %d\n", point.x, point.y);
	}
	void pointerRelease(int x, int y){
		printf("Releasing on time\n");
	}
//	void closeEvent(){
//		printf("Why do you want to exit? Don't you want cake?\n");
//	}
//	void customEvent(const MAEvent  &event){
//		printf("What just happened?\n");
//	}


};


