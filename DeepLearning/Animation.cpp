
#include "Animation.h"
#include "Globals.h"
#include "fstream"


void Animation::create(std::string const& name) {
	this->name = name;
	pSprite = nullptr;
	numSprite = -1;

	int num = 0;
	while (true) {
		const auto imagePath = getConfiguration().resourcesRoot + name + "/" + std::to_string(num) + ".png";
		{
			std::ifstream imageFile{ imagePath };
			if (!imageFile.is_open()) break;
		}
		getTextures().addTexture(name + std::to_string(num), imagePath);
		++num;
	}
	spritesCount = num;
}

void Animation::start(sf::Sprite& sprite, float loopSec) {
	maxSec = loopSec;
	currentSec = 0.f;
	numSprite = 0;
	pSprite = &sprite;
	pSprite->setTexture(getTextures()[name + std::to_string(0)]);
}

void Animation::update(float deltaSec) {
	currentSec += deltaSec;
	if (currentSec >= maxSec) currentSec -= maxSec;
	const int newNum = static_cast<int>((currentSec * spritesCount) / maxSec);
	if (newNum != numSprite) {
		pSprite->setTexture(getTextures()[name + std::to_string(newNum)]);
	}
	numSprite = newNum;
}

void Animation::stop() {
	numSprite = -1;
}

bool Animation::isRunning() const {
	return numSprite != -1;
}
