#include "Map.h"



Map::Map(int _width, int _height) : _grid(_width, std::vector<GridCell>(_height, GridCell()))
{
}

bool Map::moveUnit(GridCell* start, GridCell* destination) {
	if (!start->getTile()->hasUnit() || destination->getTile()->hasUnit()) {
		return false;
	}
	else {
		destination->getTile()->insertUnit(start->getTile()->removeUnit());
		return true;
	}
}
std::vector<GridCell*> Map::getAccesibleCells(GridCell* start) {
	findShortestPaths(start);
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (std::map<GridCell*, prev_cost_pair>::iterator it = _shortest_path_map.begin(); it != _shortest_path_map.end(); it++) {
		if (it->second._cost < 100) { //assume 100 move for now and that there are no negative edges (else we might need to go over our max move temporarily to reach a node)
			cells.push_back(it->first);
		}
	}
	return cells;
}
CellPath Map::getShortestPath(GridCell* start, GridCell* destination) {
	if (start != _shortest_path_start) {
		findShortestPaths(start);
	}
	if (start == destination) {
		return CellPath(start);
	}
	CellPath path = getShortestPath(start, _shortest_path_map.at(destination)._prev_cell);
	path.insertTile(destination);
	return path;
}
void Map::findShortestPaths(GridCell* start) {
	if (start == _shortest_path_start) { //need another flag for if the map is changed
		return;
	}
	std::priority_queue<prev_cost_pair> queue = std::priority_queue<prev_cost_pair>();
	prev_cost_pair first;
	first._cost = 0;
	first._prev_cell = start;
	_shortest_path_map.clear();
	_shortest_path_map.insert(std::pair<GridCell*, prev_cost_pair>(start, first));
	queue.push(first);
	findShortestPaths(queue);
}
void Map::findShortestPaths(std::priority_queue<prev_cost_pair>& queue) {
	if (queue.size() == 0) {
		return;
	}
	prev_cost_pair top = queue.top();
	queue.pop();
	std::vector<GridCell*> _adj_cells = top._prev_cell->getAdjacentCells();
	for (std::vector<GridCell*>::iterator it = _adj_cells.begin(); it != _adj_cells.end(); it++) {
		if (_shortest_path_map.find(*it) == _shortest_path_map.end()) {//no shortest path found
			prev_cost_pair new_element_insert;
			prev_cost_pair new_element_push;
			new_element_push._prev_cell = *it;
			new_element_insert._prev_cell = top._prev_cell;
			new_element_push._cost = top._cost + top._prev_cell->getEdgeCost(*it);
			new_element_insert._cost = new_element_push._cost;
			queue.push(new_element_push);
			_shortest_path_map.insert(std::pair<GridCell*, prev_cost_pair>(top._prev_cell, new_element_insert));
		}
		else if (top._cost + top._prev_cell->getEdgeCost(*it) < _shortest_path_map.at(*it)._cost) { //found a new shortest path
			prev_cost_pair modify_element = _shortest_path_map.at(*it);
			modify_element._cost = top._cost + top._prev_cell->getEdgeCost(*it);
			modify_element._prev_cell = top._prev_cell;
			prev_cost_pair new_element_push;
			new_element_push._prev_cell = *it;
			new_element_push._cost = top._cost + top._prev_cell->getEdgeCost(*it);
			queue.push(new_element_push);
		}
	}

}

/*std::vector<GridCell> cellsWithinWeaponRange(GridCell start) {
	return 0;
}*/
