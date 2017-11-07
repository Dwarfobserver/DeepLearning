
#include "Window.h"


namespace {
	using lock_t = std::lock_guard<std::mutex>;
}

void Window::run() {
	sfmlWindow.create({ 1200, 800 }, "Deep Learning");
	sfmlWindow.setVerticalSyncEnabled(true);

	while (sfmlWindow.isOpen()) {
		update();
		render();
		handleInputs();
	}
}

void Window::invoke(std::function<void()>&& f) {
	lock_t lock{ tasksMutex };
	tasksQueue.push(move(f));
}

void Window::update() {
	lock_t lock{ tasksMutex };
	while (!tasksQueue.empty()) {
		tasksQueue.front()();
		tasksQueue.pop();
	}
}

void Window::render() {
	sfmlWindow.clear();

	sfmlWindow.display();
}

void Window::handleInputs() {
	sf::Event event{};
	while (sfmlWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			sfmlWindow.close();
		}

	}
}
