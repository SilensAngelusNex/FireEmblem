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
	return std::as_const(*this).findShortestPaths(_grid[x][y]._id, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

PathMap GridMap::findShortestPaths(ID start) {
	return std::as_const(*this).findShortestPaths(start, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

PathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility) {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return std::as_const(*this).findShortestPaths(start, max_move, mobility, intangible);
}

PathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) {
	return std::as_const(*this).findShortestPaths(start, max_move, mobility, intangible);
}

PathMap GridMap::findShortestPaths(const Unit & unit) {
	return std::as_const(*this).findShortestPaths(unit);
}

const PathMap GridMap::findShortestPaths(size_t x, size_t y) const {
	return findShortestPaths((*this)[x][y]._id, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

const PathMap GridMap::findShortestPaths(ID start) const {
	return findShortestPaths(start, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false);
}

const PathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return findShortestPaths(start, max_move, mobility, intangible);
}

const PathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) const {
	PathQueue queue = PathQueue(comp);
	PathMap path_map = PathMap();
	path_map.emplace(start, CellCost(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		CellCost top = queue.top();
		queue.pop();
		top.second;
		std::list<CellEdge> adj_edges = (*this)[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if ((!hasUnit(edge._cell) || intangible) && cost.has_value()) {
				cost = top.first + cost.value();
				if (cost.value() <= max_move && (path_map.count(edge._cell._id) == 0 || cost.value() < path_map.at(edge._cell._id).first)) {
					path_map.insert_or_assign(edge._cell._id, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell._id);
				}
			}
		}
	}
	return path_map;
}

 const PathMap GridMap::findShortestPaths(const Unit& unit) const{
	const GridCell& start = (*this)[unit];
	auto queue = PathQueue(comp);
	auto path_map = PathMap();
	path_map.emplace(start._id, CellCost(0, start._id));
	queue.emplace(0, start._id);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = (*this)[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = unit.getMobility().getCost(edge);
			if (unit.getMobility().canPass(getUnit(edge._cell)) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= unit.getMobility().getMove() && (path_map.count(edge._cell._id) == 0 || cost.value() < path_map.at(edge._cell._id).first)) {
					path_map.insert_or_assign(edge._cell._id, CellCost(cost.value(), top.second));
					queue.emplace(cost.value(), edge._cell._id);
				}
			}
		}
	}
	return path_map;
}

/*
CellPath GridMap::getShortestPath(GridCell & start, GridCell & destination, int max_move, MobilitySet mobility) {
	PathMap path_map = findShortestPaths(start._id, max_move, mobility);
	std::list<CellRef> path = std::list<CellRef>();
	path.push_front(destination);
	while (!(start == path.front().get())) {
		path.push_front(path_map.at(&path.front().get()).second);
	}
	return CellPath(path, mobility);
}*/