#include "Map.h"
//TODO(Torrey): Make more useful constructors, USE GRIDCELL&, Refactor into multiple classes, define move/copy constructors
Map::Map(int width, int height) : 
	_grid(width, std::vector<GridCell>(height, GridCell()))
{
	insertAdjacencies();
}
GridCell& Map::getGridCell(int x_pos, int y_pos) {
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
	removeUnit(unit);
	insertUnit(unit, destination);
}
void Map::insertUnit(Unit* new_unit, GridCell& destination) {
	Expects(!destination.getTile().hasUnit());
	_unit_to_cell.emplace(new_unit, &destination);// Map the Unit to the destination.
	destination.getTile().insertUnit(new_unit);
}
void Map::removeUnit(Unit* unit) { //Expects(unit) to exist
	Expects(_unit_to_cell.count(unit) > 0);
	_unit_to_cell[unit]->getTile().removeUnit();
	_unit_to_cell.erase(unit);
}

std::vector<GridCell*> Map::getAccesibleCells(Unit* unit) {
	PathMap map = findShortestPaths(unit);
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (auto& pair: map) {
		cells.push_back(pair.first);
	}
	return cells;
}
/* Get Cells that a unit can attack without moving
*/
std::vector<GridCell*> Map::getAttackableCells(Unit* unit) {
	return getAttackableCells(unit, _unit_to_cell.at(unit));
}
/*Get Cells a Unit could attack, if it were standing on cell
*/
std::vector<GridCell*> Map::getAttackableCells(Unit* unit, GridCell* cell) {
	const std::array<bool, 32> ranges = { false, true }; //temporary range 1 weapon range
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (int i = 0; i < ranges.size(); i++) {
		if (ranges[i]) {
			PathMap map = findShortestPaths(cell, i, MobilityList<bool>({ false, false, false, true }));
			for (auto& pair : map) {
				if (pair.second.first == i) {
					cells.push_back(pair.first);
				}
			}
		}
	}
	return cells;	
}
/*Get Cells a Unit can Attack including movement
*/
std::vector<GridCell*> Map::getAllAttackableCells(Unit* unit) {
	std::vector<GridCell*> cells = std::vector<GridCell*>();;
	std::vector<GridCell*> accesible_cells = getAccesibleCells(unit);
	for (GridCell* acc_cell : accesible_cells) {
		std::vector<GridCell*> attack_cells = getAttackableCells(unit, acc_cell);
		for (GridCell* atk_cell : attack_cells) {
			if (std::count(cells.begin(), cells.end(), atk_cell) == 0) {
				cells.push_back(atk_cell);
			}
		}
	}
	return cells;
}
/*
CellPath& Map::getShortestPath(GridCell* start, GridCell* destination) {
	findShortestPaths(start);
	if (start == destination) {
		CellPath path = CellPath(start);
		return path;
	}
	CellPath path = getShortestPath(start, _shortest_path_map.at(destination).second);
	path.insertTile(destination);
	return path;
}
*/
PathMap Map::findShortestPaths(GridCell* start) {
	return findShortestPaths(start, INT_MAX, MobilityList<bool>({true, false, false}));//
}

PathMap Map::findShortestPaths(Unit* unit) {
	return findShortestPaths(_unit_to_cell.at(unit), unit->getMobility().getMove(), unit->getMobility().getMobilityType());
}

PathMap Map::findShortestPaths(GridCell* start, int max_move, MobilityList<bool> mobility) {
	PathQueue queue = PathQueue();
	PathMap path_map = PathMap();
	path_map.try_emplace(start, std::pair<int, GridCell*>(0, start));
	queue.emplace(0, start);
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
std::vector<GridCell*> Map::getAlliedCells(GridCell* unit_cell) {
	return std::vector<GridCell*>();
}

/*std::vector<GridCell> cellsWithinWeaponRange(GridCell start) {
	return 0;
}*/
