
#include "Globals.h"
#include "Application.h"
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

// Textures

void Textures::addTexture(std::string const& name, std::string const& file) {
	if (textures.find(name) == textures.end()) {
		textures[name].loadFromFile(file);
	}
}

sf::Texture& Textures::operator[](std::string const& name) {
	return textures[name];
}
