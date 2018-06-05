#pragma once
class GridCell;
#include <array>
#include "MobilityList.h"
/**
Represents a Path through some tiles, basically a struct
*/
class CellEdge {
	MobilityList<int> _costs;
	MobilityList<bool> _traversable;
public:
	GridCell* _cell;
	CellEdge(GridCell* cell, MobilityList<int> costs, MobilityList<bool> traversable);
	int getCost(MobilityType mobility);
	bool canTraverse(MobilityType mobility);
	bool operator==(const CellEdge & c) const;
};

