#include "GridCell.h"



GridCell::GridCell(): _tile()
{
}


GridCell::~GridCell()
{
}
/** Adds _new_cell to the adjacency vector
	Returns true if succesful, false if _new_cell is already in the adjacency vector
*/
bool GridCell::addAdjacentCell(GridCell* _new_cell) 
{
	if (std::find(_adjacent_cells.begin(), _adjacent_cells.end(), _new_cell) != _adjacent_cells.end()) {
		/* this contains that _new_cell already */
		return false;
	}
	else {
		/* _new_cell is new */
		_adjacent_cells.push_back(_new_cell);
		return true;
	}
}

bool GridCell::removeAdjacentCell(GridCell* _delete_cell)
{
	std::vector<GridCell*>::iterator contains = std::find(_adjacent_cells.begin(), _adjacent_cells.end(), _delete_cell);
	if (contains != _adjacent_cells.end()) {
		/* _adjacent_cells has the cell to delete */
		_adjacent_cells.erase(contains);
		return true;
	}
	else {
		/* _adjacent_cells does not have the cell to delete */
		return false;
	}
}
bool GridCell::isAdjacent(GridCell* _other_cell) {
	return std::find(_adjacent_cells.begin(), _adjacent_cells.end(), _other_cell) != _adjacent_cells.end();

}
