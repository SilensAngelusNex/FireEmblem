#include "Tile.h"
Tile::Tile()
	= default;
Tile::~Tile() = default;
bool Tile::insertUnit(Unit* unit) {
	if (hasUnit()) {
		return false;
	}
	
		_unit = unit;
		return true;
	
}
Unit* Tile::removeUnit() {
	if (hasUnit()) {
		Unit* temp = _unit;
		this->_unit = nullptr;
		return temp;
	}  {return nullptr;
}
}
bool Tile::hasUnit() {
	return _unit != nullptr;
}
Unit* Tile::getUnit() {
	return _unit;
}
Terrain Tile::getTerrain() {
	return this->_terrain;
}
void Tile::setTerrain(Terrain* new_terrain) {
	this->_terrain = *new_terrain;
}
