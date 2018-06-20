#include "Tile.h"
#include "Unit.h"
Tile::Tile() :
	 
	_terrain()
{}
Tile::Tile(const Terrain terrain) :
	_terrain(terrain)
{}

Tile::~Tile() = default;

bool Tile::operator==(const Tile & tile) const
{
	return this == &tile;
}

