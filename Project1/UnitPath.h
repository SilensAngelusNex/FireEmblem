#pragma once
#include "PathBase.h"
#include "CostMap.h"

class Unit;
class UnitPath :public PathBase<const GridCell> {
public:
	const Unit& _unit;
	//UnitPath(const Unit& unit);
	UnitPath(const Unit& unit, const GridCell& head);
	UnitPath(const Unit& unit, CostMap map, const GridCell& destination);

	//Modifiers
	void push_back(const GridCell & tail);

	//Element 
	int getCost() const;
	UnitPath& operator+(const UnitPath& path);
};

