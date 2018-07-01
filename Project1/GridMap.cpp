#include "GridMap.h"
#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "GridCell.h"
//#include "CellPath.h"
#include "CellEdge.h"
#include "Mobility.h"
#include "Passkey.h"

template<typename Lambda>
id_cost_map getShortestPathsHelper(ID start, int max_move, MobilitySet mobility, Lambda canPass, const GridMap& map) {
	PathQueue queue = PathQueue();
	id_cost_map path_map = id_cost_map();
	path_map.emplace(start, CostID(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = map[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility);
			if (canPass(map.getUnit(edge._id)) && cost.has_value()) {
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

//Non- const getShortestPathsMap()//
/////////////////////////////////////////////////////////////////////////

PathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility) {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return getShortestPathsMap(start, max_move, mobility, intangible);
}

PathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) {
	return PathMap( *this, getShortestPathsHelper(start, max_move, mobility, [intangible](const Unit* unit) { return intangible || unit == nullptr; }, *this));
}
PathMap GridMap::getShortestPathsMap(const Unit& unit) {
	return PathMap( *this, getShortestPathsHelper((*this)[unit], unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit](const Unit* other) { return unit.getMobility().canPass(other); }, * this));
}
//const getShortestPathsMap()//
/////////////////////////////////////////////////////////////////////////

constPathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return getShortestPathsMap(start, max_move, mobility, intangible);
}

constPathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const {
	return constPathMap(*this, getShortestPathsHelper(start, max_move, mobility, [intangible](const Unit* unit) { return intangible || unit == nullptr; }, *this));
}

constPathMap GridMap::getShortestPathsMap(const Unit& unit) const{
	return constPathMap(*this, getShortestPathsHelper((*this)[unit], unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit](const Unit* other) { return unit.getMobility().canPass(other); }, *this));
}
// private helper methods for getShortestPathsMap() //
/////////////////////////////////////////////////////////////////////////

/*
CellPath<GridCell> GridMap::getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility) {
	PathMap path_map = getShortestPathsMap(start, max_move, mobility);
	auto path = std::list<GridCell::Ref>();
	path.emplace_front((*this)[destination]);
	while (start != path.front().get()._id) {
		path.emplace_front(path_map[path.front()].second);
	}
	return CellPath<GridCell>(mobility, path);
}
*/
