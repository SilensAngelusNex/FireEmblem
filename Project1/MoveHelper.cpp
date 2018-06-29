
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
std::vector<GridCell::Ref> MoveHelper::getAccesibleCells(const Unit& unit) {
	PathMap path_map = findShortestPaths(unit);
	std::vector<GridCell::Ref> cells = std::vector< GridCell::Ref>();
	for (auto pair : path_map) {
		cells.push_back(pair.first);
	}
	std::vector<GridCell::Ref> allied_cells = getOtherAlliedCells(unit);
	vectorSubtract(cells,allied_cells);
	return cells;
}
PathMap MoveHelper::findShortestPaths(const Unit& unit) const{ 
	return _map.findShortestPaths(_map[unit]._id, unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit](const Unit* other) { return unit.getMobility().canPass(other); });
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
// Get Cells that a unit can attack without moving

std::vector<GridCell::Ref> MoveHelper::getAttackableCells(const Unit& unit) {
	return getAttackableCells(unit, _map[unit]);
}
//Get Cells a Unit could attack, if it were standing on cell

std::vector<GridCell::Ref> MoveHelper::getAttackableCells(const Unit& unit, GridCell& cell) {
	Range range = Range({1}); //sword //TODO(Torrey):get actual ranges from Unit
	return getCellsWithin(range, cell);
}
//Get Cells a Unit can Attack including movement

std::vector<GridCell::Ref> MoveHelper::getAllAttackableCells(const Unit& unit) {
	auto cells = std::set<GridCell::Ref>();
	auto accesible_cells = getAccesibleCells(unit);
	for (auto acc_cell : accesible_cells) {
		auto attack_cells = getAttackableCells(unit, acc_cell);
		//std::cout << attack_cells.size() << std::endl;
		for (auto atk_cell : attack_cells) {
				cells.insert(atk_cell);
		}
	}
	std::vector<GridCell::Ref> vec = std::vector<GridCell::Ref>(cells.begin(), cells.end());
	return vec;
}
std::vector<GridCell::Ref> MoveHelper::getAlliedCells(const Unit& unit) {
	auto vec = std::vector<GridCell::Ref>();
	for (Unit& ally : _map.getParty(unit).getUnits()) {
		if (_map.hasUnit(ally)) {
			vec.push_back(_map[ally]);
		}
	}
	return vec;
}
std::vector<GridCell::Ref> MoveHelper::getOtherAlliedCells(const Unit& unit) {
	auto vec = std::vector<GridCell::Ref>();
	for (Unit& ally : _map.getParty(unit).getOtherUnits(unit)) {
		if (_map.hasUnit(ally)) {
			vec.push_back(_map[ally]);
		}
	}
	return vec;
}
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