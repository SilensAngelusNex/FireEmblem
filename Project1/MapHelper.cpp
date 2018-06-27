#include "MapHelper.h"
#include "GridMap.h"
#include "PathMap.h"
#include "Unit.h"
#include "GridCell.h"
#include "PartyBase.h"
#include "Range.h"
#include <vector>


MapHelper::MapHelper(GridMap & map) :
	_map(map)
{}

std::vector<UnitRef> MapHelper::getUnits() {
	return std::vector<UnitRef>();
}
std::vector<UnitRef> MapHelper::getAllies(const Unit& unit) {
	Expects(_map.hasUnit(unit));
	return std::vector<UnitRef>();
}
std::vector<UnitRef> MapHelper::getEnemies(const Unit& unit) {
	Expects(_map.hasUnit(unit));
	return std::vector<UnitRef>();
}

std::vector<UnitRef> MapHelper::getUnitsWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithin(range, _map[unit]);
}
std::vector<UnitRef> MapHelper::getAlliesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return std::vector<UnitRef>();
}
std::vector<UnitRef> MapHelper::getEnemiesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return std::vector<UnitRef>();
}

std::vector<UnitRef> MapHelper::getUnitsWithin(Range range, GridCell& pos) {
	std::vector<CellRef> cells = getCellsWithin(range, pos);
	auto vec = std::vector<UnitRef>();
	for (auto cell: cells) {
		if (_map.hasUnit(cell)) {
			vec.emplace_back(_map[cell]);
		}
	}
	return vec;
}


std::vector<UnitRef> MapHelper::getAlliesWithin(Range range, GridCell& pos, const PartyBase& party) {
	std::vector<CellRef> cells = getAlliedCellsWithin(range, pos, party);
	auto vec = std::vector<UnitRef>();
	for (auto cell : cells) {
		vec.emplace_back(_map[cell]);
	}
	return vec;
}
std::vector<UnitRef> MapHelper::getEnemiesWithin(Range range, GridCell& pos, const PartyBase& party) {
	std::vector<CellRef> cells = getEnemyCellsWithin(range, pos, party);
	auto vec = std::vector<UnitRef>();
	for (auto cell : cells) {
		vec.emplace_back(_map[cell]);
	}
	return vec;
}

/*
Bool Range::hasDistance(int dist) const{
return _range[(dist + 9)/10];
}

*/

std::vector<CellRef> MapHelper::getCellsWithin(Range range, GridCell& pos) {
	PathMap path_map = _map.findShortestPaths(pos._id, range.maxRange(), range._type);
	auto vec = std::vector<CellRef>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			vec.emplace_back(pair.first);
		}
	}
	return vec;
}

std::vector<CellRef> MapHelper::getAlliedCellsWithin(Range range, GridCell & pos, const PartyBase& party) {
	PathMap path_map = _map.findShortestPaths(pos._id, range.maxRange(), range._type);
	auto vec = std::vector<CellRef>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (_map.hasUnit(pair.first) && party.hasUnit(_map[pair.first]))
				vec.emplace_back(pair.first);
		}
	}
	return vec;
}

std::vector<CellRef> MapHelper::getEnemyCellsWithin(Range range, GridCell & pos, const PartyBase & party) {
	PathMap path_map = _map.findShortestPaths(pos._id, range.maxRange(), range._type);
	auto vec = std::vector<CellRef>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (_map.hasUnit(pair.first) && !party.hasUnit(_map[pair.first]))
				vec.emplace_back(pair.first);
		}
	}
	return vec;
}
