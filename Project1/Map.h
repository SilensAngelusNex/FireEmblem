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
class Map
{
private:
	struct prev_cost_pair {
		GridCell* _prev_cell;
		int _cost;
		bool operator<(const prev_cost_pair& a) const
		{
			return (_cost < a._cost);
		}
	};
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Unit> _units;
	std::map<GridCell*, prev_cost_pair> _shortest_path_map = std::map<GridCell*, prev_cost_pair>();
	GridCell* _shortest_path_start = nullptr;
	void findShortestPaths(GridCell* start);
	void findShortestPaths(std::priority_queue<prev_cost_pair>& queue);

public:
	Map(int _width, int _height);
	bool moveUnit(GridCell* start, GridCell* destination);
	std::vector<GridCell*> getAccesibleCells(GridCell* start);
	CellPath getShortestPath(GridCell* start, GridCell* destination);
	//std::vector<GridCell*> cellsWithinWeaponRange(GridCell start);

};

