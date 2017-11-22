
#include "PlayState.h"
#include "Globals.h"
#include "Application.h"


PlayState::PlayState() {
	getTextures().addTexture("bricks", getConfiguration().resourcesRoot + "bricks.png");
	getTextures().addTexture("lava", getConfiguration().resourcesRoot + "lava.png");
	ground = ground::parse(getConfiguration().resourcesRoot + "ground.txt");
}

void PlayState::onEnter() {
	distance = 0.f;
	finished = false;

	for (auto i = 0u; i < ground.size(); ++i) {
		std::string texture;
		switch (ground[i]) {
			case ground::bricks:
				texture = "bricks";
			break;
			case ground::lava:
				texture = "lava";
			break;
		default:;
		}
		sf::Sprite sprite;
		sprite.setPosition(128.f * i, getConfiguration().windowSize.height - 128.f);
		sprite.setTexture(getTextures()[texture]);
		sprites.push_back(std::move(sprite));
	}

	sprites.emplace_back();
	hero.create(sprites.back());
}

void PlayState::onExit() {
	sprites.clear();
}

void PlayState::onUpdate(float deltaSec) {
	if (finished) return;

	const float oldDistance = distance;
	distance += deltaSec * getConfiguration().scrollingSpeed;

	for (auto i = 0u; i < ground.size(); ++i) {
		sprites[i].move((oldDistance - distance), 0);
	}

	hero.update(deltaSec);
	if (hero.isAtFloor()) {
		const int i = static_cast<int>((distance + getConfiguration().heroPosition) / 128.f);
		if (ground[i] == ground::lava) {
			getApplication().setState("wait");
		}
	}

	if (distance - getConfiguration().heroPosition > ground.size() * 128) finished = true;
}

void PlayState::onEvent(sf::Event const& event) {
	if (!finished) {
		if (event.type == sf::Event::KeyPressed) {
			hero.jump();
		}
	}
	else {
		if (event.type == sf::Event::KeyPressed) {
			getApplication().setState("wait");
		}
	}
}
