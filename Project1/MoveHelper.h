#pragma once

#include <vector>
#include "GridMap.h"
#include "MapHelper.h"

template<typename T>
inline bool operator== (const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) {
	return lhs.get() == rhs.get();
}
inline bool operator< (const CellRef& lhs, const CellRef& rhs) {
	return &lhs.get() < &rhs.get();
}

class Unit;
class CellPath;
class GridCell;
class MoveHelper : 
	public MapHelper 
{
private:



	//static auto comp = [](const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) { return 0 == 1); };

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

