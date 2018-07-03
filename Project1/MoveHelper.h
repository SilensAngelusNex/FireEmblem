#pragma once

#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "GridCell.h"
#include "ID.h"

class Unit;
class GridCell;

class MoveHelper : 	public MapHelper {
public:
	MoveHelper(GridMap& map);

	std::set<ID> getAccesibleCellIDs(const Unit& unit) const;

	std::vector<ID> getEquipedAttackIDs(const Unit & unit) const;
	std::vector<ID> getEquipedAttackIDs(const Unit & unit, ID pos) const;
	std::set<ID> getEquipableAttackIDs(const Unit & unit) const;
	std::set<ID> getEquipableAttackIDs(const Unit & unit, ID pos) const;	
	std::set<ID> getMoveEquipableAttackIDs(const Unit& unit) const;

	std::vector<ID> getEquipedAssistIDs(const Unit & unit) const;
	std::vector<ID> getEquipedAssistIDs(const Unit & unit, ID pos) const;
	std::set<ID> getEquipableAssistIDs(const Unit & unit) const;
	std::set<ID> getEquipableAssistIDs(const Unit & unit, ID pos) const;
	std::set<ID> getMoveEquipableAssistIDs(const Unit& unit) const;


	std::vector<ID> getAlliedCellIDs(const Unit & unit) const;
	std::vector<ID> getOtherAlliedCellIDs(const Unit & unit) const;
};