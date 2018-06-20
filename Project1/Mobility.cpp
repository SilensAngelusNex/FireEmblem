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

int & Mobility::getMove() {
	return _movement;
}

MobilitySet& Mobility::getMobilitySet() {
	return _mobility;
}

int Mobility::getMove() const {
	return _movement;
}

MobilitySet Mobility::getMobilitySet() const {
	return _mobility;
}

bool Mobility::canPass(const Unit* unit) const {
	//TODO(Torrey): add skill Logic stuff
	return unit == nullptr || _owner._party->hasUnit(*unit);
}

std::optional<int> Mobility::getCost(const CellEdge & edge) const {
	std::optional<int> cost;
	for (MobilityType type : MobilityType::list) {
		if (_mobility[type]) {
			std::optional<int> edge_cost = edge.getCost(type);
			if (edge_cost &&(!cost || cost > edge_cost)) { // if we can step on the tile
				cost = edge_cost.value();
			}
		}
	}
	return cost;
}
