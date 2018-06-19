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

	MobilitySet getMobilityList() const;
	int getMove() const;

	bool canPass(const Unit * unit) const;
	std::optional<int> getCost(const CellEdge& edge) const;


};

