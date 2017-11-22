
#include "Terminal.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>


using namespace std::string_literals;

void Terminal::addCommand(
	std::string&& name,
	std::vector<char>&& args,
	std::string&& description,
	std::function<void(std::vector<int> const&)>&& f) {

	commands.emplace(std::make_pair(
		std::move(name),
		Command{ std::move(args), std::move(f), std::move(description) }
	));
}

void Terminal::executeCommand(std::string const& line) {
	std::istringstream ssline{ line };

	std::string name;
	if (!std::getline(ssline, name, ' '))
		return;

	if (name.empty())
		throw std::runtime_error{ "Invalid command (it must not begin with a space)." };

	if (name == "help") {
		printHelp();
		return;
	}
	
	const auto it = commands.find(name);
	if (it == commands.end())
		throw std::runtime_error{ "Command name unknown." };

	std::vector<std::string> argNames;
	std::vector<int> argValues;

	auto& command = it->second;
	std::string argName;
	std::string argValue;
	while (std::getline(ssline, argName, ' ')) {
		if (argName.empty()) continue;
		argNames.push_back(std::move(argName));

		if (!std::getline(ssline, argValue, ' ') || argValue.empty()) {
			argValues.push_back(1);
		}
		else try {
			argValues.push_back(std::stoi(argValue));
		}
		catch(...) {
			throw std::runtime_error{ "Command argument value could not be parsed." };
		}
	}
	assert(argNames.size() == argValues.size());

	if (argNames.size() != command.args.size())
		throw std::runtime_error{ "Wrong number of arguments for command '" + name + "'." };

	const int emptyValue = -135'468;
	std::vector<int> orderedValues(argNames.size(), emptyValue);
	for (auto i = 0u; i < argNames.size(); ++i) {
		auto& arg = argNames[i];
		if (arg.size() != 2 || arg[0] != '-')
			throw std::runtime_error{ "Invalid argument name format ('-' + 'arg letter')." };

		char letter = arg[1];
		const auto charIt = std::find(command.args.begin(), command.args.end(), letter);
		if (charIt == command.args.end())
			throw std::runtime_error{ "Unkwon argument '"s + letter + "' for command '"s + name + "'." };

		const int charPos = charIt - command.args.begin();
		if (orderedValues[charPos] != emptyValue)
			throw std::runtime_error{ "Argument '"s + letter + "' given two times."s };

		orderedValues[charPos] = argValues[i];
	}
	assert(std::find(orderedValues.begin(), orderedValues.end(), emptyValue) == orderedValues.end());

	command.f(std::move(orderedValues));
}

void Terminal::printHelp() {
	std::vector<std::string> lines;
	lines.emplace_back("Available commands :");
	for (auto& pair : commands) {
		auto& cmd = pair.second;
		auto line = "    " + pair.first;
		for (auto arg : cmd.args) {
			line += " -"s + arg;
		}
		line += " : " + cmd.description;
		lines.emplace_back(line);
	}
	for (auto& line : lines) {
		std::cout << line << '\n';
	}
}
