#pragma once
#include <list>
#include "GridCell.h"
class CellPath
{
private:
		std::list<GridCell*> _tiles;
public:
	CellPath();
	CellPath(GridCell* _start_tile);
	bool insertTile(GridCell* _new_tile);
	GridCell* getTail();
	GridCell* getHead();
	int getCost();
	~CellPath();
};

