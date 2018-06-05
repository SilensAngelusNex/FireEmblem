#pragma once
#include <vector>
#include "Unit.h"
#include "GridCell.h"
#include "CellPath.h"
#include "GridCell.h"
#include <map>
#include <queue>

//Should this class be a singleton?
/**
Map class. Holds a Matrix of GridCells and all of the units. Should be initialized at the start of each chapter.
*/
class Map {
private:
	std::map<Unit*, GridCell*> _unit_to_cell;
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Unit> _units;
	std::map<GridCell*, std::pair<int, GridCell*>> findShortestPaths(GridCell* start);
	std::map<GridCell*, std::pair<int, GridCell*>> findShortestPaths(GridCell * start, int max_move, MobilityType mobility);
	std::map<GridCell*, std::pair<int, GridCell*>> findShortestPaths(std::priority_queue<std::pair<int, GridCell*>>& queue, std::map<GridCell*, std::pair<int, GridCell*>> &path_map, int max_move, MobilityType mobility);
	void insertAdjacencies();

public:
	Map(int width, int height);
	GridCell& getGridCell(int x_pos, int y_pos);
	bool moveUnit(GridCell* start, GridCell* destination);
	bool insertUnit(Unit * new_unit, GridCell * destination);
	void removeUnit(Unit * unit);
	std::vector<GridCell*> getAccesibleCells(Unit * unit);
	//CellPath& getShortestPath(GridCell* start, GridCell* destination);
	std::vector<GridCell*> getAlliedCells(GridCell * unit_cell);
	//std::vector<GridCell*> cellsWithinWeaponRange(GridCell start);

};

