
#include "MoveHelper.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
//#include "CellPath.h"
#include "GridCell.h"
#include "Range.h"
#include "GridMap.h"

struct AttackRangeMap { static std::map<MobilitySet, Range::DistanceSet> getRangeMap(const Unit& unit) { return unit.getInventory().getAttackRanges(); } };
struct AssistRangeMap { static std::map<MobilitySet, Range::DistanceSet> getRangeMap(const Unit& unit) { return unit.getInventory().getAssistRanges(); } };

template<typename RangeGetter>
std::set<ID> MoveHelper::getMaxEquipableIDs(const Unit& unit) const {
	std::map<MobilitySet, Range::DistanceSet> range_map = RangeGetter::getRangeMap(unit);
	std::set<ID> ids;
	for (auto range_pair : range_map) {
		Range range = Range(range_pair.first, range_pair.second);
		auto range_ids = getCellIDsWithin(range, _map[unit]);
		for (auto id : range_ids) {
			ids.emplace(id);
		}
	}
	return ids;
}

MoveHelper::MoveHelper(GridMap& map) :
	MapHelper(map)
{}

//Get Cells a Unit can move to
std::set<ID> MoveHelper::getAccesibleCellIDs(const Unit& unit) {
	PathMap path_map = _map.getShortestPathsMap(unit);
	std::set<ID> cells = std::set<ID>();
	for (auto pair : path_map) {
		cells.emplace(pair.first._id);
	}
	std::vector<ID> allied_cells = getOtherAlliedCellIDs(unit);
	for (ID cell : allied_cells) {
		cells.erase(cell);
	}	
	return cells;
}

//Get Cell IDs Unit can Attack with Equipped Weapon Without moving
std::vector<ID> MoveHelper::getEquipedAttackIDs(const Unit & unit) {
	return getEquipedAttackIDs(unit, _map[unit]);
}
//Get Cell IDs Unit can Attack with Equipped Weapon Without moving from pos
std::vector<ID> MoveHelper::getEquipedAttackIDs(const Unit & unit, ID pos) {
	Range range = Range(); 
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange();
	}
	return getCellIDsWithin(range, pos);
}
//Get Cell IDs Unit can Attack with Equippable Weapons Without moving
std::set<ID> MoveHelper::getEquipableAttackIDs(const Unit & unit) {
	return getEquipableAttackIDs(unit, _map[unit]);
}
//Get Cell IDs Unit can Attack with Equippable Weapons Without moving from pos
std::set<ID> MoveHelper::getEquipableAttackIDs(const Unit & unit, ID pos) {
	auto range_map = unit.getInventory().getAttackRanges();
	std::set<ID> ids;
	for (auto range_pair : range_map) {
		Range range = Range(range_pair.first, range_pair.second);
		auto range_ids= getCellIDsWithin(range, pos);
		for (auto id : range_ids) {
			ids.emplace(id);
		}
	}
	return ids;
}
//Get Cell IDs Unit Can Attack with any equippable Weapon from any Accessible Cell
std::set<ID> MoveHelper::getMaxEquipableAttackIDs(const Unit & unit) {
	auto acc_ids = getAccesibleCellIDs(unit);
	std::set<ID> ids;
	for (auto acc_id : acc_ids) {
		auto atk_ids = getEquipableAttackIDs(unit, acc_id);
		for (auto atk_id : atk_ids) {
			ids.emplace(atk_id);
		}
	}
	return ids;
}
///////////////////////////////////////////////////////////////////////////////////
std::vector<ID> MoveHelper::getEquipedAssistIDs(const Unit & unit)
{
	return getEquipedAssistIDs(unit, _map[unit]);
}
//Get Cell IDs Unit can Assist with Equipped Weapon Without moving from pos
std::vector<ID> MoveHelper::getEquipedAssistIDs(const Unit & unit, ID pos) {
	Range range = Range();
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAssistRange();
	}
	return getCellIDsWithin(range, pos);
}
//Get Cell IDs Unit can Assist with Equippable Weapons Without moving
std::set<ID> MoveHelper::getEquipableAssistIDs(const Unit & unit) {
	return getEquipableAssistIDs(unit, _map[unit]);
}

//Get Cell IDs Unit can Assist with Equippable Weapons Without moving from pos
std::set<ID> MoveHelper::getEquipableAssistIDs(const Unit & unit, ID pos) {
	return getMaxEquipableIDs<AssistRangeMap>(unit);

}
//Get Cell IDs Unit Can Assist with any equippable Weapon from any Accessible Cell
std::set<ID> MoveHelper::getMaxEquipableAssistIDs(const Unit & unit) {
	return getMaxEquipableIDs<AttackRangeMap>(unit);
}
////////////////////////////////////////////////////////////////////////////////////

std::vector<ID> MoveHelper::getAlliedCellIDs(const Unit& unit) {
	auto vec = std::vector<ID>();
	for (Unit& ally : _map.getParty(unit).getUnits()) {
		if (_map.hasUnit(ally)) {
			vec.emplace_back(_map[ally]);
		}
	}
	return vec;
}
std::vector<ID> MoveHelper::getOtherAlliedCellIDs(const Unit& unit) {
	auto vec = std::vector<ID>();
	for (Unit& ally : _map.getParty(unit).getOtherUnits(unit)) {
		if (_map.hasUnit(ally)) {
			vec.emplace_back(_map[ally]);
		}
	}
	return vec;
}
	////////////////////////////////////////////////////////////////////////////////

