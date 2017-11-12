
#include "Globals.h"
#include "ApplicationState.h"


Configuration& getConfiguration() {
	static Configuration instance;
	return instance;
}
Textures& getTextures() {
	static Textures instance;
	return instance;
}
Application& getApplication() {
	static Application instance;
	return instance;
}

// Application

void Application::run() {
	if (!currentState) throw std::logic_error{ "Application state not set before running." };

	window.create(getConfiguration().windowSize, getConfiguration().windowTitle);
	window.setVerticalSyncEnabled(true);

	currentState->onEnter();
	while (window.isOpen()) {
		update();
		render();
		handleInputs();
	}
	currentState->onExit();
}

void Application::addState(std::string const& name, std::unique_ptr<ApplicationState>&& state) {
	states[name] = move(state);
}

void Application::setState(std::string const& name) {
	const auto oldState = currentState;
	currentState = states[name].get();
	if (oldState) {
		oldState->onExit();
	}
	currentState->onEnter();
}

void Application::update() {
	currentState->onUpdate(1.f / 60.f);
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

// Textures

void Textures::addTexture(std::string const& name, std::string const& file) {
	if (textures.find(name) == textures.end()) {
		textures[name].loadFromFile(file);
	}
}

sf::Texture& Textures::operator[](std::string const& name) {
	return textures[name];
}
