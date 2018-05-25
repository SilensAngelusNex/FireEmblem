#pragma once
#include "Tile.h"
#include <algorithm>
class GridCell
{
private:
	Tile _tile;
	std::vector<GridCell*> _adjacent_cells;
public:
	GridCell();
	~GridCell();
	bool addAdjacentCell(GridCell* _new_cell);
	bool removeAdjacentCell(GridCell* _new_cell);
	bool isAdjacent(GridCell* _other_cell);
};

