#include "Terrain.h"
Terrain::Terrain(std::string name, MobilityList<std::optional<int>> costs) :
	_name(name),
	_costs(costs)
{}

Terrain::Terrain() : Terrain("~NULL TERRAIN~", MobilityList<std::optional<int>>({ 10, 10, 10, 1, 1 })) {}

Terrain::Terrain(TerrainType type) {
	switch(type) {
	case (TerrainType::values::PLAINS) :
		Terrain("Plains", MobilityList<std::optional<int>>({ 10, 10, 10, 1, 1 }));
		break;
	case (TerrainType::values::WATER):
		Terrain("Water", MobilityList<std::optional<int>>({ empty(), 10, 10, 1, 1 }));
		break;
	case (TerrainType::values::FOREST):
		Terrain("Forest", MobilityList<std::optional<int>>({ 20, 10, 20, 1, 1 }));
		break;
	case (TerrainType::values::MOUNTAIN):
		Terrain("Mountain", MobilityList<std::optional<int>>({ 30, 10, 30, 1, 1 }));
		break;
	case (TerrainType::values::WALL):
		Terrain("Wall", MobilityList<std::optional<int>>({ empty(), empty(), empty(), empty(), 1 }));
		break;
	default:
		Terrain("~NULL TERRAIN~", MobilityList<std::optional<int>>({ 10, 10, 10, 1, 1 }));
	}
}
const std::string& Terrain::getName() const {
	return _name;
}
std::string& Terrain::getName() {
	return _name;
}
const MobilityList<std::optional<int>> Terrain::getCosts() const
{
	return _costs;
}
MobilityList<std::optional<int>> Terrain::getCosts() {
	return _costs;
}

bool Terrain::operator==(const Terrain & terrain) const
{
	return this->_costs == terrain._costs && this->_name == terrain._name;
}
