#include "CellPath.h"



CellPath::CellPath(GridCell* start_tile) :
	_tiles({ start_tile }) {
}

CellPath CellPath::copy() {
	CellPath copy = CellPath(this->getHead());
	copy._cost = this->_cost;
	copy._tiles = this->_tiles;
	return copy;
}
void CellPath::insertTile(GridCell* new_tile) {
	if (this->getTail()->isAdjacent(new_tile)) {
		_cost += _tiles.back()->getEdge(new_tile).value().getCost(MobilityType::values::GROUNDED).value();//assume grounded for now
		_tiles.push_back(new_tile);
	}
}
GridCell* CellPath::getTail() {
	return this->_tiles.back();
}
GridCell* CellPath::getHead() {
	return this->_tiles.front();
}
int CellPath::getCost() {
	return _cost;
}
bool CellPath::operator<(const CellPath & c) const {
	return this->_cost < c._cost;
}

bool CellPath::operator>(const CellPath & c) const {
	return this->_cost > c._cost;
}

