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
Party& Grid::getParty(Unit & unit) {
	return unit._party->getParty(Passkey<Grid>());
}
const GridCell& Grid::getGridCell(int x_pos, int y_pos) const{
	Expects(x_pos > 0 && y_pos > 0 && x_pos < _grid.size() && y_pos < _grid[0].size());
	return _grid[x_pos][y_pos];
}
const Party& Grid::getParty(Unit & unit) const {
	return unit._party->getParty(Passkey<Grid>());
}
///////////////////////////////////////////////////////////
PathMap Grid::findShortestPaths(GridCell& start) {
	return std::as_const(*this).findShortestPaths(start);
}

PathMap Grid::findShortestPaths(GridCell & start, Mobility & mobility) {
	return std::as_const(*this).findShortestPaths(start, mobility);
}

PathMap Grid::findShortestPaths(GridCell& start, int max_move, MobilitySet mobility) {
	return std::as_const(*this).findShortestPaths(start, max_move, mobility);
}

PathMap Grid::findShortestPaths(GridCell & start, int max_move, MobilitySet mobility, bool intangible) {
	return std::as_const(*this).findShortestPaths(start, max_move, mobility, intangible);
}
const PathMap Grid::findShortestPaths(GridCell& start) const {
	return findShortestPaths(start, INT_MAX, MobilitySet({ true, }), false);
};
const PathMap Grid::findShortestPaths(GridCell& start, int max_move, MobilitySet mobility, bool intangible) const {
	PathQueue queue = PathQueue(comp);
	PathMap path_map = PathMap();
	path_map.emplace(&start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		CellCost top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if ((!hasUnit(edge._cell) || intangible) && cost.has_value()) {
				cost = top.first + cost.value();
				if (cost.value() <= max_move && (path_map.count(&(edge._cell)) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}

const PathMap Grid::findShortestPaths(GridCell& start,  Mobility& mobility) const {
	PathQueue queue = PathQueue(comp);
	PathMap path_map = PathMap();
	path_map.emplace(&start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		CellCost top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = mobility.getCost(edge);
			const Unit* unit = nullptr;
			if (hasUnit(edge._cell)) {
				unit = &(*this)[edge._cell];
			}
			if (mobility.canPass(unit) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= mobility.getMove() && (path_map.count(&(edge._cell)) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}
const PathMap Grid::findShortestPaths(GridCell& start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return findShortestPaths(start, max_move, mobility, intangible);
}

CellPath Grid::getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilitySet mobility) {
	PathMap path_map = findShortestPaths(start, max_move, mobility);
	std::list<CellRef> path = std::list<CellRef>();
	path.push_front(destination);
	while (!(start == path.front().get())) {
		path.push_front(path_map.at(&path.front().get()).second);
	}
	return CellPath(path, mobility);
}

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