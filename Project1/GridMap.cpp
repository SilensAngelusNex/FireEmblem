#include "GridMap.h"
#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "GridCell.h"
#include "CellPath.h"
#include "CellEdge.h"



GridMap::GridMap(int width, int height) : 
	Grid(width, height)
{}

GridMap::GridMap(int width, int height, std::vector<PartyData> data) :
	Grid(width, height, data)
{}

Party& GridMap::getParty(Unit & unit) {
	return unit._party->getParty(Passkey<GridMap>());
}

const Party& GridMap::getParty(Unit & unit) const {
	return unit._party->getParty(Passkey<GridMap>());
}

PathMap GridMap::findShortestPaths(GridCell& start) {
	return std::as_const(*this).findShortestPaths(start);
}

PathMap GridMap::findShortestPaths(GridCell & start, Mobility & mobility) {
	return std::as_const(*this).findShortestPaths(start, mobility);
}

PathMap GridMap::findShortestPaths(GridCell& start, int max_move, MobilitySet mobility) {
	return std::as_const(*this).findShortestPaths(start, max_move, mobility);
}

PathMap GridMap::findShortestPaths(GridCell & start, int max_move, MobilitySet mobility, bool intangible) {
	return std::as_const(*this).findShortestPaths(start, max_move, mobility, intangible);
}
const PathMap GridMap::findShortestPaths(GridCell& start) const {
	return findShortestPaths(start, INT_MAX, MobilitySet({ true, }), false);
};
const PathMap GridMap::findShortestPaths(GridCell& start, int max_move, MobilitySet mobility, bool intangible) const {
	PathQueue queue = PathQueue(comp);
	PathMap path_map = PathMap();
	path_map.emplace(&start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		CellCost top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if ((!hasUnit(edge._cell) || intangible) && cost.has_value()) {
				cost = top.first + cost.value();
				if (cost.value() <= max_move && (path_map.count(&(edge._cell)) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}

const PathMap GridMap::findShortestPaths(GridCell& start, Mobility& mobility) const {
	PathQueue queue = PathQueue(comp);
	PathMap path_map = PathMap();
	path_map.emplace(&start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		CellCost top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = mobility.getCost(edge);

			if (mobility.canPass(getUnit(edge._cell)) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= mobility.getMove() && (path_map.count(&(edge._cell)) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}
const PathMap GridMap::findShortestPaths(GridCell& start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return findShortestPaths(start, max_move, mobility, intangible);
}

CellPath GridMap::getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilitySet mobility) {
	PathMap path_map = findShortestPaths(start, max_move, mobility);
	std::list<CellRef> path = std::list<CellRef>();
	path.push_front(destination);
	while (!(start == path.front().get())) {
		path.push_front(path_map.at(&path.front().get()).second);
	}
	return CellPath(path, mobility);
}