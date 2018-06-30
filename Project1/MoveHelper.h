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
	private MapHelper 
{
public:
	MoveHelper(GridMap& map);

	PathMap getShortestPathsMap(const Unit & unit) const;
	std::set<ID> getAccesibleCellIDs(const Unit& unit);

	std::vector<ID> getEquipedAttackIDs(const Unit & unit);
	std::vector<ID> getEquipedAttackIDs(const Unit & unit, ID pos);
	std::set<ID> getEquipableAttackIDs(const Unit & unit);
	std::set<ID> getEquipableAttackIDs(const Unit & unit, ID pos);	
	std::set<ID> getMaxEquipableAttackIDs(const Unit& unit);

	std::vector<ID> getAlliedCellIDs(const Unit & unit);
	std::vector<ID> getOtherAlliedCellIDs(const Unit & unit);

	//AdjCellPath getShortestPath(const Unit& unit,GridCell & destination);
	//AdjCellPath getShortestPath(GridCell& start, GridCell& destination);
	//AdjCellPath getShortestPath(GridCell& start, GridCell& destination, int max_move);
	//bool canWalk(Unit & unit, AdjCellPath path);
	//void walkPath(Unit& unit, AdjCellPath path);
};

