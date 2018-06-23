#include "Tile.h"
#include "Unit.h"
#include "Terrain.h"
Tile::Tile() :
	_terrain(Terrain::TerrainFactory(TerrainType::values::ENUM_END))
{}
Tile::Tile(TerrainType terrain) :
	_terrain(Terrain::TerrainFactory(terrain))
{}

Tile::~Tile() = default;

bool Tile::operator==(const Tile & tile) const
{
	return this == &tile;
}

