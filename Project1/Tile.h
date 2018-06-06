#pragma once
#include "Terrain.h"
#include "CellEdge.h"
#include <vector>
#include "Unit.h"
/** Tile held within a GridCell. Has no position information to keep the implementation OO
*/
class Tile {
private:
public:
	Tile();
	~Tile();
	const Terrain _terrain;
	Unit* _unit;
	bool insertUnit(Unit* unit);
	Unit* removeUnit();
	bool hasUnit() const;
};

