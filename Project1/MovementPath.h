#pragma once
#include <list>
#include "MobilityList.h"
#include "EnumContainer.h"
#include "GridCell.h"
#include "CostMap.h"
#include "GridCell.h"
#include "PathBase.h"


class MovementPath :public PathBase {
private:
	MobilitySet _mobility_set;
public:
	MovementPath();
	MovementPath(MobilitySet mobility);
	MovementPath(MobilitySet mobility, GridCell& head);
	MovementPath(CostMap map, GridCell& destination);

	//Modifiers
	void push_back(GridCell & tail);

	//Element Access
	int getCost() const;
};

