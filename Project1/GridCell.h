#pragma once
#include "Tile.h"
#include <algorithm>
#include <list>
#include <optional>
/** GridCell that composes the Map. Holds a Tile.
*/
class GridCell {
private:
	Tile _tile;
	std::list<CellEdge> _adjacent_cells;
public:
	void addAdjacentCell(GridCell* new_cell);
	void addAdjacentCell(GridCell * new_cell, MobilityList<std::optional<int>> costs);
	void removeAdjacentCell(GridCell* delete_cell);
	bool isAdjacent(GridCell* other_cell);
	std::optional<CellEdge> getEdge(GridCell * other_cell);
	Tile& getTile();
	std::vector<GridCell*> getAdjacentCells();
	std::list<CellEdge> getEdges();
};

