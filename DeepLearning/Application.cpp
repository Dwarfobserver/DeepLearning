
#include "Application.h"
#include "Globals.h"
#include "ApplicationState.h"


void Application::run() {
	if (!currentState) throw std::logic_error{ "Application state not set before running." };

	visible = true;
	window.create(getConfiguration().windowSize, getConfiguration().windowTitle);
	window.setVerticalSyncEnabled(true);

	currentState->onEnter();
	auto oldState = currentState;
	while (window.isOpen()) {
		if (oldState != currentState) {
			oldState->onExit();
			currentState->onEnter();
			oldState = currentState;
		}
		currentState->onUpdate(1.f / 60.f);
		if (visible) render();
		handleInputs();
	}
	currentState->onExit();
}

void Application::quit() {
	window.close();
}

void Application::addState(std::string const& name, std::unique_ptr<ApplicationState>&& state) {
	states[name] = move(state);
}

void Application::setState(std::string const& name) {
	currentState = states[name].get();
}

void Application::setVisibility(bool visible) {
	this->visible = visible;
}

void Application::render() {
	window.clear();
	for (auto const& sprite : currentState->sprites) {
		window.draw(sprite);
	}
	window.display();
}

void Application::handleInputs() {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window.close();
		}
		else currentState->onEvent(e);
	}
}
