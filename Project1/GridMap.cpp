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

//Non- const getShortestPathsMap()//
/////////////////////////////////////////////////////////////////////////

PathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility) {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return getShortestPathsMap(start, max_move, mobility, intangible);
}

PathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) {
	return PathMap(*this, getShortestPathsHelper(start, max_move, mobility, [intangible](const Unit* unit) { return intangible || unit == nullptr; }));
}

//const getShortestPathsMap()//
/////////////////////////////////////////////////////////////////////////

constPathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility) const {
	bool intangible = mobility[MobilityType::values::PROJECTILE] || mobility[MobilityType::values::ETHEREAL];
	return getShortestPathsMap(start, max_move, mobility, intangible);
}

constPathMap GridMap::getShortestPathsMap(ID start, int max_move, MobilitySet mobility, bool intangible) const {
	return constPathMap(*this, getShortestPathsHelper(start, max_move, mobility, [intangible](const Unit* unit) { return intangible || unit == nullptr; }));
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

