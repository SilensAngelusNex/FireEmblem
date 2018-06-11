#pragma once
#include "MobilityList.h"
class Mobility
{
	int _movement{50};
	MobilityList<bool> _mobility;
public:
	Mobility();
	Mobility(int move, MobilityList<bool> mobility_type);

	const MobilityList<bool>& getMobilityType() const;
	const int& getMove() const;

	MobilityList<bool>& getMobilityType();
	int& getMove();

};

