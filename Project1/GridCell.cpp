#include "GridCell.h"

GridCell::GridCell(): _tile() {
}

CellEdge GridCell::getEdge(GridCell* other_cell) {
	for (std::list<CellEdge>::iterator it = _adjacent_cells.begin(); it != _adjacent_cells.end(); it++) {
		if (it->_cell == other_cell) {
			_found = true;
			return (*it);
		}
	}
	_found = false;
	return CellEdge(nullptr, MobilityList({ -1 }), MobilityList({false}));
}

GridCell::~GridCell() {
}
/** Adds _new_cell to the adjacency vector
	Returns true if succesful, false if _new_cell is already in the adjacency vector
*/
bool GridCell::addAdjacentCell(GridCell* new_cell, MobilityList costs, MobilityList traversable) {
	if (new_cell != nullptr) {
		CellEdge edge= getEdge(new_cell);
		if (_found) {
			return false;
		}
		else {
			_adjacent_cells.push_back(CellEdge(new_cell, costs, traversable));
			return true;
		}
	} else 	return false;
}

bool GridCell::removeAdjacentCell(GridCell* delete_cell) {
	if (delete_cell == nullptr) {
		return false;
	}
	CellEdge edge = getEdge(delete_cell);
	if (_found) {
		_adjacent_cells.remove(edge);
		return true;
	}
	else {
		return false;
	}
	
}
bool GridCell::isAdjacent(GridCell* other_cell) {
	getEdge(other_cell);
	return _found;

}
Tile& GridCell::getTile() {
	return this->_tile;
}
std::vector<GridCell*> GridCell::getAdjacentCells() {
	std::vector<GridCell*> _adj_cells = std::vector<GridCell*>();
	for (std::list<CellEdge>::iterator it = _adjacent_cells.begin(); it != _adjacent_cells.end(); it++) {
		_adj_cells.push_back(it->_cell);
	}
	return _adj_cells;
}