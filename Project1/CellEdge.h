#pragma once
class GridCell;
#include <array>
#define NUM_MOVEMENT_TYPES 2 //temp, for ground and flying
/**
Represents a Path through some tiles, basically a struct
*/
class CellEdge
{

public:
	std::array<int, NUM_MOVEMENT_TYPES> _movement_costs;
	int _cost;
	GridCell* _cell;
	CellEdge(GridCell* cell, int cost);
	bool operator==(const CellEdge & c) const;
};

