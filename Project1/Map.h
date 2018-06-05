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
	struct prev_cost_pair {
		GridCell* _prev_cell;
		int _cost;
		bool operator<(const prev_cost_pair& a) const {
			return (_cost < a._cost);
		}
	};
	std::map<Unit*, GridCell*> _unit_to_cell;
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Unit> _units;
	bool _changed = true;

	GridCell* _shortest_path_start = nullptr;
	void findShortestPaths(GridCell* start);
	void findShortestPaths(GridCell * start, int max_move, MobilityType mobility);
	void findShortestPaths(std::priority_queue<prev_cost_pair>& queue, int max_move, MobilityType mobility);
	void insertAdjacencies();

	

public:
	std::map<GridCell*, prev_cost_pair> _shortest_path_map = std::map<GridCell*, prev_cost_pair>();
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

