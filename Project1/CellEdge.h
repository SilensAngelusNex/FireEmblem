#pragma once
class GridCell;
#include <array>
#include "MobilityList.h"
#include <optional>
/**
Represents an Edge to a GridCell, basically a struct
*/
class CellEdge {
	 const MobilityList<std::optional<int>> _costs;
public:
	GridCell* _cell;
	CellEdge(GridCell* cell, MobilityList<std::optional<int>> costs);
	int getCost(MobilityType mobility);
	bool canTraverse(MobilityType mobility);
	bool operator==(const CellEdge & c) const;
};

