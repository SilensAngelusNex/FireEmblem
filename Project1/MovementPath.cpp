#include "MovementPath.h"
#include "MobilityList.h"
#include "GridCell.h"
#include "GridMap.h"
#include "Unit.h"

MovementPath::MovementPath(const Unit& unit, GridCell & head) :
	_unit(unit),
	_head(head)
{}

MovementPath::MovementPath(const Unit& unit, CostMap map, GridCell & destination) :
	_unit(unit),
	_head(map._origin)
{
	GridCell* curr = &destination;
	while (map[*curr].first != 0) {
		_path.emplace_front(map[*curr].first, *curr);
		curr = &map[front()].second;
	} 
}


void MovementPath::push_back(GridCell & tail) {
	const GridCell* back_cell = &_head;
	if (!empty()) {
		back_cell = &back();
	}
	Expects(back_cell->isAdjacent(tail));
	int cost = getCost() + back_cell->getEdge(tail).value().getCost(_unit.getMobility().getMobilitySet()).value();
	Expects(cost <= _unit.getMobility().getMove());
	_path.emplace_back(cost, tail);	
}

int MovementPath::getCost() const{
	if (empty()) {
		return 0;
	}
	else return _path.back().first;
}

//Should this be const?
MovementPath & MovementPath::operator+(const MovementPath & path) {
	Expects(_unit == path._unit);
	for (auto& pair : path) {
		push_back(pair.second);
	}
	return *this;
}

