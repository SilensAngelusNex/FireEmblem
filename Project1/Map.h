#pragma once
#include <vector>
#include "Unit.h"
#include "GridCell.h"
#include "CellPath.h"
#include <map>
#include <queue>
#include <functional>
#include "Party.h"
/**
Map class. Holds a Matrix of GridCells and all of the units. Should be initialized at the start of each chapter.
*/
using PathMap = std::map<GridCell*, CellCost>;
inline auto comp = [](const CellCost& lhs, const CellCost& rhs) { return lhs.first < rhs.first; };
using PathQueue = std::priority_queue<CellCost, std::vector<CellCost>, decltype (comp)>;
class Map {
private:

	std::map<Unit*, GridCell*> _unit_to_cell;
	std::vector<std::vector<GridCell>> _grid;
	std::vector<Party> _parties;
	void insertAdjacencies();

public:
	Map(const Map& map) = delete;
	Map& operator=(const Map & map) = delete;
	Map(Map&& map) = default;
	Map& operator=(Map&& map) = default;

	Map(int width, int height);
	
	void moveUnit(GridCell& start, GridCell& destination);
	void insertUnit(Unit& new_unit, GridCell& destination);
	void removeUnit(Unit& unit);
	
	GridCell& getGridCell(int x_pos, int y_pos);
	GridCell& getGridCell(Unit& unit);

	const GridCell& getGridCell(int x_pos, int y_pos) const;
	const GridCell& getGridCell(Unit& unit) const;

	PathMap findShortestPaths(GridCell& start);
	PathMap findShortestPaths(GridCell& start, int max_move, MobilityList<bool> mobility);

	CellPath getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilityList<bool> mobility);
	
	//I can't get std::as_const to work
	const PathMap findShortestPaths(GridCell& start) const;
	const PathMap findShortestPaths(GridCell& start, int max_move, MobilityList<bool> mobility) const;
	std::vector<GridCell*> getAlliedCells(GridCell& unit_cell);

};

