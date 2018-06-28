#pragma once

#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "reference_logic.h"

class Unit;
class CellPath;
class GridCell;
class MoveHelper : 
	public MapHelper 
{
private:
	template<typename T>
	void vectorSubtract(std::vector<std::reference_wrapper<T>>& a, std::vector<std::reference_wrapper<T>>& b) {
		std::sort(a.begin(), a.end());
		std::sort(b.begin(), b.end());
		std::vector<std::reference_wrapper<T>> c = std::vector<std::reference_wrapper<T>>();
		std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
		a = c;
	};
public:
	MoveHelper(GridMap& map);
	std::vector<CellRef> getAccesibleCells(const Unit& unit);
	PathMap findShortestPaths(const Unit & unit) const;
	//CellPath getShortestPath(const Unit& unit,GridCell & destination);
	//CellPath getShortestPath(GridCell& start, GridCell& destination);
	//CellPath getShortestPath(GridCell& start, GridCell& destination, int max_move);

	std::vector<CellRef> getAttackableCells(const Unit & unit);
	std::vector<CellRef> getAttackableCells(const Unit & unit, GridCell & cell);
	std::vector<CellRef> getAllAttackableCells(const Unit & unit);
	std::vector<CellRef> getAlliedCells(const Unit & unit);

	std::vector<CellRef> getOtherAlliedCells(const Unit & unit);

	//bool canWalk(Unit & unit, CellPath path);

	//void walkPath(Unit& unit, CellPath path);
};

