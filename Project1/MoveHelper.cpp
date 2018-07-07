
#include "MoveHelper.h"
#include "UnitPath.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
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
	CostMap cost_map = _map.getShortestPathsMap(unit);
	std::set<ID> cells = std::set<ID>();
	for (auto pair : cost_map) {
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

UnitPath MoveHelper::getShortestPath(const Unit& unit, ID destination) {
	Expects(_map.getShortestPathsMap(unit).hasKey(destination));
	return UnitPath(unit, _map.getShortestPathsMap(unit), _map[destination]);
}

//Modify path to add destination while keeping the path legal, and using as much of the current path as possible
UnitPath& MoveHelper::routePathTo(UnitPath& path, ID destination) {
	if (path.contains(destination)) {
		path.trimPath(destination);
		return path;
	}
	if (path.back().isAdjacent(destination)) { //Take Adjacent option if available
		auto cost = path.back().getEdge(destination).value().getCost(path._unit.getMobility().getMobilitySet());
		if (cost && cost.value() + path.getCost() <= path._unit.getMobility().getMove()) {
			path.push_back(_map[destination]);
			return path;
		}
	}
	CostMap cost_map = _map.getShortestPathsMap(path._unit);
	if (!cost_map.hasKey(destination)) { //If impossible, cut our losses
		return path;
	}
	while (path.size() > 0) { //Keep as much of our current path as possible
		CostMap cost_map = _map.getShortestPathsMap(path._unit, path.back()._id, path._unit.getMobility().getMove() - path.getCost());
		if (cost_map.hasKey(destination)) {
			return path + UnitPath(path._unit, cost_map, _map[destination]);
		}
		path.pop_back(); //GSL will throw if we reach here when size = 1, but we should never do that anyways.
	}
	Ensures(false);
	return path;
}

void MoveHelper::walkPath(Unit & unit, UnitPath path) {
	GridCell* current_cell = _map.getCell(unit);
	//std::cout << "Start walking " << unit.getIdentity() << " from space:" << _map[unit] << " to space " << path.back()._id << std::endl;
	for (auto& pair : path) {
		//std::cout << "Moving " << unit.getIdentity() << " from " << current_cell->_id << " to " << pair.second.get()._id << std::endl;
		if (!unit.getMobility().canPass(_map.getUnit(pair.second))) {
			// Walked into a stealthed unit or the like
			//Add logic for that
			return;
		}
		if (!_map.hasUnit(pair.second)) { //Skip over units we can move through add skill logic for that
			_map.moveUnit(current_cell->_id, pair.second.get()._id);
			current_cell = _map.getCell(unit);
		}
	}

}
