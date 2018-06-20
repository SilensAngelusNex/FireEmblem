#pragma once

#include <vector>
#include "GridMap.h"

class CellPath;
class GridCell;
class Unit;
class MoveHelper {
private:
	GridMap& _map;
	template<typename T>
	void vectorSubtract(std::vector<T>& a, std::vector<T>& b) {
		std::sort(a.begin(), a.end());
		std::sort(b.begin(), b.end());
		std::vector<T> c = std::vector<T>();
		std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
		a = c;
	};
public:
	MoveHelper(GridMap& map);
	std::vector<GridCell*> getAccesibleCells(const Unit& unit);
	PathMap findShortestPaths(const Unit & unit) const;
	PathMap findShortestPaths(const Unit& unit);
	CellPath getShortestPath(const Unit& unit,GridCell & destination);
	CellPath getShortestPath(GridCell& start, GridCell& destination);
	CellPath getShortestPath(GridCell& start, GridCell& destination, int max_move);

	std::vector<GridCell*> getAttackableCells(const Unit & unit);
	std::vector<GridCell*> getAttackableCells(const Unit & unit, GridCell & cell);
	std::vector<GridCell*> getAllAttackableCells(const Unit & unit);
	std::vector<GridCell*> getAlliedCells(const Unit & unit);

	std::vector<GridCell*> getOtherAlliedCells(const Unit & unit);

	bool canWalk(Unit & unit, CellPath path);

	void walkPath(Unit& unit, CellPath path);
};

