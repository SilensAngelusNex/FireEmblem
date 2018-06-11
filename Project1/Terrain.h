#pragma once
#include <string>
#include <optional>
#include "MobilityList.h"

enum class _TERRAIN_TYPES { PLAINS, WATER, FOREST, MOUNTAIN, WALL, ENUM_END }; 
using TerrainType = Enum<_TERRAIN_TYPES>;
class Terrain {
private:
	std::string _name;
	MobilityList<std::optional<int>> _costs;

	Terrain(std::string name, MobilityList<std::optional<int>> costs);
public:
	Terrain(const Terrain& cell) = default;
	Terrain& operator=(const Terrain & edge) = default;
	Terrain(Terrain&& cell) = default;
	Terrain& operator=(Terrain&& edge) = default;

	Terrain();
	Terrain(TerrainType type);

	std::string& getName();
	MobilityList<std::optional<int>> getCosts();

	const std::string& getName() const;
	const MobilityList<std::optional<int>> getCosts() const;
	
	bool operator==(const Terrain & terrain) const;
};

