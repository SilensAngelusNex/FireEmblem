#include "CellEdge.h"
#include "GridCell.h"
#include "Mobility.h"


CellEdge::CellEdge(GridCell& cell, MobilityCostSet costs) :
	_cell(cell),
	_costs(costs)
{}

std::optional<int> CellEdge::getCost(MobilityType mobility) const {
	return _costs[mobility];
}

std::optional<int> CellEdge::getCost(MobilitySet mobility_type) const {
	return getCost(mobility_type, true);
}

std::optional<int> CellEdge::getCost(MobilitySet mobility_type, bool intangible) const{
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

bool CellEdge::operator== (const CellEdge& c) const {
	return this->_cell == c._cell && this->_costs == c._costs;
}
bool CellEdge::operator!= (const CellEdge& c) const {
	return this->_cell != c._cell && this->_costs != c._costs;
}

