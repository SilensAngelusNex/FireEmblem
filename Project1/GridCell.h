#pragma once
#include "Tile.h"
#include <algorithm>
#include <list>
class GridCell
{

private:

	Tile _tile;
	std::list<CellEdge> _adjacent_cells;
	bool _found = false; //flag
	CellEdge getEdge(GridCell* other_cell);

public:

	GridCell();
	~GridCell();
	bool addAdjacentCell(GridCell* _new_cell, int cost);
	bool removeAdjacentCell(GridCell* _new_cell);
	bool isAdjacent(GridCell* _other_cell);
	int getEdgeCost(GridCell* _other_cell);
};

