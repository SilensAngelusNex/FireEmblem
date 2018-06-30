
#include "MoveHelper.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
//#include "CellPath.h"
#include "GridCell.h"
#include "Range.h"

MoveHelper::MoveHelper(GridMap& map) :
	MapHelper(map)
{}
//Get Cells a Unit can move to
std::vector<ID> MoveHelper::getAccesibleCellIDs(const Unit& unit) {
	PathMap path_map = getShortestPathsMap(unit);
	std::set<ID> cells = std::set<ID>();
	for (auto pair : path_map) {
		cells.emplace(pair.first._id);
	}
	std::vector<ID> allied_cells = getOtherAlliedCellIDs(unit);
	for (ID cell : allied_cells) {
		cells.erase(cell);
	}	
	return std::vector<ID>(cells.begin(), cells.end());
}
//Get a PathMap used to find the shortest paths to any Accesible Cell
PathMap MoveHelper::getShortestPathsMap(const Unit& unit) const{ 
	return _map.getShortestPathsMap(_map[unit], unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit](const Unit* other) { return unit.getMobility().canPass(other); });
}

///////////////////////////////////////////////////////////////////////////////////

// Get Cells that a unit can attack without moving with Equipped Weapon
std::vector<ID> MoveHelper::getAttackableCellIDs(const Unit& unit) {
	return getAttackableCellIDs(unit, _map[unit]);
}

//Get Cells a Unit could attack with Equipped Weapon, if it were standing on cell
std::vector<ID> MoveHelper::getAttackableCellIDs(const Unit& unit, ID cell) {
	Range range = Range(); //sword //TODO(Torrey):get actual ranges from Unit
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange();
	}
	return getCellIDsWithin(range, cell);
}

//Get Cells a Unit can Attack with Equipped Weapon including movement
std::vector<ID> MoveHelper::getAllAttackableCellIDs(const Unit& unit) {
	auto cells = std::set<ID>();
	auto accesible_cells = getAccesibleCellIDs(unit);
	for (auto acc_cell : accesible_cells) {
		auto attack_cells = getAttackableCellIDs(unit, acc_cell);
		//std::cout << attack_cells.size() << std::endl;
		for (auto atk_cell : attack_cells) {
				cells.insert(atk_cell);
		}
	}
	std::vector<ID> vec = std::vector<ID>(cells.begin(), cells.end());
	return vec;
}
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