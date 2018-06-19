#include "Mobility.h"
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

bool Mobility::canPass(MobilityType mobility_type, const Unit* unit) const {
	return _mobility[mobility_type] && (unit == nullptr ||_owner._party->hasUnit(*unit));
}