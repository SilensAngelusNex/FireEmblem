#pragma once
#include "MobilityList.h"
#include "Component.h"

class Unit;

class Mobility : Component<Unit> {
	int _movement{50};
	MobilitySet _mobility;
public:
	Mobility(Unit& owner);
	Mobility(Unit& owner, int move, MobilitySet mobility_type);

	const MobilitySet& getMobilityList() const;
	const int& getMove() const;

	MobilitySet& getMobilityList();
	int& getMove();

	bool canPass(MobilityType mobility_type, const Unit * unit) const;



};

