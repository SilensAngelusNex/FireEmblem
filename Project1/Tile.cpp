#include "Tile.h"
Tile::Tile() :
	 
	_terrain()
{}
Tile::Tile(const Terrain terrain) :
	_terrain(terrain)
{}

Tile::~Tile() = default;
void Tile::insertUnit(Unit* unit) {
	//return !hasUnit() ? _unit = unit : false;
	Expects(unit != nullptr && !hasUnit());
	_unit = unit;
}
Unit* Tile::removeUnit() {
	Expects(hasUnit());
	Unit* temp = _unit;
	this->_unit = nullptr;
	return temp;
}
bool Tile::hasUnit() const{
	return _unit != nullptr;
}

bool Tile::operator==(const Tile & tile) const
{
	return this == &tile;
}

