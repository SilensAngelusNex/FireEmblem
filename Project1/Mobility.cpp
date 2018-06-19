#include "Mobility.h"
#include "CellEdge.h"
#include "GridCell.h"
#include "Unit.h"


Mobility::Mobility(Unit& owner) : 
	Component<Unit>(owner),
	_mobility(MobilitySet({true}))
{}
Mobility::Mobility(Unit& owner, int move, MobilitySet mobility_type) :
	Component<Unit>(owner),
	_movement(move), 
	_mobility(mobility_type)
{}

const MobilitySet& Mobility::getMobilityList() const {
	return _mobility;
}

const int& Mobility::getMove() const {
	return _movement;
}

MobilitySet& Mobility::getMobilityList() {
	return _mobility;
}

int& Mobility::getMove() {
	return _movement;
}

bool Mobility::canPass(const Unit* unit) const {
	//TODO(Torrey): add skill Logic stuff
	return unit == nullptr || _owner._party->hasUnit(*unit);
}

std::optional<int> Mobility::getCost(const CellEdge & edge) const {
	std::optional<int> cost;
	for (MobilityType type : MobilityType::list) {
		std::optional<int> edge_cost = edge.getCost(type);
		if (_mobility[type] && canPass(edge._cell.getTile()._unit) && edge_cost.has_value() && (cost > edge_cost || !cost.has_value())) { // if we can step on the tile
			cost = edge_cost.value();
		}
	}
	return cost;
}
