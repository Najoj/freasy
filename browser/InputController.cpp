#include <conprint.h>
#include "InputController.h"


using namespace MAUtil;
using namespace MAUI;


InputController::InputController () {

}

void InputController::keyPressed (int keyCode) {
	if(keyCode == 12){
		maExit(0);
	}
	printf("KeyCode: %d \n", keyCode);
}

void InputController::keyReleased (int keyCode) {

}

void InputController::pointerPressed (int x, int y) {
//		printf("Pressing %d %d\n", point.x, point.y);
}

void InputController::pointerMoved (int x, int y){
//		printf("Moving %d %d\n", point.x, point.y);
}

void InputController::pointerReleased (int x, int y){
//	printf("Releasing on time\n");
}


//	void closeEvent(){
//		printf("Why do you want to exit? Don't you want cake?\n");
//	}
//	void customEvent(const MAEvent  &event){
//		printf("What just happened?\n");
//	}


