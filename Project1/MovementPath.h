#pragma once
#include <list>
#include "MobilityList.h"
#include "EnumContainer.h"
#include "GridCell.h"
#include "CostMap.h"
#include "GridCell.h"
#include "PathBase.h"

class Unit;

class MovementPath :public PathBase {
public:
	const Unit& _unit;
	MovementPath(const Unit& unit);
	MovementPath(const Unit& unit, GridCell& head);
	MovementPath(const Unit& unit, CostMap map, GridCell& destination);

	//Modifiers
	void push_back(GridCell & tail);

	//Element Access
	int getCost() const;
	MovementPath& operator+(const MovementPath& path);
};

