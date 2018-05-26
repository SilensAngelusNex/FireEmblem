#pragma once
class GridCell;
#include <array>
#define NUM_MOVEMENT_TYPES 2 //temp, for ground and flying
/**
Represents a Path through some tiles
*/
class CellEdge
{

public:
	std::array<int, NUM_MOVEMENT_TYPES> _movement_costs;
	GridCell* _cell;
	CellEdge();
	~CellEdge();
};

