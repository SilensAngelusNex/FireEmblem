#pragma once
#include "Grid.h"
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "CellPath.h"
#include "Party.h"



using constPathMap = std::map<const GridCell*, constCellCost>;
using PathMap = std::map<GridCell*, CellCost>;
inline auto comp = [](const CellCost& lhs, const CellCost& rhs) { return lhs.first < rhs.first; };
inline auto const_comp = [](const constCellCost& lhs, const constCellCost& rhs) { return lhs.first < rhs.first; };
using constPathQueue = std::priority_queue<constCellCost, std::vector<constCellCost>, decltype (const_comp)>;
using PathQueue = std::priority_queue<CellCost, std::vector<CellCost>, decltype (comp)>;
class GridMap :
	public Grid
{
public:
	GridMap(int width, int height);
	GridMap(int width, int height, std::vector<PartyData> data);

	Party& getParty(const Unit& unit);
	const Party& getParty(const Unit& unit) const;


	PathMap findShortestPaths(const Unit& unit);
	PathMap findShortestPaths(size_t x, size_t y);
	PathMap findShortestPaths(GridCell& start);
	PathMap findShortestPaths(GridCell& start, int max_move, MobilitySet mobility);
	PathMap findShortestPaths(GridCell& start, int max_move, MobilitySet mobility, bool intangible);

	constPathMap findShortestPaths(const Unit& unit) const;
	constPathMap findShortestPaths(size_t x, size_t y) const;
	constPathMap findShortestPaths(const GridCell& start) const;
	constPathMap findShortestPaths(const GridCell& start, int max_move, MobilitySet mobility) const;
	constPathMap findShortestPaths(const GridCell& start, int max_move, MobilitySet mobility, bool intangible) const;

	CellPath getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilitySet mobility);
};

