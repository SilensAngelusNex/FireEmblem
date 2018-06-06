#include "Mobility.h"


Mobility::Mobility() :
	_movement(50),
	_mobility(MobilityList<bool>({true}))
{}
Mobility::Mobility(int move, MobilityList<bool> mobility_type) :
	_movement(move), 
	_mobility(mobility_type)
{}

const MobilityList<bool>& Mobility::getMobilityType() const
{
	return _mobility;
}

const int& Mobility::getMove() const
{
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