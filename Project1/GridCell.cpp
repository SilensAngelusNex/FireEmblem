#include "GridCell.h"


std::optional<CellEdge> GridCell::getEdge(GridCell* other_cell) {
	for (CellEdge edge: _adjacent_cells) {
		if (edge._cell == other_cell) {
			return edge;
		}
	}
	return {};
}

void GridCell::addAdjacentCell(GridCell * new_cell) {
	Expects(new_cell != nullptr);
	addAdjacentCell(new_cell, new_cell->getTile()._terrain.getCosts());
}

/** Adds _new_cell to the adjacency vector
	Returns true if succesful, false if _new_cell is already in the adjacency vector
*/
void GridCell::addAdjacentCell(GridCell* new_cell, MobilityList<std::optional<int>> costs) {
	Expects(new_cell != nullptr && !getEdge(new_cell).has_value());
	_adjacent_cells.emplace_back(new_cell, costs);
}

void GridCell::removeAdjacentCell(GridCell* delete_cell) {
	std::optional<CellEdge> edge = getEdge(delete_cell);
	Expects(edge.has_value());
	_adjacent_cells.remove(edge.value());
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
std::list<CellEdge> GridCell::getEdges() {
	return _adjacent_cells;
}