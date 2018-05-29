#pragma once
#include <list>
#include "GridCell.h"
//TODO: ADD MULTIPLE PATH TYPES, currently only accepts adjacent, grounded paths.
class CellPath
{
private:
	std::list<GridCell*> _tiles;
	int _cost = 0;
public:
	CellPath(GridCell* start_tile);
	CellPath copy();
	bool insertTile(GridCell* new_tile);
	GridCell* getTail();
	GridCell* getHead();
	int getCost();
	bool operator<(const CellPath & c) const;
	bool operator>(const CellPath & c) const;
};

