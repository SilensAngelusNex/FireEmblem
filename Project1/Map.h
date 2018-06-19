#pragma once
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "CellPath.h"
#include "Party.h"
/**
Map class. Holds a Matrix of GridCells and all of the units. Should be initialized at the start of each chapter.
*/
class Party;
class GridCell;
class Unit;
class CellPath;
class Mobility;

using PathMap = std::map<GridCell*, CellCost>;
inline auto comp = [](const CellCost& lhs, const CellCost& rhs) { return lhs.first < rhs.first; };
using PathQueue = std::priority_queue<CellCost, std::vector<CellCost>, decltype (comp)>;
class Map {
private:

	std::map<Unit*, GridCell*> _unit_to_cell;
	std::vector<std::vector<GridCell>> _grid;

	void insertAdjacencies();

public:
	std::list<Party> _parties;

	Map(const Map& map) = delete;
	Map& operator=(const Map & map) = delete;
	Map(Map&& map) = default;
	Map& operator=(Map&& map) = default;

	Map(int width, int height);
	Map(int width, int height, std::vector<PartyData> data);
	
	void insertParty(PartyData data);
	void moveUnit(GridCell& start, GridCell& destination);
	void insertUnit(Unit& new_unit, GridCell& destination);
	void removeUnit(Unit& unit);
	
	GridCell& getGridCell(int x_pos, int y_pos);
	GridCell& getGridCell(Unit& unit);
	bool hasUnit(Unit & unit) const;
	Party& getParty(Unit& unit);

	const GridCell& getGridCell(int x_pos, int y_pos) const;
	const GridCell& getGridCell(Unit& unit) const;
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

};

