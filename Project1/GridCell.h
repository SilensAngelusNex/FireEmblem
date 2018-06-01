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

public:
	GridCell();
	~GridCell();
	bool addAdjacentCell(GridCell* new_cell, MobilityList costs);
	bool removeAdjacentCell(GridCell* new_cell);
	bool isAdjacent(GridCell* other_cell);
	CellEdge getEdge(GridCell * other_cell);
	Tile* getTile();
	std::vector<GridCell*> getAdjacentCells();
};

