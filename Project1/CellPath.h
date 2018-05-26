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
	CellPath();
	CellPath(GridCell* _start_tile);
	bool insertTile(GridCell* _new_tile);
	GridCell* getTail();
	GridCell* getHead();
	int getCost();
	~CellPath();
};

