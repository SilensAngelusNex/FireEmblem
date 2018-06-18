#include "Mobility.h"
#include "Unit.h"


Mobility::Mobility(Unit& owner) : 
	Component<Unit>(owner),
	_mobility(MobilityList<bool>({true}))
{}
Mobility::Mobility(Unit& owner, int move, MobilityList<bool> mobility_type) :
	Component<Unit>(owner),
	_movement(move), 
	_mobility(mobility_type)
{}

const MobilityList<bool>& Mobility::getMobilityType() const
{
	return _mobility;
}

const int& Mobility::getMove() const {
	return _movement;
}

MobilityList<bool>& Mobility::getMobilityType()
{
	return _mobility;
}

int& Mobility::getMove()
{
	return _movement;
}

bool Mobility::canPass(MobilityType mobility_type, const Unit* unit) const {
	return _mobility[mobility_type] && (unit == nullptr ||_owner._party->hasUnit(*unit));
}