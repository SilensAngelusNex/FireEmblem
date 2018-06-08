#include "Map.h"
//TODO(Torrey): Make more useful constructors, USE GRIDCELL&, Refactor into multiple classes, define move/copy constructors
Map::Map(int width, int height) : 
	_grid(width, std::vector<GridCell>(height, GridCell()))
{
	insertAdjacencies();
}
GridCell& Map::getGridCell(int x_pos, int y_pos) {
	Expects(x_pos > 0 && y_pos > 0 && x_pos < _grid.size() && y_pos < _grid[0].size());
	return _grid[x_pos][y_pos];
}
/**Inserts Eucildian Adjacencies
*/
void Map::insertAdjacencies() {
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
void Map::moveUnit(GridCell& start, GridCell& destination) {
	Expects(start.getTile().hasUnit() && !destination.getTile().hasUnit());
	Unit* unit = start.getTile()._unit;
	removeUnit(*unit);
	insertUnit(*unit, destination);
}
void Map::insertUnit(Unit& new_unit, GridCell& destination) {
	Expects(!destination.getTile().hasUnit());
	_unit_to_cell.emplace(&new_unit, &destination);// Map the Unit to the destination.
	destination.getTile().insertUnit(&new_unit);
}
void Map::removeUnit(Unit& unit) { //Expects(unit) to exist
	Expects(_unit_to_cell.count(&unit) > 0);
	_unit_to_cell[&unit]->getTile().removeUnit();
	_unit_to_cell.erase(&unit);
}

GridCell& Map::getGridCell(Unit & unit) {
	return *_unit_to_cell[&unit];
}

PathMap Map::findShortestPaths(GridCell& start) {
	return findShortestPaths(start, INT_MAX, MobilityList<bool>({true, false, false}));//
}

PathMap Map::findShortestPaths(GridCell& start, int max_move, MobilityList<bool> mobility) {
	PathQueue queue = PathQueue();
	PathMap path_map = PathMap();
	path_map.try_emplace(&start, CellCost(0, &start));
	queue.emplace(0, &start);
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];

	while (!queue.empty()) {
		std::pair<int, GridCell*> top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second->getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if (cost.has_value()) {
				cost = top.first + cost.value();
				if (cost.value() <= max_move && (path_map.count(&(edge._cell)) == 0 || cost.value() < path_map[&edge._cell].first)) {
					path_map.insert_or_assign(&edge._cell, std::pair<int, GridCell*>(cost.value(), top.second));
					queue.emplace(cost.value(), &edge._cell);
				}
			}
		}
	}
	return path_map;
}
std::vector<GridCell*> Map::getAlliedCells(GridCell& unit_cell) {
	return std::vector<GridCell*>();
}
