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

std::vector<Unit::Ref> MapHelper::getUnits() {
	return std::vector<Unit::Ref>();
}
std::vector<Unit::Ref> MapHelper::getAllies(const Unit& unit) {
	Expects(_map.hasUnit(unit));
	return std::vector<Unit::Ref>();
}
std::vector<Unit::Ref> MapHelper::getEnemies(const Unit& unit) {
	Expects(_map.hasUnit(unit));
	return std::vector<Unit::Ref>();
}

std::vector<Unit::Ref> MapHelper::getUnitsWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithin(range, _map[unit]);
}
std::vector<Unit::Ref> MapHelper::getAlliesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return std::vector<Unit::Ref>();
}
std::vector<Unit::Ref> MapHelper::getEnemiesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return std::vector<Unit::Ref>();
}

std::vector<Unit::Ref> MapHelper::getUnitsWithin(Range range,ID pos) {
	std::vector<GridCell::Ref> cells = getCellsWithin(range, pos);
	auto vec = std::vector<Unit::Ref>();
	for (auto cell: cells) {
		if (_map.hasUnit(cell)) {
			vec.emplace_back(_map[cell]);
		}
	}
	return vec;
}


std::vector<Unit::Ref> MapHelper::getAlliesWithin(Range range, ID pos, const PartyBase& party) {
	std::vector<GridCell::Ref> cells = getAlliedCellsWithin(range, pos, party);
	auto vec = std::vector<Unit::Ref>();
	for (auto cell : cells) {
		vec.emplace_back(_map[cell]);
	}
	return vec;
}
std::vector<Unit::Ref> MapHelper::getEnemiesWithin(Range range, ID pos, const PartyBase& party) {
	std::vector<GridCell::Ref> cells = getEnemyCellsWithin(range, pos, party);
	auto vec = std::vector<Unit::Ref>();
	for (auto cell : cells) {
		vec.emplace_back(_map[cell]);
	}
	return vec;
}

std::vector<GridCell::Ref> MapHelper::getCellsWithin(Range range, ID pos) {
	PathMap path_map = _map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<GridCell::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			vec.emplace_back(pair.first);
		}
	}
	return vec;
}

std::vector<GridCell::Ref> MapHelper::getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) {
	PathMap path_map = _map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<GridCell::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (_map.hasUnit(pair.first) && party.hasUnit(_map[pair.first])) {
				vec.emplace_back(pair.first);
			}
		}
	}
	return vec;
}

std::vector<GridCell::Ref> MapHelper::getEnemyCellsWithin(Range range, ID pos, const PartyBase & party) {
	PathMap path_map = _map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<GridCell::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (_map.hasUnit(pair.first) && !party.hasUnit(_map[pair.first])) {
				vec.emplace_back(pair.first);
			}
		}
	}
	return vec;
}
