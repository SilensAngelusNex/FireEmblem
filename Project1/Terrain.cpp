#include "Terrain.h"

#include <utility>

namespace Terrain_Costs {
	MobilityCostSet plains({ 10, 10, 10, 10, 10 });
	MobilityCostSet water({ std::nullopt, std::nullopt, 10, 10, 10 });
	MobilityCostSet forest({ 20, 10, 20, 10, 10 });
	MobilityCostSet mountain({ 30, 30, 10, 10, 10 });
	MobilityCostSet wall({ std::nullopt, std::nullopt, std::nullopt, std::nullopt, 10 });
	MobilityCostSet null({ std::nullopt });
}

Terrain::Terrain(std::string name, MobilityCostSet costs) :
	_name(std::move(name)),
	_costs(costs)
{}

Terrain::Terrain() : Terrain("~NULL TERRAIN~", MobilityCostSet({ 10, 10, 10, 10, 10 })) {}

/////////////////////////////////////////////////////////////////

Terrain Terrain::TerrainFactory(TerrainType type)
{
	switch (type) {
	case (TerrainType::values::PLAINS):
		return Terrain("Plains", Terrain_Costs::plains);
		break;
	case (TerrainType::values::WATER):
		return Terrain("Water", Terrain_Costs::water);
		break;
	case (TerrainType::values::FOREST):
		return Terrain("Forest", Terrain_Costs::forest);
		break;
	case (TerrainType::values::MOUNTAIN):
		return Terrain("Mountain", Terrain_Costs::mountain);
		break;
	case (TerrainType::values::WALL):
		return Terrain("Wall", Terrain_Costs::wall);
		break;
	default:
		return Terrain("~NULL TERRAIN~", Terrain_Costs::null);
	}
}


std::string& Terrain::getName() {
	return _name;
}

MobilityCostSet Terrain::getCosts() {
	return _costs;
}

///////////////////////////////////////////////////////////////

const std::string& Terrain::getName() const {
	return _name;
}

const MobilityCostSet Terrain::getCosts() const
{
	return _costs;
}

///////////////////////////////////////////////////////////////////

bool Terrain::operator==(const Terrain & terrain) const
{
	return this->_costs == terrain._costs && this->_name == terrain._name;
}

