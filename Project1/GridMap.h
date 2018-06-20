#pragma once
#include "Grid.h"
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "CellPath.h"
#include "Party.h"

using PathMap = std::map<GridCell*, CellCost>;
inline auto comp = [](const CellCost& lhs, const CellCost& rhs) { return lhs.first < rhs.first; };
using PathQueue = std::priority_queue<CellCost, std::vector<CellCost>, decltype (comp)>;
class GridMap :
	public Grid
{
public:
	GridMap(int width, int height);
	GridMap(int width, int height, std::vector<PartyData> data);

	Party& getParty(Unit& unit);
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

