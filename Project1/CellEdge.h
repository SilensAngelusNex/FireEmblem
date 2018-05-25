#pragma once
#include "GridCell.h"
#include <array>
#define NUM_MOVEMENT_TYPES 2 //temp, for ground and flying
/**
Represents a Path through some tiles
*/
class CellEdge
{
private:

public:
	GridCell* _cell;
	std::array<int, NUM_MOVEMENT_TYPES> _movement_costs;
	CellEdge();
	~CellEdge();
};

