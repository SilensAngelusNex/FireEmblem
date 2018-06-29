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

class GridMap :
	public Grid
{

private: 
	id_cost_map getShortestPaths(const Unit & unit) const;
	id_cost_map getShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) const;
	using PathQueue = std::priority_queue<CostID>;
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


	constPathMap findShortestPaths(const Unit& unit) const;
	constPathMap findShortestPaths(size_t x, size_t y) const;
	constPathMap findShortestPaths(ID start) const;
	constPathMap findShortestPaths(ID start, int max_move, MobilitySet mobility) const;
	constPathMap findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) const;

	//CellPath<GridCell> getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility);
};

