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
	findShortestPaths(_unit_to_cell.at(unit), unit->getStats().getAttribs()[AttribType::values::MOV], unit->getStats().getMobilityType());
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (std::map<GridCell*, prev_cost_pair>::iterator it = _shortest_path_map.begin(); it != _shortest_path_map.end(); it++) {
		cells.push_back(it->first);
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
	CellPath path = getShortestPath(start, _shortest_path_map.at(destination)._prev_cell);
	path.insertTile(destination);
	return path;
}
*/
void Map::findShortestPaths(GridCell* start) {
	std::priority_queue<prev_cost_pair> queue = std::priority_queue<prev_cost_pair>();
	prev_cost_pair first;
	first._cost = 0;
	first._prev_cell = start;
	_shortest_path_map.clear();
	_shortest_path_map.insert(std::pair<GridCell*, prev_cost_pair>(start, first));
	queue.push(first);
	findShortestPaths(queue, -1, _MOBILITY_TYPES::GROUNDED);//assume grounded for now
}
void Map::findShortestPaths(GridCell* start, int max_move, MobilityType mobility) {
	std::priority_queue<prev_cost_pair> queue = std::priority_queue<prev_cost_pair>();
	prev_cost_pair first;
	first._cost = 0;
	first._prev_cell = start;
	_shortest_path_map.clear();
	_shortest_path_map.insert(std::pair<GridCell*, prev_cost_pair>(start, first));
	queue.push(first);
	findShortestPaths(queue, max_move, mobility);
}
void Map::findShortestPaths(std::priority_queue<prev_cost_pair>& queue, int max_move, MobilityType mobility) {
	if (queue.size() == 0) {
		return;
	}
	prev_cost_pair top = queue.top();
	queue.pop();
	std::vector<GridCell*> adj_cells = top._prev_cell->getAdjacentCells();
	for (std::vector<GridCell*>::iterator it = adj_cells.begin(); it != adj_cells.end(); it++) {
		if (top._prev_cell->getEdge(*it).canTraverse(mobility) && !(*it)->getTile().hasUnit()) { //if we can step on this tile
			int cost = top._cost + top._prev_cell->getEdge(*it).getCost(mobility);
			if (_shortest_path_map.count(*it) == 0) {//no shortest path found
				if (cost <= max_move || max_move == -1) {
					prev_cost_pair new_element_insert;
					prev_cost_pair new_element_push;
					new_element_push._prev_cell = *it;
					new_element_insert._prev_cell = top._prev_cell;
					new_element_push._cost = cost;
					new_element_insert._cost = new_element_push._cost;
					queue.push(new_element_push);
					_shortest_path_map.insert(std::pair<GridCell*, prev_cost_pair>(*it, new_element_insert));
				}
			}
			else if (cost < _shortest_path_map.at(*it)._cost) { //found a new shortest path
				prev_cost_pair& modify_element = _shortest_path_map.at(*it);
				modify_element._cost = top._cost + top._prev_cell->getEdge(*it).getCost(mobility);
				modify_element._prev_cell = top._prev_cell;
				prev_cost_pair new_element_push;
				new_element_push._prev_cell = *it;
				new_element_push._cost = cost;
				queue.push(new_element_push);
			}
		}
	}
	findShortestPaths(queue, max_move, mobility);
}
std::vector<GridCell*> Map::getAlliedCells(GridCell* unit_cell) {
	return std::vector<GridCell*>();
}

/*std::vector<GridCell> cellsWithinWeaponRange(GridCell start) {
	return 0;
}*/
