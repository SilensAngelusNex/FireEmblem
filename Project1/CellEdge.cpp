#include "CellEdge.h"
#include "GridCell.h"
#include "Mobility.h"


CellEdge::CellEdge(GridCell& cell, MobilityList<std::optional<int>> costs) :
	_cell(cell),
	_costs(costs)
{}

std::optional<int> CellEdge::getCost(const MobilityType mobility) const {
	return _costs[mobility];
}
std::optional<int> CellEdge::getCost(const Mobility mobility) const {
	std::optional<int> cost;
	for (MobilityType mobility_type : MobilityType::list) {
		if (mobility.canPass(mobility_type, _cell.getTile()._unit)) {
			std::optional<int> edge_cost = getCost(mobility_type);
			if (edge_cost.has_value() && cost < edge_cost) { // if we can step on the tile
				cost = edge_cost.value();				
			}			
		}		
	}
	return cost;
}
std::optional<int> CellEdge::getCost(const MobilitySet mobility_type) const {
	return getCost(mobility_type, true);
}

std::optional<int> CellEdge::getCost(const MobilitySet mobility_type, bool intangible) const{
	std::optional<int> cost;
	for (MobilityType mobility : MobilityType::list) {
		if (mobility_type[mobility]) {
			std::optional<int> edge_cost = getCost(mobility);
			if (edge_cost.has_value() && canPass(intangible)) { // if we can step on the tile
				if (cost < edge_cost) { // if the cost is best found yet
					cost = edge_cost.value();
				}
			}
		}
	}
	return cost;
}

bool CellEdge::canPass(bool intangible) const{
	return intangible || !(_cell.getTile().hasUnit());
}


/**
This function allows me to use list.remove() on CellEdge. Probably a bad idea
*/
bool CellEdge::operator== (const CellEdge& c) const {
	return this->_cell == c._cell && this->_costs == c._costs;
}
