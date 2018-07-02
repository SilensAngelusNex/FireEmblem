#pragma once
#include "Grid.h"
//#include "CellPath.h"
#include "Party.h"
#include "ID.h"
#include "CostMap.h"
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

	CostMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility);
	CostMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible);
	CostMap getShortestPathsMap(const Unit& unit);

	constCostMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const;
	constCostMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const;
	constCostMap getShortestPathsMap(const Unit& unit) const;

	//CellPath<GridCell> getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility);
};


