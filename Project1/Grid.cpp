#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "Mobility.h"
#include "GridCell.h"
//#include "CellPath.h"
#include "CellEdge.h"
//TODO(Torrey): Make more useful constructors
Grid::Grid(int width, int height) {
	for (int i = 0; i < width; i++) {
		_grid.emplace_back();
		for (int j = 0; j < height; j++) {
			_grid[i].emplace_back(TerrainType::values::PLAINS, ID(i, j));
		}
	}
	insertAdjacencies();
}

Grid::Grid(int width, int height, std::vector<PartyData> data) {
	for (int i = 0; i < width; i++) {
		_grid.emplace_back();
		for (int j = 0; j < height; j++) {
			_grid[i].emplace_back(TerrainType::values::PLAINS, ID(i, j));
		}
	}
	insertAdjacencies();
	for (auto& party : data) {
		insertParty(party);
	}
}

Unit* Grid::getUnit(const GridCell& key) {
	return  hasUnit(key) ? _cell_to_unit[&key] : nullptr;
}
const Unit* Grid::getUnit(const GridCell& key) const{
	return  hasUnit(key) ? _cell_to_unit.at(&key) : nullptr;
}

Unit* Grid::getUnit(ID index) {
	return  hasUnit(index) ? _cell_to_unit.at(&(*this)[index]) : nullptr;
}
GridCell * Grid::getCell(const Unit & key)
{
	return  hasUnit(key) ? _unit_to_cell[&key] : nullptr;
}

const GridCell * Grid::getCell(const Unit & key) const
{
	return  hasUnit(key) ? _unit_to_cell.at(&key) : nullptr;
}
const Unit* Grid::getUnit(ID index) const {
	return  hasUnit(index) ? _cell_to_unit.at(&(*this)[index]) : nullptr;
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
	Expects(hasUnit(start) && !hasUnit(destination));	
	Unit* unit = &(*this)[start];
	removeUnit(*unit);
	insertUnit(*unit, destination);
}
void Grid::insertUnit(Unit& new_unit, GridCell& destination) {
	Expects(!hasUnit(destination) && !hasUnit(new_unit)); 
	_unit_to_cell.emplace(&new_unit, &destination);// Grid the Unit to the destination.
	_cell_to_unit.emplace(&destination, &new_unit);
}

void Grid::moveUnit(ID start, ID destination) {
	Expects(hasUnit(start) && !hasUnit(destination));
	Unit* unit = getUnit(start);
	removeUnit(*unit);
	insertUnit(*unit, destination);
}

void Grid::insertUnit(Unit& new_unit, ID destination) {
	Expects(!hasUnit(destination) && !hasUnit(new_unit));
	_unit_to_cell.emplace(&new_unit, &(*this)[destination]);// Grid the Unit to the destination.
	_cell_to_unit.emplace(&(*this)[destination], &new_unit);
}



void Grid::removeUnit(Unit& unit) {
	Expects(hasUnit(unit));
	_cell_to_unit.erase(_unit_to_cell[&unit]);
	_unit_to_cell.erase(&unit);
}
/////////////////////////////////////////////////////////////

bool Grid::hasUnit(const GridCell& key) const{
	return _cell_to_unit.count(&key) > 0;
}
bool Grid::hasUnit(const Unit& key) const{
	return _unit_to_cell.count(&key) > 0;
}

bool Grid::hasUnit(ID index) const {
	return _cell_to_unit.count(&(*this)[index]) > 0;
}

///////////////////////////////////////////////////////////
Unit& Grid::operator[](const GridCell& index) {
	Expects(hasUnit(index));
	return *_cell_to_unit[&index];
}
ID Grid::operator[](const Unit& index) {
	Expects(hasUnit(index));
	return _unit_to_cell[&index]->_id;
}
GridCell & Grid::operator[](ID index) {
	return _grid[index.first][index.second];
}
Grid::GridRow Grid::operator[](size_t index) {
	return GridRow(_grid[index]);
}
const ID Grid::operator[](const Unit& index) const {
	Expects(hasUnit(index));
	return _unit_to_cell.at(&index)->_id;
}
Grid::constGridRow Grid::operator[](size_t index) const {
	return constGridRow(_grid.at(index));
}
const Unit& Grid::operator[](const GridCell& index) const {
	Expects(hasUnit(index));
	return *_cell_to_unit.at(&index);
}

const GridCell& Grid::operator[](ID index) const{
	return _grid[index.first][index.second];
}


