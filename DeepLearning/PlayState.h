
#pragma once

#include "ApplicationState.h"
#include "Ground.h"
#include "Hero.h"


class PlayState : public ApplicationState {
public:
	PlayState();
	void onEnter() override;
	void onExit() override;
	void onUpdate(float deltaSec) override;
	void onEvent(sf::Event const& event) override;
private:
	Hero hero;
	std::vector<ground::type> ground;

	float distance;
	bool finished;
};
