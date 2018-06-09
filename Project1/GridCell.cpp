#include "GridCell.h"
GridCell::GridCell(Tile tile) :
	_tile(tile)
{}
std::optional<CellEdge> GridCell::getEdge(const GridCell& other_cell) {
	for (CellEdge edge: _adjacent_cells) {
		if (&edge._cell == &other_cell) {
			return edge;
		}
	}
	return {};
}
const std::optional<CellEdge> GridCell::getEdge(const GridCell& other_cell) const {
	for (CellEdge edge : _adjacent_cells) {
		if (&edge._cell == &other_cell) {
			return edge;
		}
	}
	return {};
}

void GridCell::addAdjacentCell(GridCell & new_cell)
{
	addAdjacentCell(new_cell, new_cell.getTile()._terrain.getCosts());
}

/** Adds _new_cell to the adjacency vector
*/
void GridCell::addAdjacentCell(GridCell& new_cell, MobilityList<std::optional<int>> costs) {
	Expects(!getEdge(new_cell).has_value());
	_adjacent_cells.emplace_back(new_cell, costs);
}

void GridCell::removeAdjacentCell(const GridCell& delete_cell) {
	std::optional<CellEdge> edge = getEdge(delete_cell);
	Expects(edge.has_value());
	_adjacent_cells.remove(edge.value());
}
bool GridCell::isAdjacent(const GridCell& other_cell) const{
	return getEdge(other_cell).has_value();
}
const Tile& GridCell::getTile() const{
	return _tile;
}
Tile& GridCell::getTile() {
	return _tile;
}
std::vector<GridCell*> GridCell::getAdjacentCells() {
	std::vector<GridCell*> adj_cells = std::vector<GridCell*>();
	for (CellEdge edge : _adjacent_cells) {
		adj_cells.push_back(&edge._cell);
	}
	return adj_cells;
}
std::list<CellEdge> GridCell::getEdges() const{
	return _adjacent_cells;
}
std::list<CellEdge> GridCell::getEdges() {
	return _adjacent_cells;
}
bool GridCell::operator==(const GridCell & cell) const {
	return this->_tile == cell._tile && this->_adjacent_cells == cell._adjacent_cells;
}
