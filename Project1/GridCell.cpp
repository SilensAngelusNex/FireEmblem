#include "GridCell.h"



GridCell::GridCell(): _tile()
{
}

CellEdge GridCell::getEdge(GridCell* other_cell) {
	for (std::list<CellEdge>::iterator it = _adjacent_cells.begin(); it != _adjacent_cells.end(); it++) {
		if (it->_cell == other_cell) {
			_found = true;
			return (*it);
		}
	}
	_found = false;
	return CellEdge(nullptr, -1);
}

GridCell::~GridCell()
{
}
/** Adds _new_cell to the adjacency vector
	Returns true if succesful, false if _new_cell is already in the adjacency vector
*/
bool GridCell::addAdjacentCell(GridCell* new_cell, int cost) 
{
	if (new_cell != nullptr) {
		CellEdge edge= getEdge(new_cell);
		if (_found) {
			return false;
		}
		else {
			_adjacent_cells.push_back(CellEdge(new_cell, cost));
			return true;
		}
	} else 	return false;
}

bool GridCell::removeAdjacentCell(GridCell* delete_cell)
{
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
int GridCell::getEdgeCost(GridCell* other_cell) {
	CellEdge temp = getEdge(other_cell);
	if (_found) {
		return temp._cost;
	}
	else return -1;

}