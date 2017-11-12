
#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Window;

class Animation {
public:
	void create(std::string const& name);
	void start(sf::Sprite& sprite, float loopSec = 0.5f);
	void update(float deltaSec);
	void stop();
	bool isRunning() const;
private:
	std::string name;
	sf::Sprite* pSprite;

	float maxSec;
	float currentSec;

	int spritesCount;
	int numSprite;
};
