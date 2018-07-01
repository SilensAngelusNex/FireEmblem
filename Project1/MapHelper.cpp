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

struct allies { static bool hasUnit(const PartyBase* party, const GridMap& map, ID pos) { return map.hasUnit(pos) && party->hasUnit(*map.getUnit(pos)); } };
struct enemies { static bool hasUnit(const PartyBase* party, const GridMap& map, ID pos) { return map.hasUnit(pos) && !party->hasUnit(*map.getUnit(pos)); } };
struct all { static bool hasUnit(const PartyBase*  /*unused*/, const GridMap&  /*unused*/, ID  /*unused*/) { return true; } };

template<typename hasUnit>
std::vector<GridCell::Ref> getCellsWithinHelper(Range range, ID pos, const PartyBase* party,  GridMap& map) {
	PathMap path_map = map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<GridCell::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (hasUnit::hasUnit(party, map, pair.first._id)) {
				vec.emplace_back(pair.first);
}
		}
	}
	return vec;
}

template<typename hasUnit>
std::vector<ID> getIDsWithinHelper(Range range, ID pos, const PartyBase* party,  GridMap& map) {
	PathMap path_map = map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<ID>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first)) {
			if (hasUnit::hasUnit(party, map, pair.first._id)) {
				vec.emplace_back(pair.first._id);
}
		}
	}
	return vec;
}

template<typename hasUnit>
std::vector<Unit::Ref> getUnitsWithinHelper(Range range, ID pos, const PartyBase * party, GridMap& map) {
	PathMap path_map = map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<Unit::Ref>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first) && map.hasUnit(pair.first)) {
			if (hasUnit::hasUnit(party, map, pair.first._id)) {
				vec.emplace_back(map[pair.first]);
}
		}
	}
	return vec;
}


std::vector<Unit::Ref> MapHelper::getUnits() {
	return std::as_const(*this).getUnits();
}
std::vector<Unit::Ref> MapHelper::getAllies(const Unit& unit) {
	return std::as_const(*this).getAllies(unit);
}
std::vector<Unit::Ref> MapHelper::getEnemies(const Unit& unit) {
	return std::as_const(*this).getEnemies(unit);
}

const std::vector<Unit::Ref> MapHelper::getUnits() const{
	auto vec = std::vector<Unit::Ref>();
	for (auto& party : _map._parties) {
		for (auto& unit : party) {
			vec.emplace_back(*unit);
		}
	}
	return vec;
}
const std::vector<Unit::Ref> MapHelper::getAllies(const Unit& unit) const{
	Expects(_map.hasUnit(unit));
	auto vec = std::vector<Unit::Ref>(); 
	for (auto& unit_ptr : _map.getParty(unit)) {
		vec.emplace_back(*unit_ptr);
	}
	return vec;
}
const std::vector<Unit::Ref> MapHelper::getEnemies(const Unit& unit) const{
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
	return getUnitsWithinHelper<all>(range, _map[unit], unit.getParty(), _map);
}

const std::vector<Unit::Ref> MapHelper::getUnitsWithin(const Unit& unit, Range range) const{
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<all>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::Ref> MapHelper::getAlliesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<allies>(range, _map[unit], unit.getParty(), _map);
}

const std::vector<Unit::Ref> MapHelper::getAlliesWithin(const Unit& unit, Range range) const{
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<allies>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::Ref> MapHelper::getEnemiesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<enemies>(range, _map[unit], unit.getParty(), _map);
}

const std::vector<Unit::Ref> MapHelper::getEnemiesWithin(const Unit& unit, Range range) const{
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<enemies>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::Ref> MapHelper::getUnitsWithin(Range range,ID pos) {
	return getUnitsWithinHelper<all>(range, pos, nullptr, _map);
}

const std::vector<Unit::Ref> MapHelper::getUnitsWithin(Range range, ID pos) const{
	return getUnitsWithinHelper<all>(range, pos, nullptr, _map);
}

std::vector<Unit::Ref> MapHelper::getAlliesWithin(Range range, ID pos, const PartyBase& party) {
	return getUnitsWithinHelper<allies>(range, pos, &party, _map);
}

const std::vector<Unit::Ref> MapHelper::getAlliesWithin(Range range, ID pos, const PartyBase& party) const {
	return getUnitsWithinHelper<allies>(range, pos, &party, _map);
}

std::vector<Unit::Ref> MapHelper::getEnemiesWithin(Range range, ID pos, const PartyBase& party) {
	return getUnitsWithinHelper<enemies>(range, pos, &party, _map);
}

const std::vector<Unit::Ref> MapHelper::getEnemiesWithin(Range range, ID pos, const PartyBase& party) const{
	return getUnitsWithinHelper<enemies>(range, pos, &party, _map);
}


std::vector<GridCell::Ref> MapHelper::getCellsWithin(Range range, ID pos) {
	return getCellsWithinHelper<all>(range, pos, nullptr, _map);
}

const std::vector<GridCell::Ref> MapHelper::getCellsWithin(Range range, ID pos) const{
	return getCellsWithinHelper<all>(range, pos, nullptr, _map);
}

std::vector<GridCell::Ref> MapHelper::getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) {
	return getCellsWithinHelper<allies>(range, pos, &party, _map);
}

const std::vector<GridCell::Ref> MapHelper::getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) const{
	return getCellsWithinHelper<allies>(range, pos, &party, _map);
}

std::vector<GridCell::Ref> MapHelper::getEnemyCellsWithin(Range range, ID pos, const PartyBase & party) {
	return getCellsWithinHelper<enemies>(range, pos, &party, _map);
}

const std::vector<GridCell::Ref> MapHelper::getEnemyCellsWithin(Range range, ID pos, const PartyBase & party) const{
	return getCellsWithinHelper<enemies>(range, pos, &party, _map);
}

std::vector<ID> MapHelper::getCellIDsWithin(Range range, ID pos) const {
	return getIDsWithinHelper<all>(range, pos, nullptr, _map);
}

std::vector<ID> MapHelper::getAlliedCellIDsWithin(Range range, ID pos, const PartyBase& party) const{
	return getIDsWithinHelper<allies>(range, pos, &party, _map);
}

std::vector<ID> MapHelper::getEnemyCellIDsWithin(Range range, ID pos, const PartyBase & party) const{
	return getIDsWithinHelper<enemies>(range, pos, &party, _map);
}


