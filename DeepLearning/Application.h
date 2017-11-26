
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <map>


class ApplicationState;
class Application {
public:
	void run();
	void quit();
	void addState(std::string const& name, std::unique_ptr<ApplicationState>&& state);
	void setState(std::string const& name);
	void setVisibility(bool visible);
private:
	ApplicationState* currentState;
	std::map<std::string, std::unique_ptr<ApplicationState>> states;
	sf::RenderWindow window;
	bool visible;

	void render();
	void handleInputs();
};
