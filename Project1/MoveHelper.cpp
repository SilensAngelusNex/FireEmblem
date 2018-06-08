#include "MoveHelper.h"

MoveHelper::MoveHelper(Map& map) :
	_map(map)
{}
std::vector<GridCell*> MoveHelper::getAccesibleCells(Unit& unit) {
	PathMap path_map = findShortestPaths(unit);
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (auto& pair : path_map) {
		cells.push_back(pair.first);
	}
	std::vector<GridCell*> allied_cells = getAlliedCells(unit);
	vectorSubtract(cells,allied_cells);
	cells.push_back(&_map.getGridCell(unit));
	return cells;
}
PathMap MoveHelper::findShortestPaths(Unit& unit) {
	return _map.findShortestPaths(_map.getGridCell(unit), unit.getMobility().getMove(), unit.getMobility().getMobilityType());
}
/* Get Cells that a unit can attack without moving
*/
std::vector<GridCell*> MoveHelper::getAttackableCells(Unit& unit) {
	return getAttackableCells(unit, _map.getGridCell(unit));
}
/*Get Cells a Unit could attack, if it were standing on cell
*/
std::vector<GridCell*> MoveHelper::getAttackableCells(Unit& unit, GridCell& cell) {
	const std::array<bool, 32> ranges = { false, true }; //temporary range 1 weapon range
	std::vector<GridCell*> cells = std::vector<GridCell*>();
	for (int i = 0; i < ranges.size(); i++) {
		if (ranges[i]) {
			PathMap map = _map.findShortestPaths(cell, i, MobilityList<bool>({ false, false, false, true }));
			for (auto& pair : map) {
				if (pair.second.first == i) {
					cells.push_back(pair.first);
				}
			}
		}
	}
	return cells;
}
/*Get Cells a Unit can Attack including movement
*/
std::vector<GridCell*> MoveHelper::getAllAttackableCells(Unit& unit) {
	std::vector<GridCell*> cells = std::vector<GridCell*>();;
	std::vector<GridCell*> accesible_cells = getAccesibleCells(unit);
	for (GridCell* acc_cell : accesible_cells) {
		std::vector<GridCell*> attack_cells = getAttackableCells(unit, *acc_cell);
		for (GridCell* atk_cell : attack_cells) {
			if (std::count(cells.begin(), cells.end(), atk_cell) == 0) {
				cells.push_back(atk_cell);
			}
		}
	}
	return cells;
}
std::vector<GridCell*> MoveHelper::getAlliedCells(Unit& unit) {
	return std::vector < GridCell*>({&_map.getGridCell(unit)});
}
