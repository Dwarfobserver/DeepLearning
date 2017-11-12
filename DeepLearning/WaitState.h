
#pragma once
#include "ApplicationState.h"


class WaitState : public ApplicationState {
public:
	void onEnter() override;
	void onExit() override;
	void onUpdate(float deltaSec) override;
	void onEvent(sf::Event const& event) override;
};
