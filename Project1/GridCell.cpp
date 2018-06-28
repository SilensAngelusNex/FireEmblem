#include "GridCell.h"
#include "CellEdge.h"
#include "Grid.h"
#include <utility>

std::optional<CellEdge> GridCell::getEdge(const GridCell& other_cell) {
	for (CellEdge edge: _adjacent_cells) {
		if (edge._id == other_cell._id) {
			return edge;
		}
	}
	return {};
}
const std::optional<CellEdge> GridCell::getEdge(const GridCell& other_cell) const {
	for (CellEdge edge : _adjacent_cells) {
		if (edge._id == other_cell._id) {
			return edge;
		}
	}
	return {};
}

std::optional<CellEdge> GridCell::getEdge(ID other_cell_id) {
	for (CellEdge edge : _adjacent_cells) {
		if (edge._id == other_cell_id) {
			return edge;
		}
	}
	return {};
}
const std::optional<CellEdge> GridCell::getEdge(ID other_cell_id) const {
	for (CellEdge edge : _adjacent_cells) {
		if (edge._id == other_cell_id) {
			return edge;
		}
	}
	return {};
}

GridCell::GridCell(TerrainType terrain, ID id) :
	_terrain(Terrain::TerrainFactory(terrain)),
		_id(id)
{}

void GridCell::addAdjacentCell(GridCell & new_cell)
{
	addAdjacentCell(new_cell._id, new_cell._terrain.getCosts());
}

/** Adds _new_cell to the adjacency vector
*/
void GridCell::addAdjacentCell(ID new_cell, MobilityCostSet costs) {
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
bool GridCell::isAdjacent(const GridCell & other_cell, MobilityType mobility) const
{
	return isAdjacent(other_cell) && getEdge(other_cell).value().getCost(mobility).has_value();
}
bool GridCell::isAdjacent(const GridCell & other_cell, MobilitySet mobility) const
{
	return isAdjacent(other_cell) && getEdge(other_cell).value().getCost(mobility).has_value();
}
const Terrain& GridCell::getTerrain() const{
	return _terrain;
}
Terrain& GridCell::getTerrain() {
	return _terrain;
}
std::vector<ID> GridCell::getAdjacentCellIDs() {
	auto adj_cells = std::vector<ID>();
	for (CellEdge edge : _adjacent_cells) {
		adj_cells.push_back(edge._id);
	}
	return adj_cells;
}
const std::vector<ID> GridCell::getAdjacentCellIDs() const {
	auto adj_cells = std::vector<ID>();
	for (CellEdge edge : _adjacent_cells) {
		adj_cells.push_back(edge._id);
	}
	return adj_cells;
}
const std::list<CellEdge> GridCell::getEdges() const{
	return _adjacent_cells;
}
std::list<CellEdge> GridCell::getEdges() {
	return _adjacent_cells;
}
bool GridCell::operator==(const GridCell & cell) const {
	return this == &cell;
}

bool GridCell::operator!=(const GridCell & cell) const {
	return this != &cell;
}
