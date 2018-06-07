#pragma once
#include <string>
#include <optional>
#include "MobilityList.h"
//TODO(Torrey): FACTORY
class Terrain {
private:
	std::string _name;
	MobilityList<std::optional<int>> _costs;
public:
	Terrain();
	std::string getName() const	{
		return _name;
	};
	MobilityList<std::optional<int>> getCosts() const{
		return _costs;
	};
};

