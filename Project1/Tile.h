#pragma once
#include "Terrain.h"
#include "CellEdge.h"
#include <vector>
#include "Unit.h"
class Tile
{
private:
	
	Terrain* _terrain; //Not sure how i want to do terrain yet, this is placeholder i think it should be some kind of pointer to some static object.
	Unit* _unit;
public:
	Tile();
	~Tile();
	bool insertUnit(Unit* _unit);
	bool removeUnit();
	Terrain* getTerrain();
	void setTerrain(Terrain* _new_terrain);

};

