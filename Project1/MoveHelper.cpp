
#include "MoveHelper.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
//#include "CellPath.h"
#include "GridCell.h"
#include "Range.h"
#include "GridMap.h"

MoveHelper::MoveHelper(GridMap& map) :
	MapHelper(map)
{}

//Get Cells a Unit can move to
std::set<ID> MoveHelper::getAccesibleCellIDs(const Unit& unit) {
	PathMap path_map = getShortestPathsMap(unit);
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
//Get a PathMap used to find the shortest paths to any Accesible Cell
PathMap MoveHelper::getShortestPathsMap(const Unit& unit) const{ 
	return _map.getShortestPathsMap(_map[unit], unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit](const Unit* other) { return unit.getMobility().canPass(other); });
}

///////////////////////////////////////////////////////////////////////////////////

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
	/*
	AdjCellPath MoveHelper::getShortestPath(const Unit& unit, GridCell & destination) {
	return _map.getShortestPath(_map[unit], destination, unit.getMobility().getMove(), unit.getMobility().getMobilitySet());
	}

	AdjCellPath MoveHelper::getShortestPath(GridCell & start, GridCell & destination) {
	return _map.getShortestPath(start, destination, INT_MAX, MobilitySet(MobilityType::values::GROUNDED));
	}

	AdjCellPath MoveHelper::getShortestPath(GridCell & start, GridCell & destination, int max_move) {
	return _map.getShortestPath(start, destination, max_move, MobilitySet(MobilityType::values::GROUNDED));
	}
	*/
	////////////////////////////////////////////////////////////////////////

/*
bool MoveHelper::canWalk(Unit& unit, AdjCellPath path) {
	bool valid = path.getHead() == _map[unit];
	for (auto pair : path) {
		valid &= pair.first <= unit.getMobility().getMove();
	}
	return valid;
}

void MoveHelper::walkPath(Unit & unit, AdjCellPath path) {
	Expects(canWalk(unit, path));
	GridCell::Ref unit_cell = path.getHead();
	for (auto it = std::next(path.begin()); it != path.end(); it++) {
		if (unit_cell.get().getEdge(it->second).value().getCost(unit.getMobility().getMobilitySet()).has_value()) {
			_map.moveUnit(unit_cell, it->second);
		} else {// can't pass
				return;
		}
		unit_cell = it->second;
	}	
}
*/