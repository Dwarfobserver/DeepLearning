
#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <functional>
#include <mutex>


class Window {
public:
	void run();
	void invoke(std::function<void()>&& f);

	Window() = default;
	Window(Window&&) = delete; // Remove move & copy ctor & assignements
private:
	sf::RenderWindow sfmlWindow;
	std::queue<std::function<void()>> tasksQueue;
	std::mutex tasksMutex;

	void update();
	void render();
	void handleInputs();
};
