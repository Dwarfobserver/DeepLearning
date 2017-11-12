
#pragma once

#include "Animation.h"
#include <SFML/Graphics/Sprite.hpp>


class Hero {
public:
	void create(sf::Sprite& sprite);
	void update(float deltaSec);
	void jump();
	bool isAtFloor() const;
private:
	sf::Sprite* pSprite;

	Animation animRun;
	Animation animFall;

	float acceleration;
	float floor;
};
