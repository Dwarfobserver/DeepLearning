
#include "WaitState.h"
#include "Globals.h"
#include "Application.h"
#include <thread>
#include <iostream>


WaitState::WaitState() {
	getTextures().addTexture(
		"wait_background",
		getConfiguration().resourcesRoot + "wait_background.png");
	sprites.emplace_back();
	sprites.back().setTexture(getTextures()["wait_background"]);

	setTerminalCommands();
	printWelcome();

	std::cin.clear();
	terminalLine.clear();
	listenTerminal.store(true);
	lineEmpty.store(true);
	std::cout << '>';

	terminalThread = std::thread{[this] { terminalTask(); }};
}

WaitState::~WaitState() noexcept {
	listenTerminal.store(false);
	lineEmpty.store(true);
	std::cout << "Press enter to exit\n";
	terminalThread.join();
}

void WaitState::onEnter() {
	std::lock_guard<std::mutex> lock{ terminalLineMutex };
	terminalLine.clear();
}

void WaitState::onExit() {}

void WaitState::onUpdate(float deltaSec) {
	if (!lineEmpty.load()) {
		std::string line;
		{
			std::lock_guard<std::mutex> lock{ terminalLineMutex };
			line = terminalLine;
		}
		try {
			terminal.executeCommand(line);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
		}
		std::cout << '>';
		lineEmpty.store(true);
	}
}

void WaitState::onEvent(sf::Event const& event) {
	if (event.type == sf::Event::KeyPressed) {
		getApplication().setState("play");
	}
}

void WaitState::setTerminalCommands() {
	terminal.addCommand(
		"quit", {},
		"Quit the application.",
		[](std::vector<int> const& values) {

		getApplication().quit();
	});
	terminal.addCommand(
		"show", { 'n' },
		"Show the genome designed by number 'n'.",
		[](std::vector<int> const& values) {

		if (values.empty())
			throw std::runtime_error{ "The genome number must be given." };

		std::cout << "<Imagine here the genome '" + std::to_string(values[0]) + "'>\n";
	});
}

void WaitState::printWelcome() {
	std::cout << "\n          +---------------+";
	std::cout << "\n          | Deep Learning |";
	std::cout << "\n          +---------------+";
	std::cout << "\n";
	std::cout << "\nPress a touch in the window to play.";
	std::cout << "\nWrite 'help' to get terminal commands.";
	std::cout << "\n";
}

void WaitState::terminalTask() {
	std::string line;
	while (true) {
		std::getline(std::cin, line);

		if (!listenTerminal.load())
			return;
		{
			std::lock_guard<std::mutex> lock{ terminalLineMutex };
			terminalLine = line;
		}
		lineEmpty.store(false);
		while (!lineEmpty.load()) {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1ms);
		}
	}
}
