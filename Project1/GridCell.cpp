#include "GridCell.h"


std::optional<CellEdge> GridCell::getEdge(GridCell* other_cell) {
	for (CellEdge edge: _adjacent_cells) {
		if (edge._cell == other_cell) {
			return edge;
		}
	}
	return {};
}

/** Adds _new_cell to the adjacency vector
	Returns true if succesful, false if _new_cell is already in the adjacency vector
*/
bool GridCell::addAdjacentCell(GridCell* new_cell, MobilityList<std::optional<int>> costs) {
	if (new_cell != nullptr) {
		if (getEdge(new_cell).has_value()) {
			return false;
		}			
		_adjacent_cells.emplace_back(new_cell, costs);
		return true;
	}  {	return false;
}
}

bool GridCell::removeAdjacentCell(GridCell* delete_cell) {
	if (delete_cell == nullptr) {
		return false;
	}
	std::optional<CellEdge> edge = getEdge(delete_cell);
	if (edge.has_value()) {
		_adjacent_cells.remove(edge.value());
		return true;
	}	
		return false;
}
bool GridCell::isAdjacent(GridCell* other_cell) {
	return getEdge(other_cell).has_value();
}
Tile& GridCell::getTile() {
	return this->_tile;
}
std::vector<GridCell*> GridCell::getAdjacentCells() {
	std::vector<GridCell*> adj_cells = std::vector<GridCell*>();
	for (CellEdge edge : _adjacent_cells) {
		adj_cells.push_back(edge._cell);
	}
	return adj_cells;
}