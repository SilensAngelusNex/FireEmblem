#pragma once
#include <list>
#include "MobilityList.h"
#include "EnumContainer.h"
#include "GridCell.h"
#include "PathMap.h"
#include "GridCell.h"
#include "PathBase.h"


class MovementPath :public PathBase {
private:
	MobilitySet _mobility_set;
public:
	MovementPath();
	MovementPath(MobilitySet mobility);
	MovementPath(MobilitySet mobility, GridCell& head);
	MovementPath(PathMap map, GridCell& destination);


	void push_back(GridCell & tail);

	int getCost() const;
};

