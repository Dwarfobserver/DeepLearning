
#pragma once

#include <functional>
#include <vector>
#include <map>


class Terminal {
public:
	Terminal() = default;

	void addCommand(
		std::string&& name,
		std::vector<char>&& args,
		std::string&& description,
		std::function<void(std::vector<int> const&)>&& f);
	void executeCommand(std::string const& line);
private:
	void printHelp();

	struct Command {
		std::vector<char> args;
		std::function<void(std::vector<int> const&)> f;
		std::string description;
	};
	char cinBuffer[256];
	std::map<std::string, Command> commands;
};
