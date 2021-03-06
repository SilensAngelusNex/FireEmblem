#include "CellEdge.h"

#include <utility>
#include "GridCell.h"
#include "Mobility.h"


CellEdge::CellEdge(ID id, MobilityCostSet costs) :
	_id(std::move(id)),
	_costs(costs)
{}

std::optional<int> CellEdge::getCost(MobilityType mobility) const {
	return _costs[mobility];
}

std::optional<int> CellEdge::getCost(MobilitySet mobility_type) const {
	std::optional<int> cost;
	for (MobilityType mobility : MobilityType::list) {
		if (mobility_type[mobility]) {
			std::optional<int> edge_cost = getCost(mobility);
			if (!cost || edge_cost < cost) { // if the cost is best found yet
					cost = edge_cost;			
			}
		}
	}
	return cost;
}



bool CellEdge::operator== (const CellEdge& c) const {
	return this->_id == c._id && this->_costs == c._costs;
}
bool CellEdge::operator!= (const CellEdge& c) const {
	return this->_id != c._id && this->_costs != c._costs;
}

