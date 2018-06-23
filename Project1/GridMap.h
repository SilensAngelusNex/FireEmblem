#pragma once
#include "Grid.h"
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include "CellPath.h"
#include "Party.h"
#include "ID.h"
//#include "PathMap.h"



using PathMap = std::map<const ID, CellCost>;
inline auto comp = [](const CellCost& lhs, const CellCost& rhs) { return lhs.first < rhs.first; };
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
	PathMap findShortestPaths(ID start);
	PathMap findShortestPaths(ID start, int max_move, MobilitySet mobility);
	PathMap findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible);


	const PathMap findShortestPaths(const Unit& unit) const;
	const PathMap findShortestPaths(size_t x, size_t y) const;
	const PathMap findShortestPaths(ID start) const;
	const PathMap findShortestPaths(ID start, int max_move, MobilitySet mobility) const;
	const PathMap findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) const;

	//CellPath getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilitySet mobility);
};

