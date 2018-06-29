#pragma once

#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "reference_logic.h"
#include "GridCell.h"

class Unit;
class GridCell;

class MoveHelper : 
	public MapHelper 
{
public:
	MoveHelper(GridMap& map);
	std::vector<CellRef> getAccesibleCells(const Unit& unit);
	PathMap findShortestPaths(const Unit & unit) const;
	//AdjCellPath getShortestPath(const Unit& unit,GridCell & destination);
	//AdjCellPath getShortestPath(GridCell& start, GridCell& destination);
	//AdjCellPath getShortestPath(GridCell& start, GridCell& destination, int max_move);

	std::vector<CellRef> getAttackableCells(const Unit & unit);
	std::vector<CellRef> getAttackableCells(const Unit & unit, GridCell & cell);
	std::vector<CellRef> getAllAttackableCells(const Unit & unit);
	std::vector<CellRef> getAlliedCells(const Unit & unit);

	std::vector<CellRef> getOtherAlliedCells(const Unit & unit);

	//bool canWalk(Unit & unit, AdjCellPath path);

	//void walkPath(Unit& unit, AdjCellPath path);
};

