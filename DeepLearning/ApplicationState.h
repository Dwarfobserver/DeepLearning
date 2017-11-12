
#pragma once

#include <SFML/Graphics.hpp>


class ApplicationState {
public:
	std::vector<sf::Sprite> sprites;

	virtual ~ApplicationState() = default;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void onUpdate(float deltaSec) = 0;
	virtual void onEvent(sf::Event const& event) = 0;
};
