#include "UnitPath.h"
#include "MobilityList.h"
#include "GridCell.h"
#include "GridMap.h"
#include "Unit.h"

/*
UnitPath::UnitPath(const Unit& unit) :
	PathBase(*unit.getMobility().getLocation()),
	_unit(unit)
{}
*/

UnitPath::UnitPath(const Unit& unit, const GridCell & head) :
	PathBase(head),
	_unit(unit)
{}

UnitPath::UnitPath(const Unit& unit, CostMap map, const GridCell & destination) :
	PathBase<const GridCell>(map._origin),
	_unit(unit)
{
	const GridCell* curr = &destination;
	while (map[*curr].first != 0) {
		auto temp = *curr;
		_path.emplace_front(map[*curr].first, *curr);
		curr = &map[_path.front().second].second;
	} 
}


void UnitPath::push_back(const GridCell & tail) {
	if (tail == _head) {
		_path.clear();
		return;
	}
	if(contains(tail)) {
		trimPath(tail);
		return;
	}
	const GridCell* back_cell = &_head;
	if (!empty()) {
		back_cell = &back();
	}
	Expects(back_cell->isAdjacent(tail));
	int cost = getCost() + back_cell->getEdge(tail).value().getCost(_unit.getMobility().getMobilitySet()).value();
	Expects(cost <= _unit.getMobility().getMove());
	_path.emplace_back(cost, tail);	
}

int UnitPath::getCost() const{
	if (empty()) {
		return 0;
	}
	return _path.back().first;
}

UnitPath & UnitPath::operator+(const UnitPath & path) {
	Expects(_unit == path._unit && back() == path._head);
	for (auto& pair : path) {
		push_back(pair.second);
	}
	return *this;
}

