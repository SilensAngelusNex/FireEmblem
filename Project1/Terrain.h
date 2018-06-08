#pragma once
#include <string>
#include <optional>
#include "MobilityList.h"
//TODO(Torrey): FACTORY
enum class _TERRAIN_TYPES { PLAINS, WATER, FOREST, MOUNTAIN, WALL, ENUM_END }; //Temporary Solution
using TerrainType = Enum<_TERRAIN_TYPES>;
class Terrain {
private:
	using empty = std::optional<int>; //static const std::optional<int> empty = std::optional<int>();??
	std::string _name;
	MobilityList<std::optional<int>> _costs;

	Terrain(std::string name, MobilityList<std::optional<int>> costs);
public:
	Terrain();
	Terrain(TerrainType type);
	const std::string& getName() const;
	std::string& getName();
	const MobilityList<std::optional<int>> getCosts() const;
	MobilityList<std::optional<int>> getCosts();
	bool operator==(const Terrain & terrain) const;
};

