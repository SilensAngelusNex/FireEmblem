#pragma once
#include <vector>
#include "Unit.h"
#include "GridCell.h"
#include "CellPath.h"
#include "GridCell.h"
#include <map>
#include <queue>
/**
Map class. Holds a Matrix of GridCells and all of the units. Should be initialized at the start of each chapter.
*/
using PathMap = std::map<GridCell*, std::pair<int, GridCell*>>;
using PathQueue = std::priority_queue<std::pair<int, GridCell*>>;
class Map {
private:
	std::map<Unit*, GridCell*> _unit_to_cell;
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Unit> _units;
	PathMap findShortestPaths(GridCell* start);
	PathMap findShortestPaths(Unit * unit);
	PathMap findShortestPaths(GridCell* start, int max_move, MobilityList<bool> mobility);
	PathMap findShortestPaths(PathQueue& queue, PathMap& path_map, int max_move, MobilityList<bool> mobility_types);
	std::vector<GridCell*> getAttackableCells(Unit * unit, GridCell * cell);
	void insertAdjacencies();

public:
	Map(int width, int height);
	GridCell& getGridCell(int x_pos, int y_pos);
	bool moveUnit(GridCell* start, GridCell* destination);
	bool insertUnit(Unit * new_unit, GridCell * destination);
	void removeUnit(Unit * unit);
	std::vector<GridCell*> getAccesibleCells(Unit * unit);
	std::vector<GridCell*> getAttackableCells(Unit * unit);
	std::vector<GridCell*> getAllAttackableCells(Unit * unit);
	//CellPath& getShortestPath(GridCell* start, GridCell* destination);
	std::vector<GridCell*> getAlliedCells(GridCell * unit_cell);
	//std::vector<GridCell*> cellsWithinWeaponRange(GridCell start);

};
