#include "CellEdge.h"



CellEdge::CellEdge(GridCell* cell, MobilityList<std::optional<int>> costs) :
	_cell(cell), 
	_costs(costs)
{}

int CellEdge::getCost(MobilityType mobility)
{
	return _costs[mobility].value();
}

bool CellEdge::canTraverse(MobilityType mobility)
{
	return bool(_costs[mobility].has_value());
}

/**
This function allows me to use list.remove() on CellEdge. Probably a bad idea
*/
bool CellEdge::operator== (const CellEdge& c) const {
	bool result;
	result = (this->_cell == c._cell && this->_costs == c._costs);
	return result;
}