#include "CellEdge.h"



CellEdge::CellEdge(GridCell* cell, MobilityList costs, MobilityList traversable): _cell(cell), _costs(costs), _traversable(traversable) {
}

int CellEdge::getCost(MobilityType mobility)
{
	return _costs[mobility];
}

bool CellEdge::canTraverse(MobilityType mobility)
{
	return bool(_traversable[mobility]);
}

/**
This function allows me to use list.remove() on CellEdge. Probably a bad idea
*/
bool CellEdge::operator== (const CellEdge& c) const {
	bool result;
	result = (this->_cell == c._cell && this->_costs == c._costs);
	return result;
}