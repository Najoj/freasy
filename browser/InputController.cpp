#include <MAUtil/Moblet.h>
#include <conprint.h>


using namespace MAUtil;

class InputController : public Moblet {
public:
	InputController() {
	}

	void keyPressEvent(int keyCode) {
		if(keyCode == 12){
			maExit(0);
		}
		printf("KeyCode: %d \n", keyCode);
	}

	void keyReleaseEvent(int keyCode) {
	}

	void pointerPressEvent(MAPoint2d point) {
		printf("Pressing %d %d\n", point.x, point.y);
		}
	void pointerMoveEvent(MAPoint2d  point){
		printf("Moving %d %d\n", point.x, point.y);
	}
	void pointerReleaseEvent(MAPoint2d  point){
		printf("Releasing on time\n");
	}
	void closeEvent(){
		printf("Why do you want to exit? Don't you want cake?\n");
	}
	void customEvent(const MAEvent  &event){
		printf("What just happened?\n");
	}


};

extern "C" int MAMain() {
	Moblet::run(new InputController());
	return 0;
};
