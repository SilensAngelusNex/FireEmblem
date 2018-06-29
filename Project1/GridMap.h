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

	template<typename lambda>
	id_cost_map getShortestPathsHelper(ID start, int max_move, MobilitySet mobility, lambda canPass) const;
	using PathQueue = std::priority_queue<CostID>;
public:


	GridMap(int width, int height);
	GridMap(int width, int height, std::vector<PartyData> data);

	Party& getParty(const Unit& unit);
	const Party& getParty(const Unit& unit) const;


	PathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility);
	PathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible);
	template<typename lambda>
	PathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, lambda canPass);

	constPathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const;
	constPathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const;
	template<typename lambda>
	constPathMap getShortestPathsMap(ID start, int max_move, MobilitySet mobility, lambda canPass) const;

	//CellPath<GridCell> getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility);
};


template<typename lambda>
inline id_cost_map GridMap::getShortestPathsHelper(ID start, int max_move, MobilitySet mobility, lambda canPass) const
{
	PathQueue queue = PathQueue();
	id_cost_map path_map = id_cost_map();
	path_map.emplace(start, CostID(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = (*this)[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility);
			if (canPass(getUnit(edge._id)) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= max_move && (path_map.count(edge._id) == 0 || cost.value() < path_map.at(edge._id).first)) {
					path_map.insert_or_assign(edge._id, CostID(cost.value(), top.second));
					queue.emplace(cost.value(), edge._id);
				}
			}
		}
	}
	return path_map;
}

template<typename lambda>
inline PathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, lambda canPass) {
	return PathMap(*this, getShortestPathsHelper(start, max_move, mobility, canPass));
}
template<typename lambda>
inline constPathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, lambda canPass) const{
	return constPathMap(*this, getShortestPathsHelper(start, max_move, mobility, canPass));
}