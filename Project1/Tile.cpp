#include "Tile.h"
Tile::Tile() :
	 
	_terrain()
{}

Tile::~Tile() = default;
bool Tile::insertUnit(Unit* unit) {
	return (!hasUnit()) ? (_unit = unit) : nullptr;
}
Unit* Tile::removeUnit() {
	if (hasUnit()) {
		Unit* temp = _unit;
		this->_unit = nullptr;
		return temp;
	}  
		return nullptr;	
}
bool Tile::hasUnit() const{
	return _unit != nullptr;
}

