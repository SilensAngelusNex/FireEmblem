#include "Map.h"
Map::Map(int width, int height) : _grid(width, std::vector<GridCell>(height, GridCell())) {
	insertAdjacencies();
}
GridCell & Map::getGridCell(int x_pos, int y_pos)
{
	return _grid[x_pos][y_pos];
}
void Map::insertAdjacencies() {
	int width = (int)_grid.size();
	int height = (int)_grid[0].size();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x > 0) {
				_grid[x][y].addAdjacentCell(&(_grid[x - 1][y]), MobilityList({ 10, 10, 10 }), MobilityList({true, true, true}));
			} if (x < width - 1) {
				_grid[x][y].addAdjacentCell(&(_grid[x + 1][y]), MobilityList({ 10, 10, 10 }), MobilityList({ true, true, true }));
			}if (y > 0) {
				_grid[x][y].addAdjacentCell(&(_grid[x][y - 1]), MobilityList({ 10, 10, 10 }), MobilityList({ true, true, true }));
			} if (y < height - 1) {
				_grid[x][y].addAdjacentCell(&(_grid[x][y + 1]), MobilityList({ 10, 10, 10 }), MobilityList({ true, true, true }));
			}
		}
	}
}
bool Map::moveUnit(GridCell* start, GridCell* destination) {
	if (!start->getTile().hasUnit() || destination->getTile().hasUnit()) {
		return false;
	}
	else {
		_unit_to_cell.at(start->getTile().getUnit()) = destination; // Map the Unit to the destination.
		destination->getTile().insertUnit(start->getTile().removeUnit()); // Put the Unit in the destination Tile
		return true;
	}
}
bool Map::insertUnit(Unit* new_unit, GridCell* destination) {
	if (destination->getTile().hasUnit()) {
		return false;
	}
	else {
		_unit_to_cell.insert(std::pair<Unit*, GridCell*>(new_unit, destination));// Map the Unit to the destination.
		destination->getTile().insertUnit(new_unit);
		return true;
	}
}
void Map::removeUnit(Unit* unit) { //throws exceptions if the space is not empty.
	_unit_to_cell.at(unit)->getTile().removeUnit();
	_unit_to_cell.erase(unit);
}

std::vector<GridCell*> Map::getAccesibleCells(Unit* unit) {
	std::map<GridCell*, std::pair<int, GridCell*>> map = findShortestPaths(_unit_to_cell.at(unit), unit->getStats().getAttribs()[AttribType::values::MOV], unit->getStats().getMobilityType());
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
	queue.emplace(std::pair<int, GridCell*>(0, start));
	findShortestPaths(queue, path_map, -1, _MOBILITY_TYPES::GROUNDED);//assume grounded for now
	return path_map;
}
std::map<GridCell*, std::pair<int, GridCell*>> Map::findShortestPaths(GridCell* start, int max_move, MobilityType mobility) {
	std::priority_queue<std::pair<int, GridCell*>> queue = std::priority_queue<std::pair<int, GridCell*>>();
	std::map<GridCell*, std::pair<int, GridCell*>> path_map = std::map<GridCell*, std::pair<int, GridCell*>>();
	path_map.try_emplace(start, std::pair<int, GridCell*>(0, start));
	queue.emplace(std::pair<int, GridCell*>(0, start));
	findShortestPaths(queue, path_map, max_move, mobility);
	return path_map;
}
std::map<GridCell*, std::pair<int, GridCell*>> Map::findShortestPaths(std::priority_queue<std::pair<int, GridCell*>>& queue, std::map<GridCell*, std::pair<int, GridCell*>>& path_map, int max_move, MobilityType mobility) {
	if (queue.size() == 0) {
		return path_map;
	}
	std::pair<int, GridCell*> top = queue.top();
	queue.pop();
	std::vector<GridCell*> adj_cells = top.second->getAdjacentCells();
	for ( auto& cell: adj_cells) {
		if (top.second->getEdge(cell).canTraverse(mobility) && !cell->getTile().hasUnit()) { //if we can step on this tile
			int cost = top.first + top.second->getEdge(cell).getCost(mobility);
			if (path_map.count(cell) == 0) {//no shortest path found
				if (cost <= max_move || max_move == -1) {
					queue.emplace(std::pair<int, GridCell*>(cost, cell));
					path_map.try_emplace(cell, std::pair<int, GridCell*>(cost, top.second));
				}
			}
			else if (cost < path_map.at(cell).first) { //found a new shortest path
				std::pair<int, GridCell*>& modify_element = path_map.at(cell);
				modify_element.first = top.first + top.second->getEdge(cell).getCost(mobility);
				modify_element.second = top.second;
				queue.emplace(std::pair<int, GridCell*>(cost, cell));
			}
		}
	}
	return findShortestPaths(queue, path_map, max_move, mobility);
}
std::vector<GridCell*> Map::getAlliedCells(GridCell* unit_cell) {
	return std::vector<GridCell*>();
}

/*std::vector<GridCell> cellsWithinWeaponRange(GridCell start) {
	return 0;
}*/
