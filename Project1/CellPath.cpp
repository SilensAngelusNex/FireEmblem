#include "CellPath.h"



CellPath::CellPath(GridCell* _start_tile) : _tiles({ _start_tile })
{

}

CellPath CellPath::copy() {
	CellPath copy = CellPath(this->getHead());
	copy._cost = this->_cost;
	copy._tiles = this->_tiles;
	return copy;
}
bool CellPath::insertTile(GridCell* _new_tile)
{
	if (this->getTail()->isAdjacent(_new_tile)) {
		_cost += _tiles.back()->getEdgeCost(_new_tile);
		_tiles.push_back(_new_tile);
		return true;
	}
	return false;
}
GridCell* CellPath::getTail()
{
	return this->_tiles.back();
}
GridCell* CellPath::getHead()
{
	return this->_tiles.front();
}
int CellPath::getCost()
{
	return _cost;
}
bool CellPath::operator<(const CellPath & c) const {
	return this->_cost < c._cost;
}

bool CellPath::operator>(const CellPath & c) const {
	return this->_cost > c._cost;
}

