#pragma once
#include "PathBase.h"
#include "CostMap.h"

class Unit;
class MovementPath :public PathBase {
public:
	const Unit& _unit;
	MovementPath(const Unit& unit);
	MovementPath(const Unit& unit, const GridCell& head);
	MovementPath(const Unit& unit, CostMap map, const GridCell& destination);

	//Modifiers
	void push_back(const GridCell & tail);

	//Element 
	int getCost() const;
	MovementPath& operator+(const MovementPath& path);
};

