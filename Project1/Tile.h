#pragma once
#include "Terrain.h"
#include "CellEdge.h"
#include <vector>
#include "Unit.h"
/** Tile held within a GridCell. Has no position information to keep the implementation OO
*/
class Tile
{
private:
	
	Terrain* _terrain; //Not sure how i want to do terrain yet, this is placeholder i think it should be some kind of pointer to some static object.
	Unit* _unit = nullptr;
public:
	Tile();
	~Tile();
	bool insertUnit(Unit* unit);
	Unit* removeUnit();
	bool hasUnit();
	Unit * getUnit();
	Terrain* getTerrain();
	void setTerrain(Terrain* new_terrain);

};

