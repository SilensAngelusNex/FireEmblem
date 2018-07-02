
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
std::set<ID> getEquipableRangesHelper(const Unit & unit, ID pos, const MapHelper* helper) {
	std::map<MobilitySet, Range::DistanceSet> range_map = RangeGetter::getRangeMap(unit);
	std::set<ID> ids;
	for (auto range_pair : range_map) {
		Range range = Range(range_pair.first, range_pair.second);
		auto range_ids = helper->getCellIDsWithin(range, pos);
		for (auto id : range_ids) {
			ids.emplace(id);
		}
	}
	return ids;

}

template<typename RangeGetter>
std::set<ID> getMoveEquipableRangesHelper(const Unit& unit, const MoveHelper* helper){
	std::map<MobilitySet, Range::DistanceSet> range_map = RangeGetter::getRangeMap(unit);
	std::set<ID> ids;
	std::set<ID> acc_cells = helper->getAccesibleCellIDs(unit);
	for (auto& acc_id : acc_cells) {
		std::set<ID> eqp_ids = getEquipableRangesHelper<RangeGetter>(unit, acc_id, helper);
		for (ID id: eqp_ids) {
			ids.emplace(id);
		}
	}
	return ids;
}




MoveHelper::MoveHelper(GridMap& map) :
	MapHelper(map)
{}

//Get Cells a Unit can move to
std::set<ID> MoveHelper::getAccesibleCellIDs(const Unit& unit) const {
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
std::vector<ID> MoveHelper::getEquipedAttackIDs(const Unit & unit) const{
	return getEquipedAttackIDs(unit, _map[unit]);
}
//Get Cell IDs Unit can Attack with Equipped Weapon Without moving from pos
std::vector<ID> MoveHelper::getEquipedAttackIDs(const Unit & unit, ID pos) const{
	Range range = Range(); 
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange();
	}
	return getCellIDsWithin(range, pos);
}
//Get Cell IDs Unit can Attack with Equippable Weapons Without moving
std::set<ID> MoveHelper::getEquipableAttackIDs(const Unit & unit) const{
	return getEquipableAttackIDs(unit, _map[unit]);
}
//Get Cell IDs Unit can Attack with Equippable Weapons Without moving from pos
std::set<ID> MoveHelper::getEquipableAttackIDs(const Unit & unit, ID pos) const{
	return getEquipableRangesHelper<AttackRangeMap>(unit, pos, this);
}
//Get Cell IDs Unit Can Attack with any equippable Weapon from any Accessible Cell
std::set<ID> MoveHelper::getMoveEquipableAttackIDs(const Unit & unit) const{
	return getMoveEquipableRangesHelper<AttackRangeMap>(unit, this);
}
///////////////////////////////////////////////////////////////////////////////////
std::vector<ID> MoveHelper::getEquipedAssistIDs(const Unit & unit) const{
	return getEquipedAssistIDs(unit, _map[unit]);
}
//Get Cell IDs Unit can Assist with Equipped Weapon Without moving from pos
std::vector<ID> MoveHelper::getEquipedAssistIDs(const Unit & unit, ID pos) const{
	Range range = Range();
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAssistRange();
	}
	return getCellIDsWithin(range, pos);
}
//Get Cell IDs Unit can Assist with Equippable Weapons Without moving
std::set<ID> MoveHelper::getEquipableAssistIDs(const Unit & unit) const{
	return getEquipableAssistIDs(unit, _map[unit]);
}

//Get Cell IDs Unit can Assist with Equippable Weapons Without moving from pos
std::set<ID> MoveHelper::getEquipableAssistIDs(const Unit & unit, ID pos) const{
	auto range_map = unit.getInventory().getAssistRanges();
	std::set<ID> ids;
	for (auto range_pair : range_map) {
		Range range = Range(range_pair.first, range_pair.second);
		auto range_ids = getCellIDsWithin(range, pos);
		for (auto id : range_ids) {
			ids.emplace(id);
		}
	}
	return ids;

}
//Get Cell IDs Unit Can Assist with any equippable Weapon from any Accessible Cell
std::set<ID> MoveHelper::getMoveEquipableAssistIDs(const Unit & unit) const{
	return getMoveEquipableRangesHelper<AssistRangeMap>(unit, this);
}
////////////////////////////////////////////////////////////////////////////////////

std::vector<ID> MoveHelper::getAlliedCellIDs(const Unit& unit) const{
	auto vec = std::vector<ID>();
	for (Unit& ally : _map.getParty(unit).getUnits()) {
		if (_map.hasUnit(ally)) {
			vec.emplace_back(_map[ally]);
		}
	}
	return vec;
}
std::vector<ID> MoveHelper::getOtherAlliedCellIDs(const Unit& unit) const{
	auto vec = std::vector<ID>();
	for (Unit& ally : _map.getParty(unit).getOtherUnits(unit)) {
		if (_map.hasUnit(ally)) {
			vec.emplace_back(_map[ally]);
		}
	}
	return vec;
}
	////////////////////////////////////////////////////////////////////////////////

MovementPath MoveHelper::getShortestPath(const Unit& unit, ID destination) {
	return MovementPath(_map.getShortestPathsMap(unit), _map[destination]);
}

void MoveHelper::walkPath(Unit & unit, MovementPath path) {
	GridCell* current_cell = _map.getCell(unit);
	std::cout << "Start walking " << unit.getIdentity() << " from space:" << _map[unit] << " to space " << path.back()._id << std::endl;
	for (auto& pair : path) {
		std::cout << "Moving " << unit.getIdentity() << " from " << current_cell->_id << " to " << pair.second.get()._id << std::endl;
		if (!unit.getMobility().canPass(_map.getUnit(pair.second))) {
			// Walked into a stealthed unit or the like
			//Add logic for that
			return;
		}
		if (!_map.hasUnit(pair.second)) { //Skip over units we can move through
			_map.moveUnit(*current_cell, pair.second);
			current_cell = _map.getCell(unit);
		}
	}

}
