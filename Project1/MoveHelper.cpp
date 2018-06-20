
#include "MoveHelper.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
#include "CellPath.h"
#include "GridCell.h"

MoveHelper::MoveHelper(GridMap& map) :
	_map(map)
{}
std::vector<GridCell*> MoveHelper::getAccesibleCells(const Unit& unit) {
	PathMap path_map = findShortestPaths(unit);
	std::vector<GridCell*> cells = std::vector< GridCell*>();
	for (auto& pair : path_map) {
		cells.push_back(pair.first);
	}
	std::vector<GridCell*> allied_cells = getOtherAlliedCells(unit);
	vectorSubtract(cells,allied_cells);
	return cells;
}
PathMap MoveHelper::findShortestPaths(const Unit& unit) const{
	return _map.findShortestPaths(unit);
}
PathMap MoveHelper::findShortestPaths(const Unit& unit) {
	return _map.findShortestPaths(unit);
}
////////////////////////////////////////////////////////////////////////////////

CellPath MoveHelper::getShortestPath(const Unit& unit, GridCell & destination) {
	return _map.getShortestPath(_map[unit], destination, unit.getMobility().getMove(), unit.getMobility().getMobilitySet());
}

CellPath MoveHelper::getShortestPath(GridCell & start, GridCell & destination) {
	return _map.getShortestPath(start, destination, INT_MAX, MobilitySet(MobilityType::values::GROUNDED));
}

CellPath MoveHelper::getShortestPath(GridCell & start, GridCell & destination, int max_move) {
	return _map.getShortestPath(start, destination, max_move, MobilitySet(MobilityType::values::GROUNDED));
}

////////////////////////////////////////////////////////////////////////
// Get Cells that a unit can attack without moving

std::vector<GridCell*> MoveHelper::getAttackableCells(const Unit& unit) {
	return getAttackableCells(unit, _map[unit]);
}
//Get Cells a Unit could attack, if it were standing on cell

std::vector<GridCell*> MoveHelper::getAttackableCells(const Unit& unit, GridCell& cell) {
	const std::array<bool, 32> ranges = { false, true }; //temporary range 1 weapon range
	auto cells = std::vector<GridCell*>();
	for (int i = 0; i < ranges.size(); i++) {
		if (ranges[i]) {
			PathMap map = _map.findShortestPaths(cell, i, MobilitySet(MobilityType::values::PROJECTILE));
			for (auto& pair : map) {
				if (pair.second.first == i) {
					cells.push_back(pair.first);
				}
			}
		}
	}
	return cells;
}
//Get Cells a Unit can Attack including movement

std::vector<GridCell*> MoveHelper::getAllAttackableCells(const Unit& unit) {
	auto cells = std::vector<GridCell*>();;
	auto accesible_cells = getAccesibleCells(unit);
	for (auto acc_cell : accesible_cells) {
		auto attack_cells = getAttackableCells(unit, *acc_cell);
		for (auto atk_cell : attack_cells) {
			if (std::count(cells.begin(), cells.end(), atk_cell) == 0) {
				cells.push_back(atk_cell);
			}
		}
	}
	return cells;
}
std::vector<GridCell*> MoveHelper::getAlliedCells(const Unit& unit) {
	auto vec = std::vector<GridCell*>();
	for (Unit& ally : _map.getParty(unit).getUnits()) {
		if (_map.hasUnit(ally)) {
			vec.push_back(&_map[ally]);
		}
	}
	return vec;
}
std::vector<GridCell*> MoveHelper::getOtherAlliedCells(const Unit& unit) {
	auto vec = std::vector<GridCell*>();
	for (Unit& ally : _map.getParty(unit).getOtherUnits(unit)) {
		if (_map.hasUnit(ally)) {
			vec.push_back(&_map[ally]);
		}
	}
	return vec;
}

bool MoveHelper::canWalk(Unit& unit, CellPath path) {
	bool valid = path.getHead() == _map[unit];
	for (CellCost pair : path) {
		valid = valid && pair.first <= unit.getMobility().getMove();
	}
	return valid;
}

void MoveHelper::walkPath(Unit & unit, CellPath path) {
	Expects(canWalk(unit, path));
	CellRef unit_cell = path.getHead();
	for (auto it = std::next(path.begin()); it != path.end(); it++) {
		if (unit_cell.get().getEdge(it->second).value().getCost(unit.getMobility().getMobilitySet()).has_value()) {
			_map.moveUnit(unit_cell, it->second);
		} else {// can't pass
				return;
		}
		unit_cell = it->second;
	}	
}
