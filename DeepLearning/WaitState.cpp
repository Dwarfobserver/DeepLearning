
#include "WaitState.h"
#include "Globals.h"
#include <thread>


void WaitState::onEnter() {
	getTextures().addTexture(
		"wait_background", 
		getConfiguration().resourcesRoot + "wait_background.png");

	sprites.emplace_back();
	sprites.back().setTexture(getTextures()["wait_background"]);
}

void WaitState::onExit() {
	sprites.clear();
}

void WaitState::onUpdate(float deltaSec) {

}

void WaitState::onEvent(sf::Event const& event) {
	if (event.type == sf::Event::KeyPressed) {
		getApplication().setState("play");
	}
}
