
#pragma once

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>


struct Configuration {
	enum class Controller {
		Player,
		Computer
	};

	sf::VideoMode windowSize;
	std::string windowTitle;
	std::string resourcesRoot;
	float scrollingSpeed; // In px per sec
	float jumpPower;
	float gravity;
	float heroPosition;
	Controller controller;
};

class Textures {
public:
	void addTexture(std::string const& name, std::string const& file);
	sf::Texture& operator[](std::string const& name);
private:
	std::map<std::string, sf::Texture> textures;
};

Configuration& getConfiguration();
Textures& getTextures();
class Application;
Application& getApplication();
