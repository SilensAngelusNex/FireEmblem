#pragma once
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "CellPath.h"
#include "Party.h"
/**
Grid class. Holds a Matrix of GridCells and all of the units. Should be initialized at the start of each chapter.
*/
class GridCell;
class Unit;
class Mobility;

using PathMap = std::map<GridCell*, CellCost>;
inline auto comp = [](const CellCost& lhs, const CellCost& rhs) { return lhs.first < rhs.first; };
using PathQueue = std::priority_queue<CellCost, std::vector<CellCost>, decltype (comp)>;
class Grid {
private:

	std::map<const Unit*, GridCell*> _unit_to_cell;
	std::map<const GridCell*, Unit*> _cell_to_unit;
	std::vector<std::vector<GridCell>> _grid;

	void insertAdjacencies();

public:
	std::list<Party> _parties;

	Grid(const Grid& map) = delete;
	Grid& operator=(const Grid & map) = delete;
	Grid(Grid&& map) = default;
	Grid& operator=(Grid&& map) = default;

	Grid(int width, int height);
	Grid(int width, int height, std::vector<PartyData> data);
	
	void insertParty(PartyData data);
	void moveUnit(GridCell& start, GridCell& destination);
	void insertUnit(Unit& new_unit, GridCell& destination);
	void removeUnit(Unit& unit);
	
	GridCell& getGridCell(int x_pos, int y_pos);
	bool hasUnit(const GridCell & index) const;
	bool hasUnit(const Unit & unit) const;
	Party& getParty(Unit& unit);

	const GridCell& getGridCell(int x_pos, int y_pos) const;
	const Party& getParty(Unit& unit) const;

	PathMap findShortestPaths(GridCell& start);
	PathMap findShortestPaths(GridCell& start, Mobility& mobility);
	PathMap findShortestPaths(GridCell& start, int max_move, MobilitySet mobility);
	PathMap findShortestPaths(GridCell & start, int max_move, MobilitySet mobility, bool intangible);

	CellPath getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilitySet mobility);
	
	const PathMap findShortestPaths(GridCell& start) const;
	const PathMap findShortestPaths(GridCell& start, int max_move, MobilitySet mobility) const;
	const PathMap findShortestPaths(GridCell& start, Mobility& mobility) const;
	const PathMap findShortestPaths(GridCell & start, int max_move, MobilitySet mobility, bool intangible) const;

	Unit& operator[](const GridCell& index);
	GridCell& operator[](const Unit& index);

	const Unit& operator[](const GridCell& index) const;
	const GridCell& operator[](const Unit& index) const;
};

