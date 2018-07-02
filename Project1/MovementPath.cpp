#include "MovementPath.h"
#include "MobilityList.h"
#include "GridCell.h"
#include "GridMap.h"

MovementPath::MovementPath() {}

MovementPath::MovementPath(MobilitySet mobility) :
	_mobility_set(mobility)
{}

MovementPath::MovementPath(MobilitySet mobility, GridCell & head) :
	_mobility_set(mobility)
{
	_path.emplace_back(0, head);
}

MovementPath::MovementPath(CostMap map, GridCell & destination) {
	GridCell* curr = &destination;
	while (map[*curr].first != 0) {
		_path.emplace_front(map[*curr].first, *curr);
		curr = &map[front()].second;
	} 
	_path.emplace_front(map[*curr].first, *curr);
}


void MovementPath::push_back(GridCell & tail) {
	if (empty()) {
		_path.emplace_back(0, tail);
	}
	else {
		Expects(back().isAdjacent(tail));
		int cost = getCost() + back().getEdge(tail).value().getCost(_mobility_set).value();
		_path.emplace_back(cost, tail);
	}
}

int MovementPath::getCost() const{
	if (empty()) {
		return 0;
	}
	else return _path.back().first;
}

