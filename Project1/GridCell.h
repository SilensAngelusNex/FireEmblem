#pragma once
#include "Tile.h"
#include <algorithm>
#include <list>
/** GridCell that composes the Map. Holds a Tile.
*/
class GridCell {
private:

	Tile _tile;
	std::list<CellEdge> _adjacent_cells;
	bool _found = false; //flag
	CellEdge getEdge(GridCell* other_cell);

public:
	GridCell();
	~GridCell();
	bool addAdjacentCell(GridCell* new_cell, int cost);
	bool removeAdjacentCell(GridCell* new_cell);
	bool isAdjacent(GridCell* other_cell);
	int getEdgeCost(GridCell* other_cell);
	Tile* getTile();
	std::vector<GridCell*> getAdjacentCells();
};

