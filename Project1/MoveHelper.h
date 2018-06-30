#pragma once

#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "reference_logic.h"
#include "GridCell.h"
#include "ID.h"

class Unit;
class GridCell;

class MoveHelper : 
	public MapHelper 
{
public:
	MoveHelper(GridMap& map);
	std::vector<ID> getAccesibleCellIDs(const Unit& unit);
	PathMap getShortestPathsMap(const Unit & unit) const;

	std::vector<ID> getAttackableCellIDs(const Unit & unit);
	std::vector<ID> getAttackableCellIDs(const Unit & unit, ID cell);
	std::vector<ID> getAllAttackableCellIDs(const Unit & unit);
	std::vector<ID> getAlliedCellIDs(const Unit & unit);

	std::vector<ID> getOtherAlliedCellIDs(const Unit & unit);

	//AdjCellPath getShortestPath(const Unit& unit,GridCell & destination);
	//AdjCellPath getShortestPath(GridCell& start, GridCell& destination);
	//AdjCellPath getShortestPath(GridCell& start, GridCell& destination, int max_move);
	//bool canWalk(Unit & unit, AdjCellPath path);
	//void walkPath(Unit& unit, AdjCellPath path);
};

