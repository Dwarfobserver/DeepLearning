
#pragma once

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>


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

class ApplicationState;
class Application {
public:
	void run();
	void addState(std::string const& name, std::unique_ptr<ApplicationState>&& state);
	void setState(std::string const& name);
private:
	ApplicationState* currentState;
	std::map<std::string, std::unique_ptr<ApplicationState>> states;
	sf::RenderWindow window;

	void update();
	void render();
	void handleInputs();
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
Application& getApplication();
