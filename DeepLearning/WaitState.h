
#pragma once

#include "ApplicationState.h"
#include "Terminal.h"
#include <future>


class WaitState : public ApplicationState {
public:
	WaitState();
	~WaitState() noexcept;
	void onEnter() override;
	void onExit() override;
	void onUpdate(float deltaSec) override;
	void onEvent(sf::Event const& event) override;
private:
	void setTerminalCommands();
	static void printWelcome();
	void terminalTask();

	Terminal terminal;
	std::thread terminalThread;
	std::mutex terminalLineMutex;
	std::string terminalLine;
	std::atomic_bool listenTerminal;
	std::atomic_bool lineEmpty;
};
