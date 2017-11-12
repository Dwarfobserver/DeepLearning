
#include "Hero.h"
#include "Globals.h"


void Hero::create(sf::Sprite& sprite) {
	pSprite = &sprite;
	animFall.create("fall");
	animRun.create("run");

	floor = getConfiguration().windowSize.height - 2 * 128.f;
	acceleration = 0.f;
	sprite.setPosition(getConfiguration().heroPosition - 64.f, floor);

	animRun.start(sprite);
}

void Hero::update(float deltaSec) {
	if (!isAtFloor()) {
		acceleration -= getConfiguration().gravity * deltaSec;
		pSprite->move(0, -acceleration * deltaSec);
		if (pSprite->getPosition().y > floor) {
			pSprite->setPosition(pSprite->getPosition().x, floor);
			acceleration = 0.f;
			animFall.stop();
			animRun.start(*pSprite);
		}
	}
	if (animRun.isRunning()) {
		animRun.update(deltaSec);
	}
	else {
		animFall.update(deltaSec);
	}
}

void Hero::jump() {
	if (animFall.isRunning()) return;
	
	acceleration = getConfiguration().jumpPower;
	animRun.stop();
	animFall.start(*pSprite);
}

bool Hero::isAtFloor() const {
	return acceleration == 0.f && pSprite->getPosition().y == floor;
}
