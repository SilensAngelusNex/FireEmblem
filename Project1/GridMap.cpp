#include "GridMap.h"
#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "GridCell.h"
//#include "CellPath.h"
#include "CellEdge.h"
#include "Mobility.h"
#include "Passkey.h"


//Constructors//
/////////////////////////////////////////////////////////////////////////
GridMap::GridMap(int width, int height) :
	Grid(width, height)
{}

GridMap::GridMap(int width, int height, std::vector<PartyData> data) :
	Grid(width, height, data)
{}

//Party Access//
/////////////////////////////////////////////////////////////////////////
Party& GridMap::getParty(const Unit & unit) {
	for (auto & party : _parties) {
		if (*unit.getParty() == party) {
			return party;
		}
	}
	Expects(false);
}

const Party& GridMap::getParty(const Unit & unit) const {
	return unit.getParty()->getParty(Passkey<GridMap>());
}

//Non- const findShortestPaths()//
/////////////////////////////////////////////////////////////////////////

PathMap GridMap::findShortestPaths(ID start) {
	return PathMap(*this, getShortestPaths(start, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false));
}

PathMap GridMap::findShortestPaths(size_t x, size_t y) {
	return PathMap(*this, getShortestPaths((*this)[x][y]._id, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false));
}

PathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility) {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return PathMap(*this, getShortestPaths(start, max_move, mobility, intangible));
}

PathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) {
	return PathMap(*this, getShortestPaths(start, max_move, mobility, intangible));
}

PathMap GridMap::findShortestPaths(const Unit& unit) {
	return PathMap(*this, getShortestPaths(unit));
}

//const findShortestPaths()//
/////////////////////////////////////////////////////////////////////////
constPathMap GridMap::findShortestPaths(ID start) const {
	return constPathMap(*this, getShortestPaths(start, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false));
}

constPathMap GridMap::findShortestPaths(size_t x, size_t y) const {
	return constPathMap(*this, getShortestPaths((*this)[x][y]._id, INT_MAX, MobilitySet(MobilityType::values::GROUNDED), false));
}

constPathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return constPathMap(*this, getShortestPaths(start, max_move, mobility, intangible));
}

constPathMap GridMap::findShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) const {
	return constPathMap(*this, getShortestPaths(start, max_move, mobility, intangible));
}
constPathMap GridMap::findShortestPaths(const Unit& unit) const {
	return constPathMap(*this, getShortestPaths(unit));
}

// private helper methods for findShortestPaths() //
/////////////////////////////////////////////////////////////////////////


id_cost_map GridMap::getShortestPaths(const Unit& unit) const {
	const GridCell& start = (*this)[unit];
	PathQueue queue = PathQueue();
	id_cost_map path_map = id_cost_map();
	path_map.emplace(start._id, CostID(0, start._id));
	queue.emplace(0, start._id);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = (*this)[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = unit.getMobility().getCost(edge);
			if (unit.getMobility().canPass(getUnit((*this)[edge._id])) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= unit.getMobility().getMove() && (path_map.count(edge._id) == 0 || cost.value() < path_map.at(edge._id).first)) {
					path_map.insert_or_assign(edge._id, CostID(cost.value(), top.second));
					queue.emplace(cost.value(), edge._id);
				}
			}
		}
	}
	return path_map;
}

id_cost_map GridMap::getShortestPaths(ID start, int max_move, MobilitySet mobility, bool intangible) const {
	PathQueue queue = PathQueue();
	id_cost_map path_map = id_cost_map();
	path_map.emplace(start, CostID(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		CostID top = queue.top();
		queue.pop();
		top.second;
		std::list<CellEdge> adj_edges = (*this)[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility, intangible);
			if ((!hasUnit((*this)[edge._id]) || intangible) && cost.has_value()) {
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

/*
CellPath<GridCell> GridMap::getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility) {
	PathMap path_map = findShortestPaths(start, max_move, mobility);
	auto path = std::list<CellRef>();
	path.emplace_front((*this)[destination]);
	while (start != path.front().get()._id) {
		path.emplace_front(path_map[path.front()].second);
	}
	return CellPath<GridCell>(mobility, path);
}
*/