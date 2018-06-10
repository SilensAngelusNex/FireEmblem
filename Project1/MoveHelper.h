#pragma once
#include "Map.h"
#include "CellPath.h"
class MoveHelper
{
private:
	Map& _map;
	template<typename T>
	void vectorSubtract(std::vector<T>& a, std::vector<T>& b) {
		std::sort(a.begin(), a.end());
		std::sort(b.begin(), b.end());
		std::vector<GridCell*> c = std::vector<GridCell*>();
		std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
		a = c;
	};
public:
	MoveHelper(Map& map);
	std::vector<GridCell*> getAccesibleCells(Unit& unit);
	PathMap findShortestPaths(Unit & unit);

	CellPath getShortestPath(Unit& unit, GridCell & destination);
	CellPath getShortestPath(GridCell& start, GridCell& destination);
	CellPath getShortestPath(GridCell& start, GridCell& destination, int max_move);

	std::vector<GridCell*> getAttackableCells(Unit & unit);
	std::vector<GridCell*> getAttackableCells(Unit & unit, GridCell & cell);
	std::vector<GridCell*> getAllAttackableCells(Unit & unit);
	std::vector<GridCell*> getAlliedCells(Unit & unit);

	bool canWalk(Unit & unit, CellPath path);

	void walkPath(Unit& unit, CellPath path);
};
