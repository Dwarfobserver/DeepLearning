
#pragma once
#include <string>
#include <vector>


namespace ground {
	enum type {
		bricks,
		lava
	};
	std::vector<type> parse(std::string const& file);
}
