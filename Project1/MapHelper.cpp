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
	auto vec = std::vector<Unit::Ref>();
	for (auto& party : _map._parties) {
		for (auto& unit : party) {
			vec.emplace_back(*unit);
		}
	}
	return vec;
}
std::vector<Unit::Ref> MapHelper::getAllies(const Unit& unit) {
	Expects(_map.hasUnit(unit));
	auto vec = std::vector<Unit::Ref>(); 
	for (auto& unit_ptr : _map.getParty(unit)) {
		vec.emplace_back(*unit_ptr);
	}
	return vec;
}
std::vector<Unit::Ref> MapHelper::getEnemies(const Unit& unit) {
	Expects(_map.hasUnit(unit));
	auto vec = std::vector<Unit::Ref>();
	for (auto& party : _map._parties) {
		if (_map.getParty(unit) != party) {
			for (auto& unit : party) {
				vec.emplace_back(*unit);
			}
		}
	}
	return vec;
}

std::vector<Unit::Ref> MapHelper::getUnitsWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<all>(range, _map[unit], unit.getParty());
}
std::vector<Unit::Ref> MapHelper::getAlliesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<allies>(range, _map[unit], unit.getParty());
}
std::vector<Unit::Ref> MapHelper::getEnemiesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<enemies>(range, _map[unit], unit.getParty());
}

std::vector<Unit::Ref> MapHelper::getUnitsWithin(Range range,ID pos) {
	return getUnitsWithinHelper<all>(range, pos, nullptr);
}

std::vector<Unit::Ref> MapHelper::getAlliesWithin(Range range, ID pos, const PartyBase& party) {
	return getUnitsWithinHelper<allies>(range, pos, nullptr);
}
std::vector<Unit::Ref> MapHelper::getEnemiesWithin(Range range, ID pos, const PartyBase& party) {
	return getUnitsWithinHelper<enemies>(range, pos, nullptr);
}

std::vector<GridCell::Ref> MapHelper::getCellsWithin(Range range, ID pos) {
	return getCellsWithinHelper<all>(range, pos, nullptr);
}

std::vector<GridCell::Ref> MapHelper::getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) {
	return getCellsWithinHelper<allies>(range, pos, &party);
}

std::vector<GridCell::Ref> MapHelper::getEnemyCellsWithin(Range range, ID pos, const PartyBase & party) {
	return getCellsWithinHelper<enemies>(range, pos, &party);
}

std::vector<ID> MapHelper::getCellIDsWithin(Range range, ID pos) {
	return getIDsWithinHelper<all>(range, pos, nullptr);
}

std::vector<ID> MapHelper::getAlliedCellIDsWithin(Range range, ID pos, const PartyBase& party) {
	return getIDsWithinHelper<allies>(range, pos, &party);
}

std::vector<ID> MapHelper::getEnemyCellIDsWithin(Range range, ID pos, const PartyBase & party) {
	return getIDsWithinHelper<enemies>(range, pos, &party);
}

template<typename hasUnit>
std::vector<GridCell::Ref> MapHelper::getCellsWithinHelper(Range range, ID pos, const PartyBase* party) {
	PathMap path_map = _map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<GridCell::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if(hasUnit::hasUnit(party,_map.getUnit(pair.first), _map, pair.first._id))
			vec.emplace_back(pair.first);
		}
	}
	return vec;
}

template<typename hasUnit>
std::vector<ID> MapHelper::getIDsWithinHelper(Range range, ID pos, const PartyBase* party) {
	PathMap path_map = _map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<ID>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (hasUnit::hasUnit(party, _map.getUnit(pair.first), _map, pair.first._id))
				vec.emplace_back(pair.first._id);
		}
	}
	return vec;
}

template<typename hasUnit>
std::vector<Unit::Ref> MapHelper::getUnitsWithinHelper(Range range, ID pos, const PartyBase * party)
{
	PathMap path_map = _map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<Unit::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first) && _map.hasUnit(pair.first)) {
			if (hasUnit::hasUnit(party, _map.getUnit(pair.first), _map, pair.first._id))
				vec.emplace_back(_map[pair.first]);
		}
	}
	return vec;
}
