#include "MovementPath.h"
#include "MobilityList.h"
#include "GridCell.h"

MovementPath::MovementPath() {}

MovementPath::MovementPath(MobilitySet mobility) :
	_mobility_set(mobility)
{}

MovementPath::MovementPath(MobilitySet mobility, GridCell & head) :
	_mobility_set(mobility)
{
	_path.emplace_back(0, head);
}

void MovementPath::addTail(GridCell & tail) {
	if (_path.size() == 0) {
		_path.emplace_back(0, tail);
	}
	else {
		Expects(getBack().isAdjacent(tail));
		int cost = getCost() + getBack().getEdge(tail).value().getCost(_mobility_set).value();
		_path.emplace_back(cost, tail);
	}
}

int MovementPath::getCost() const{
	if (_path.size() == 0) {
		return 0;
	}
	else return _path.back().first;
}

GridCell& MovementPath::getBack() {
	Expects(_path.size() > 0); {
		return _path.back().second;
	}
}

const GridCell& MovementPath::getBack() const{
	Expects(_path.size() > 0); {
		return _path.back().second;
	}
}