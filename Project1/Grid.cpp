#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "GridCell.h"
#include "CellPath.h"
#include "CellEdge.h"
//TODO(Torrey): Make more useful constructors, USE GRIDCELL&, Refactor into multiple classes, define move/copy constructors
Grid::Grid(int width, int height) : 
	_grid(width, std::vector<GridCell>(height, GridCell()))
{
	insertAdjacencies();
}

Grid::Grid(int width, int height, std::vector<PartyData> data) : 
	_grid(width, std::vector<GridCell>(height, GridCell()))
{
	insertAdjacencies();
	for (auto& party : data) {
		insertParty(party);
	}
}

Unit* Grid::getUnit(const GridCell & index) {
	return  hasUnit(index) ? _cell_to_unit[&index] : nullptr;
}
const Unit* Grid::getUnit(const GridCell & index) const{
	return  hasUnit(index) ? _cell_to_unit.at(&index) : nullptr;
}

/**Inserts Eucildian Adjacencies
*/
void Grid::insertAdjacencies() {
	auto width = static_cast<int>(_grid.size());
	auto height = static_cast<int>(_grid[0].size());
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x > 0) {
				_grid[x][y].addAdjacentCell(_grid[x - 1][y]);
			} if (x < width - 1) {
				_grid[x][y].addAdjacentCell(_grid[x + 1][y]);
			}if (y > 0) {
				_grid[x][y].addAdjacentCell(_grid[x][y - 1]);
			} if (y < height - 1) {
				_grid[x][y].addAdjacentCell(_grid[x][y + 1]);
			}
		}
	}
}
void Grid::insertParty(PartyData data) {
	_parties.emplace_back(data);
}
////////////////////////////////////////////////////////////
void Grid::moveUnit(GridCell& start, GridCell& destination) {
	Expects(hasUnit(start));

	Expects(!hasUnit(destination));
	
	Unit* unit = &(*this)[start];
	removeUnit(*unit);
	insertUnit(*unit, destination);
}
void Grid::insertUnit(Unit& new_unit, GridCell& destination) {
	Expects(!hasUnit(destination) && !hasUnit(new_unit)); 
	_unit_to_cell.emplace(&new_unit, &destination);// Grid the Unit to the destination.
	_cell_to_unit.emplace(&destination, &new_unit);
}

void Grid::removeUnit(Unit& unit) {
	Expects(hasUnit(unit));
	_cell_to_unit.erase(_unit_to_cell[&unit]);
	_unit_to_cell.erase(&unit);
}
/////////////////////////////////////////////////////////////
GridCell& Grid::getGridCell(int x_pos, int y_pos) {
	Expects(x_pos > 0 && y_pos > 0 && x_pos < _grid.size() && y_pos < _grid[0].size());
	return _grid[x_pos][y_pos];
}
bool Grid::hasUnit(const GridCell& index) const{
	return _cell_to_unit.count(&index) > 0;
}
bool Grid::hasUnit(const Unit& index) const{
	return _unit_to_cell.count(&index) > 0;
}

const GridCell& Grid::getGridCell(int x_pos, int y_pos) const{
	Expects(x_pos > 0 && y_pos > 0 && x_pos < _grid.size() && y_pos < _grid[0].size());
	return _grid[x_pos][y_pos];
}

///////////////////////////////////////////////////////////


Unit& Grid::operator[](const GridCell& index) {
	Expects(hasUnit(index));
	return *_cell_to_unit[&index];
}
GridCell& Grid::operator[](const Unit& index) {
	Expects(hasUnit(index));
	return *_unit_to_cell[&index];
}
const GridCell& Grid::operator[](const Unit& index) const {
	Expects(hasUnit(index));
	return *_unit_to_cell.at(&index);
}
const Unit& Grid::operator[](const GridCell & index) const {
	Expects(hasUnit(index));
	return *_cell_to_unit.at(&index);
}