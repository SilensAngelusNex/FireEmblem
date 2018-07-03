#pragma once
#include "Grid.h"
#include "Party.h"
#include "ID.h"
#include "CostMap.h"
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include "PathBase.h"

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
	CostMap getShortestPathsMap(const Unit& unit, ID start);
	CostMap getShortestPathsMap(const Unit& unit, ID start, int remaining_move);

	constCostMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const;
	constCostMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const;
	constCostMap getShortestPathsMap(const Unit& unit) const;
	constCostMap getShortestPathsMap(const Unit& unit, ID start) const;
	constCostMap getShortestPathsMap(const Unit& unit, ID start, int remaining_move) const;

};


