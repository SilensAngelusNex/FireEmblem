#pragma once
#include "Terrain.h"
//TODO(Torrey): Either combine this with GridCell in some way, or remove this class 
class Unit;
/** Tile held within a GridCell. Has no position information to keep the implementation OO
*/
class Tile {
private:
public:
	Tile(const Tile& cell) = default;
	Tile(Tile&& cell) = default;

	Tile();
	Tile(TerrainType terrain);
	~Tile();

	const Terrain _terrain;
	Unit* _unit;


	bool operator==(const Tile& tile) const;
};

