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
	Tile(const Terrain terrain);
	~Tile();
	const Terrain _terrain;
	Unit* _unit;
	void insertUnit(Unit* unit);
	Unit* removeUnit();
	bool hasUnit() const;

	bool operator==(const Tile& cell) const;
};

