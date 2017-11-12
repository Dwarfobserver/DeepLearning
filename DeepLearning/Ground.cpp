
#include "Ground.h"
#include <fstream>
#include <iostream>


std::vector<ground::type> ground::parse(std::string const& file) {
	std::ifstream dataFile{ file };
	if (!dataFile.is_open())
		throw std::logic_error{ "The data file " + file + " does not exists." };

	std::vector<type> result;
	char c;
	while (dataFile.get(c)) {
		switch (c) {
		case '-':
			result.emplace_back(bricks);
			break;
		case '_':
			result.emplace_back(lava);
			break;
		default:
			throw std::logic_error{ "The data file must only contain '-' and '_' characters." };
		}
	}
	return result;
}
