#pragma once
#include <string>
#include <optional>
#include "MobilityList.h"

enum class _TERRAIN_TYPES { PLAINS, WATER, FOREST, MOUNTAIN, WALL, ENUM_END }; 
using TerrainType = Enum<_TERRAIN_TYPES>;
class Terrain {
private:
	std::string _name;
	MobilityCostSet _costs;

	Terrain(std::string name, MobilityCostSet costs);
	Terrain();
public:
	Terrain(const Terrain& cell) = default;
	Terrain& operator=(const Terrain & edge) = default;
	Terrain(Terrain&& cell) = default;
	Terrain& operator=(Terrain&& edge) = default;

	static Terrain TerrainFactory(TerrainType type);




	std::string& getName();
	MobilityCostSet getCosts();

	const std::string& getName() const;
	const MobilityCostSet getCosts() const;
	
	bool operator==(const Terrain & terrain) const;
};

