#include "CellPath.h"


CellPath::CellPath()
{

}
CellPath::CellPath(GridCell* _start_tile) : _tiles({ _start_tile })
{

}
bool CellPath::insertTile(GridCell* _new_tile)
{
	if (this->getTail()->isAdjacent(_new_tile)) {
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

}


CellPath::~CellPath()
{
}
