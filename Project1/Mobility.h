#pragma once
#include "MobilityList.h"
#include "Component.h"
#include <optional>

class Unit;
class CellEdge;

class Mobility : Component<Unit> {
	
	int _movement{50};
	MobilitySet _mobility;
public:
	Mobility(Unit& owner);
	Mobility(Unit& owner, int move, MobilitySet mobility_type);

	int& getMove();
	MobilitySet& getMobilitySet();

	int getMove() const;
	MobilitySet getMobilitySet() const;

	bool canPass(const Unit * unit) const;
	std::optional<int> getCost(const CellEdge& edge) const;
	mutable bool _tired;

	bool isTired() const { return _tired; }
	void tire() const { _tired = true; };
};

