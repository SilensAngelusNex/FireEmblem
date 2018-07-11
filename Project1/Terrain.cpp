#include "Terrain.h"

#include <utility>

namespace Terrain_Costs {
	MobilityCostSet PLAINS({ Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST });
	MobilityCostSet WATER({ std::nullopt, std::nullopt, Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST });
	MobilityCostSet FOREST({ 2 * Terrain::BASE_COST, Terrain::BASE_COST, 2 * Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST });
	MobilityCostSet MOUNTAIN({ 3* Terrain::BASE_COST, 3 * Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST, Terrain::BASE_COST });
	MobilityCostSet WALL({ std::nullopt, std::nullopt, std::nullopt, std::nullopt, Terrain::BASE_COST });
	MobilityCostSet NULL_TERRAIN({ std::nullopt });
}

Terrain::Terrain(std::string name, MobilityCostSet costs) :
	_name(std::move(name)),
	_costs(costs)
{}

Terrain::Terrain() : Terrain("~NULL TERRAIN~", Terrain_Costs::NULL_TERRAIN) {}

/////////////////////////////////////////////////////////////////

Terrain Terrain::TerrainFactory(TerrainType type)
{
	switch (type) {
	case (TerrainType::values::PLAINS):
		return Terrain("Plains", Terrain_Costs::PLAINS);
		break;
	case (TerrainType::values::WATER):
		return Terrain("Water", Terrain_Costs::WATER);
		break;
	case (TerrainType::values::FOREST):
		return Terrain("Forest", Terrain_Costs::FOREST);
		break;
	case (TerrainType::values::MOUNTAIN):
		return Terrain("Mountain", Terrain_Costs::MOUNTAIN);
		break;
	case (TerrainType::values::WALL):
		return Terrain("Wall", Terrain_Costs::WALL);
		break;
	default:
		return Terrain("~NULL TERRAIN~", Terrain_Costs::NULL_TERRAIN);
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

