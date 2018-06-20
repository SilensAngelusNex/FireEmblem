#include "GridMap.h"
#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "GridCell.h"
#include "CellPath.h"
#include "CellEdge.h"
#include "Mobility.h"



GridMap::GridMap(int width, int height) :
	Grid(width, height)
{}

GridMap::GridMap(int width, int height, std::vector<PartyData> data) :
	Grid(width, height, data)
{}

Party& GridMap::getParty(const Unit & unit) {
	return unit._party->getParty(Passkey<GridMap>());
}

const Party& GridMap::getParty(const Unit & unit) const {
	return unit._party->getParty(Passkey<GridMap>());
}


PathMap GridMap::findShortestPaths(size_t x, size_t y) {
	return findShortestPaths((*this)[x][y], INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

PathMap GridMap::findShortestPaths(GridCell & start) {
	return findShortestPaths(start, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

PathMap GridMap::findShortestPaths(GridCell & start, int max_move, MobilitySet mobility) {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return findShortestPaths(start, max_move, mobility, intangible);
}

PathMap GridMap::findShortestPaths(GridCell & start, int max_move, MobilitySet mobility, bool intangible) {
	PathQueue queue = PathQueue(comp);
	PathMap path_map = PathMap();
	path_map.emplace(&start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if ((!hasUnit(edge._cell) || intangible) && cost.has_value()) {
				cost = top.first + cost.value();
				if (cost.value() <= max_move && (path_map.count(&edge._cell) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}

constPathMap GridMap::findShortestPaths(const Unit & unit) const {
	const GridCell& start = (*this)[unit];
	auto queue = constPathQueue(const_comp);
	auto path_map = constPathMap();
	path_map.emplace(&start, constCellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = unit.getMobility().getCost(edge);

			if (unit.getMobility().canPass(getUnit(edge._cell)) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= unit.getMobility().getMove() && (path_map.count(&edge._cell) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, constCellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}

constPathMap GridMap::findShortestPaths(size_t x, size_t y) const {
	return findShortestPaths((*this)[x][y], INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

constPathMap GridMap::findShortestPaths(const GridCell & start) const {
	return findShortestPaths(start, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

constPathMap GridMap::findShortestPaths(const GridCell & start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return findShortestPaths(start, max_move, mobility, intangible);
}

constPathMap GridMap::findShortestPaths(const GridCell& start, int max_move, MobilitySet mobility, bool intangible) const {
	constPathQueue queue = constPathQueue(const_comp);
	constPathMap path_map = constPathMap();
	path_map.emplace(&start, constCellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if ((!hasUnit(edge._cell) || intangible) && cost.has_value()) {
				cost = top.first + cost.value();
				if (cost.value() <= max_move && (path_map.count(&edge._cell) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, constCellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
}

PathMap GridMap::findShortestPaths(const Unit& unit) {
	GridCell& start = (*this)[unit];
	auto queue = PathQueue(comp);
	auto path_map = PathMap();
	path_map.emplace(&start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = top.second.get().getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = unit.getMobility().getCost(edge);

			if (unit.getMobility().canPass(getUnit(edge._cell)) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= unit.getMobility().getMove() && (path_map.count(&edge._cell) == 0 || cost.value() < path_map.at(&edge._cell).first)) {
					path_map.insert_or_assign(&edge._cell, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell);
				}
			}
		}
	}
	return path_map;
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