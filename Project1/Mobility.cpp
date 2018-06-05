#include "Mobility.h"



Mobility::Mobility(int move, MobilityList<bool> mobilityType) :
	_movement(move), 
	_mobility(mobilityType)
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