#include "CellEdge.h"



CellEdge::CellEdge(GridCell* cell, int cost): _cell(cell), _cost(cost)
{
}


CellEdge::~CellEdge()
{
}
/**
This function allows me to use list.remove() on CellEdge. Probably a bad idea
*/
bool CellEdge::operator== (const CellEdge& c) const
{
	bool result;
	result = (this->_cell == c._cell && this->_cost == c._cost);
	return result;
}