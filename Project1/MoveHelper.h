#pragma once

#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "reference_logic.h"
#include "GridCell.h"
#include "ID.h"

class Unit;
class GridCell;

class MoveHelper : 	private MapHelper {
public:
	MoveHelper(GridMap& map);

	PathMap getShortestPathsMap(const Unit & unit) const;
	std::set<ID> getAccesibleCellIDs(const Unit& unit);

	std::vector<ID> getEquipedAttackIDs(const Unit & unit);
	std::vector<ID> getEquipedAttackIDs(const Unit & unit, ID pos);
	std::set<ID> getEquipableAttackIDs(const Unit & unit);
	std::set<ID> getEquipableAttackIDs(const Unit & unit, ID pos);	
	std::set<ID> getMaxEquipableAttackIDs(const Unit& unit);

	std::vector<ID> getEquipedAssistIDs(const Unit & unit);
	std::vector<ID> getEquipedAssistIDs(const Unit & unit, ID pos);
	std::set<ID> getEquipableAssistIDs(const Unit & unit);
	std::set<ID> getEquipableAssistIDs(const Unit & unit, ID pos);
	std::set<ID> getMaxEquipableAssistIDs(const Unit& unit);


	std::vector<ID> getAlliedCellIDs(const Unit & unit);
	std::vector<ID> getOtherAlliedCellIDs(const Unit & unit);


private:
	struct AttackRangeMap { static std::map<MobilitySet, Range::DistanceSet> getRangeMap(const Unit& unit) { return unit.getInventory().getAttackRanges(); } };
	struct AssistRangeMap { static std::map<MobilitySet, Range::DistanceSet> getRangeMap(const Unit& unit) { return unit.getInventory().getAssistRanges(); } };
	template<typename RangeGetter>
	std::set<ID> getMaxEquipableIDs(const Unit& unit);
};