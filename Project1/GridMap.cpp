#include "GridMap.h"
#include "Grid.h"
#include "Party.h"
#include "Unit.h"
#include "GridCell.h"
#include "CellEdge.h"
#include "Mobility.h"
#include "Passkey.h"
#include "id_cost_map.h"

template<typename Lambda>
id_cost_map getShortestPathsHelper(ID start, int max_move, MobilitySet mobility, Lambda canPass, const GridMap& map) {
	PathQueue queue = PathQueue();
	id_cost_map cost_map = id_cost_map(map[start]);
	cost_map.emplace(start, CostID(0, start));
	queue.emplace(0, start);

	while (!queue.empty()) {
		auto top = queue.top();
		queue.pop();
		std::list<CellEdge> adj_edges = map[top.second].getEdges();
		for (auto& edge : adj_edges) {
			std::optional<int> cost = edge.getCost(mobility);
			if (canPass(edge) && cost.has_value()) {
				cost = top.first + cost.value();

				if (cost.value() <= max_move && (!cost_map.hasKey(edge._id) || cost.value() < cost_map.at(edge._id).first)) {
					cost_map.insert_or_assign(edge._id, CostID(cost.value(), top.second));
					queue.emplace(cost.value(), edge._id);
				}
			}
		}
	}
	return cost_map;
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

CostMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility) {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return getShortestPathsMap(start, max_move, mobility, intangible);
}

CostMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) {
	return CostMap( *this, getShortestPathsHelper(start, max_move, mobility, [intangible, this](CellEdge edge) { return intangible || !hasUnit(edge._id); }, *this));
}
CostMap GridMap::getShortestPathsMap(const Unit& unit) {
	return CostMap( *this, getShortestPathsHelper((*this)[unit], unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit, this](CellEdge edge) { return unit.getMobility().canPass(getUnit(edge._id)); }, * this));
}
CostMap GridMap::getShortestPathsMap(const Unit & unit, ID start) {
	return CostMap(*this, getShortestPathsHelper(start, unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit, this](CellEdge edge) { return unit.getMobility().canPass(getUnit(edge._id)); }, *this));
}

CostMap GridMap::getShortestPathsMap(const Unit & unit, ID start, int remaining_move) {
	return CostMap(*this, getShortestPathsHelper(start, remaining_move, unit.getMobility().getMobilitySet(), [&unit, this](CellEdge edge) { return unit.getMobility().canPass(getUnit(edge._id)); }, *this));
}

//const getShortestPathsMap()//
/////////////////////////////////////////////////////////////////////////

constCostMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return getShortestPathsMap(start, max_move, mobility, intangible);
}

constCostMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const {
	return constCostMap(*this, getShortestPathsHelper(start, max_move, mobility, [intangible, this](CellEdge edge) { return intangible || !hasUnit(edge._id); }, *this));
}

constCostMap GridMap::getShortestPathsMap(const Unit& unit) const{
	return constCostMap(*this, getShortestPathsHelper((*this)[unit], unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit, this](CellEdge edge) { return unit.getMobility().canPass(getUnit(edge._id)); }, *this));
}

constCostMap GridMap::getShortestPathsMap(const Unit & unit, ID start) const{
	return constCostMap(*this, getShortestPathsHelper(start, unit.getMobility().getMove(), unit.getMobility().getMobilitySet(), [&unit, this](CellEdge edge) { return unit.getMobility().canPass(getUnit(edge._id)); }, *this));
}

constCostMap GridMap::getShortestPathsMap(const Unit & unit, ID start, int remaining_move) const{
	return constCostMap(*this, getShortestPathsHelper(start, remaining_move, unit.getMobility().getMobilitySet(), [&unit, this](CellEdge edge) { return unit.getMobility().canPass(getUnit(edge._id)); }, *this));
}
// private helper methods for getShortestPathsMap() //
/////////////////////////////////////////////////////////////////////////

/*
CellPath<GridCell> GridMap::getShortestPath(ID start, ID destination, int max_move, MobilitySet mobility) {
	CostMap cell_cost_map = getShortestPathsMap(start, max_move, mobility);
	auto path = std::list<GridCell::Ref>();
	path.emplace_front((*this)[destination]);
	while (start != path.front().get()._id) {
		path.emplace_front(cell_cost_map[path.front()].second);
	}
	return CellPath<GridCell>(mobility, path);
}
*/
