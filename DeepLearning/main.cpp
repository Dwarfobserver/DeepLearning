
#include "Globals.h"
#include "WaitState.h"
#include "PlayState.h"


int main() {
	getConfiguration().windowSize =     { 1200, 800 };
	getConfiguration().windowTitle =    "Deep Learning";
	getConfiguration().resourcesRoot =  "../resources/";
	getConfiguration().controller =     Configuration::Controller::Player;
	getConfiguration().scrollingSpeed = 500.f;
	getConfiguration().jumpPower =      800.f;
	getConfiguration().gravity =        2000.f;
	getConfiguration().heroPosition =   100.f;

	getApplication().addState("wait", std::make_unique<WaitState>());
	getApplication().addState("play", std::make_unique<PlayState>());
	getApplication().setState("wait");
	getApplication().run();

	return 0;
}
