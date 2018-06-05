#include "Map.h"
Map::Map(int width, int height) : 
	_grid(width, std::vector<GridCell>(height, GridCell()))
{
	insertAdjacencies();
}
GridCell & Map::getGridCell(int x_pos, int y_pos) {
	return _grid[x_pos][y_pos];
}
void Map::insertAdjacencies() {
	auto width = static_cast<int>(_grid.size());
	auto height = static_cast<int>(_grid[0].size());
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x > 0) {
				_grid[x][y].addAdjacentCell(&(_grid[x - 1][y]), MobilityList<std::optional<int>>({ 10, 10, 10}));
			} if (x < width - 1) {
				_grid[x][y].addAdjacentCell(&(_grid[x + 1][y]), MobilityList<std::optional<int>>({ 10, 10, 10 }));
			}if (y > 0) {
				_grid[x][y].addAdjacentCell(&(_grid[x][y - 1]), MobilityList<std::optional<int>>({ 10, 10, 10 }));
			} if (y < height - 1) {
				_grid[x][y].addAdjacentCell(&(_grid[x][y + 1]), MobilityList<std::optional<int>>({ 10, 10, 10 }));
			}
		}
	}
}
bool Map::moveUnit(GridCell* start, GridCell* destination) {
	if (!start->getTile().hasUnit() || destination->getTile().hasUnit()) {
		return false;
	}
	
		_unit_to_cell.at(start->getTile().getUnit()) = destination; // Map the Unit to the destination.
		destination->getTile().insertUnit(start->getTile().removeUnit()); // Put the Unit in the destination Tile
		return true;
	
}
bool Map::insertUnit(Unit* new_unit, GridCell* destination) {
	if (destination->getTile().hasUnit()) {
		return false;
	}
	
		_unit_to_cell.insert(std::pair<Unit*, GridCell*>(new_unit, destination));// Map the Unit to the destination.
		destination->getTile().insertUnit(new_unit);
		return true;
	
}
void Map::removeUnit(Unit* unit) { //throws exceptions if the space is not empty.
	_unit_to_cell.at(unit)->getTile().removeUnit();
	_unit_to_cell.erase(unit);
}

std::vector<GridCell*> Map::getAccesibleCells(Unit* unit) {
	std::map<GridCell*, std::pair<int, GridCell*>> map = findShortestPaths(_unit_to_cell.at(unit), unit->getMobility().getMove(), unit->getMobility().getMobilityType());
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (auto& pair: map) {
		cells.push_back(pair.first);
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
std::map<GridCell*, std::pair<int, GridCell*>> Map::findShortestPaths(GridCell* start) {
	std::priority_queue<std::pair<int, GridCell*>> queue = std::priority_queue<std::pair<int, GridCell*>>();
	std::map<GridCell*, std::pair<int, GridCell*>> path_map = std::map<GridCell*, std::pair<int, GridCell*>>();
	path_map.try_emplace(start, std::pair<int, GridCell*>(0, start));
	queue.emplace(0, start);
	findShortestPaths(queue, path_map, -1, MobilityList<bool>({true, false, false}));//assume grounded for now
	return path_map;
}
std::map<GridCell*, std::pair<int, GridCell*>> Map::findShortestPaths(GridCell* start, int max_move, MobilityList<bool> mobility) {
	std::priority_queue<std::pair<int, GridCell*>> queue = std::priority_queue<std::pair<int, GridCell*>>();
	std::map<GridCell*, std::pair<int, GridCell*>> path_map = std::map<GridCell*, std::pair<int, GridCell*>>();
	path_map.try_emplace(start, std::pair<int, GridCell*>(0, start));
	queue.emplace(0, start);
	findShortestPaths(queue, path_map, max_move, mobility);
	return path_map;
}
std::map<GridCell*, std::pair<int, GridCell*>> Map::findShortestPaths(std::priority_queue<std::pair<int, GridCell*>>& queue, std::map<GridCell*, std::pair<int, GridCell*>>& path_map, int max_move, MobilityList<bool> mobility_types) {
	if (queue.empty()) {
		return path_map;
	}
	std::pair<int, GridCell*> top = queue.top();
	queue.pop();
	std::list<CellEdge> adj_edges = top.second->getEdges();
	for ( auto& edge: adj_edges) {
		int cost;
		bool found_cost = false;
		for (MobilityType mobility : MobilityType::list) {
			if (mobility_types[mobility] && edge.canTraverse(mobility) && !edge._cell->getTile().hasUnit()) { // if we can step on the tile
				if (!found_cost || cost > top.first + edge.getCost(mobility).value()) { // if the cost is best found yet 
					found_cost = true;
					cost = top.first + edge.getCost(mobility).value();
				}
			}
		}
		if (found_cost && path_map.count(edge._cell) == 0) {//no shortest path found
			if (cost <= max_move || max_move == -1) {
				queue.emplace(cost, edge._cell);
				path_map.try_emplace(edge._cell, std::pair<int, GridCell*>(cost, top.second));
			}
		}
		else if (found_cost && cost < path_map.at(edge._cell).first) { //found a new shortest path
					std::pair<int, GridCell*>& modify_element = path_map.at(edge._cell);
					modify_element.first = cost;
					modify_element.second = top.second;
					queue.emplace(cost, edge._cell);
		}
	}
	return findShortestPaths(queue, path_map, max_move, mobility_types);
}
std::vector<GridCell*> Map::getAlliedCells(GridCell* unit_cell) {
	return std::vector<GridCell*>();
}

/*std::vector<GridCell> cellsWithinWeaponRange(GridCell start) {
	return 0;
}*/
