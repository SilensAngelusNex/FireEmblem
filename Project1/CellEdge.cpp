#include "CellEdge.h" 
#include "GridCell.h"


CellEdge::CellEdge(GridCell& cell, MobilityList<std::optional<int>> costs) :
	_cell(cell),
	_costs(costs)
{}

std::optional<int> CellEdge::getCost(MobilityType mobility_type) const {
	return _costs[mobility_type];
}

std::optional<int> CellEdge::getCost(MobilityList<bool> mobility_list) const {
	return getCost(mobility_list, true);
}

std::optional<int> CellEdge::getCost(Mobility mobility) const {
	std::optional<int> cost;
	for (MobilityType mobility_type : MobilityType::list) {
		if (mobility.getMobilityType()[mobility_type]) {
			std::optional<int> edge_cost = getCost(mobility_type);
			if (edge_cost.has_value() && (!_cell.getTile().hasUnit() || mobility.canPass(mobility_type, _cell.getTile()._unit))) { // if we can step on the tile
				if (cost < edge_cost) { // if the cost is best found yet
					cost = edge_cost.value();
				}
			}
		}
	}
	return cost;
}

std::optional<int> CellEdge::getCost(MobilityList<bool> mobility_list, bool intangible) const {
	std::optional<int> cost;
	for (MobilityType mobility : MobilityType::list) {
		if (mobility_list[mobility]) {
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

bool CellEdge::canPass(bool intangible) const {
	return intangible || !(_cell.getTile().hasUnit());
}


/**
This function allows me to use list.remove() on CellEdge. Probably a bad idea
*/
bool CellEdge::operator== (const CellEdge& c) const {
	return this->_cell == c._cell && this->_costs == c._costs;
}