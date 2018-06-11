#pragma once
#include "MobilityList.h"
#include "Component.h"

class Unit;

class Mobility : Component<Unit> {
	int _movement{50};
	MobilityList<bool> _mobility;
public:
	Mobility(Unit& owner);
	Mobility(Unit& owner, int move, MobilityList<bool> mobility_type);

	const MobilityList<bool>& getMobilityType() const;
	const int& getMove() const;

	MobilityList<bool>& getMobilityType();
	int& getMove();

	bool canPass(MobilityType mobility_type, const Unit * unit) const;



};

