#include "Tile.h"



Tile::Tile(): _unit(nullptr), _terrain()
{
}


Tile::~Tile()
{
}
bool Tile::insertUnit(Unit* _unit) {
	if (_unit == NULL) {
		this->_unit = _unit;
		return true;
	}
	else {
		return false;
	}
}
bool Tile::removeUnit() {
	if (_unit == NULL) {
		return false;
	}
	else {
		this->_unit = NULL;
		return true;
	}
}
Terrain* Tile::getTerrain() {
	return this->_terrain;
}
void Tile::setTerrain(Terrain* _new_terrain) {
	this->_terrain = _new_terrain;
}
