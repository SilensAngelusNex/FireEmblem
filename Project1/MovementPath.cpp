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

MovementPath::MovementPath(PathMap map, GridCell & destination) {
	GridCell* curr = &destination;
	do {
		_path.emplace_front(map[*curr]);
		curr = &_path.front().second;
	} while (map[*curr].first != 0);
}


void MovementPath::addTail(GridCell & tail) {
	if (_path.size() == 0) {
		_path.emplace_back(0, tail);
	}
	else {
		Expects(back().isAdjacent(tail));
		int cost = getCost() + back().getEdge(tail).value().getCost(_mobility_set).value();
		_path.emplace_back(cost, tail);
	}
}

int MovementPath::getCost() const{
	if (_path.size() == 0) {
		return 0;
	}
	else return _path.back().first;
}

