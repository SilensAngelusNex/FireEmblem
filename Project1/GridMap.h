#pragma once
#include "Grid.h"
//#include "CellPath.h"
#include "Party.h"
#include "ID.h"
#include "PathMap.h"
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <set>

using PathQueue = std::priority_queue<CostID>;
class GridMap :	public Grid {
public:

	GridMap(int width, int height);
	GridMap(int width, int height, std::vector<PartyData> data);

	Party& getParty(const Unit& unit);
	const Party& getParty(const Unit& unit) const;

	PathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility);
	PathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible);
	PathMap getShortestPathsMap(const Unit& unit);

	constPathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const;
	constPathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const;
	constPathMap getShortestPathsMap(const Unit& unit) const;

	//CellPath<GridCell> getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility);
};


