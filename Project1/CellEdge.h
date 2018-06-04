#pragma once
class GridCell;
#include <array>
#include "MobilityList.h"
/**
Represents a Path through some tiles, basically a struct
*/
class CellEdge {
	MobilityList _costs;
	MobilityList _traversable;
public:
	GridCell* _cell;
	CellEdge(GridCell* cell, MobilityList costs, MobilityList traversable);
	int getCost(MobilityType mobility);
	bool canTraverse(MobilityType mobility);
	bool operator==(const CellEdge & c) const;
};

