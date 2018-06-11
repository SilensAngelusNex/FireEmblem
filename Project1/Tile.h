#pragma once
#include "Terrain.h"
class Unit;
/** Tile held within a GridCell. Has no position information to keep the implementation OO
*/
class Unit;
class Tile {
private:
public:
	Tile(const Tile& cell) = default;
	Tile(Tile&& cell) = default;

	Tile();
	Tile(Terrain terrain);
	~Tile();

	const Terrain _terrain;
	Unit* _unit;

	void insertUnit(Unit* unit);
	Unit* removeUnit();
	bool hasUnit() const;

	bool operator==(const Tile& tile) const;
};

