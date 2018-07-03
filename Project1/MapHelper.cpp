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

template<typename hasUnit, typename ReturnType>
std::vector<ReturnType> getCellsWithinHelper(Range range, ID pos, const PartyBase* party,  GridMap& map) {
	PathMap path_map = map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<ReturnType>();
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

template<typename hasUnit, typename ReturnType>
std::vector<ReturnType> getUnitsWithinHelper(Range range, ID pos, const PartyBase * party, GridMap& map) {
	PathMap path_map = map.getShortestPathsMap(pos, range.maxRange(), range._type);
	auto vec = std::vector<ReturnType>();
	for (auto pair : path_map) {
		if (range.hasDistance(pair.second.first) && map.hasUnit(pair.first)) {
			if (hasUnit::hasUnit(party, map, pair.first._id)) {
				vec.emplace_back(map[pair.first]);
}
		}
	}
	return vec;
}


std::vector<Unit::Ref> MapHelper::getUnits()  {
	auto vec = std::vector<Unit::Ref>();
	for (auto& party : _map._parties) {
		for (auto& unit : party) {
			vec.emplace_back(*unit);
		}
	}
	return vec;
}
std::vector<Unit::Ref> MapHelper::getAllies(const Unit& unit)  {
	Expects(_map.hasUnit(unit));
	auto vec = std::vector<Unit::Ref>();
	for (auto& unit_ptr : _map.getParty(unit)) {
		vec.emplace_back(*unit_ptr);
	}
	return vec;
}
std::vector<Unit::Ref> MapHelper::getEnemies(const Unit& unit)  {
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

std::vector<Unit::ConstRef> MapHelper::getUnits() const{
	auto vec =std::vector<Unit::ConstRef>();
	for (auto& party : _map._parties) {
		for (auto& unit : party) {
			vec.emplace_back(*unit);
		}
	}
	return vec;
}
std::vector<Unit::ConstRef> MapHelper::getAllies(const Unit& unit) const{
	Expects(_map.hasUnit(unit));
	auto vec =std::vector<Unit::ConstRef>(); 
	for (auto& unit_ptr : _map.getParty(unit)) {
		vec.emplace_back(*unit_ptr);
	}
	return vec;
}
std::vector<Unit::ConstRef> MapHelper::getEnemies(const Unit& unit) const{
	Expects(_map.hasUnit(unit));
	auto vec =std::vector<Unit::ConstRef>();
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
	return getUnitsWithinHelper<all, Unit::Ref>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::ConstRef> MapHelper::getUnitsWithin(const Unit& unit, Range range) const{
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<all, Unit::ConstRef>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::Ref> MapHelper::getAlliesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<allies, Unit::Ref>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::ConstRef> MapHelper::getAlliesWithin(const Unit& unit, Range range) const{
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<allies, Unit::ConstRef>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::Ref> MapHelper::getEnemiesWithin(const Unit& unit, Range range) {
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<enemies, Unit::Ref>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::ConstRef> MapHelper::getEnemiesWithin(const Unit& unit, Range range) const{
	Expects(_map.hasUnit(unit));
	return getUnitsWithinHelper<enemies, Unit::ConstRef>(range, _map[unit], unit.getParty(), _map);
}

std::vector<Unit::Ref> MapHelper::getUnitsWithin(Range range,ID pos) {
	return getUnitsWithinHelper<all, Unit::Ref>(range, pos, nullptr, _map);
}

std::vector<Unit::ConstRef> MapHelper::getUnitsWithin(Range range, ID pos) const{
	return getUnitsWithinHelper<all, Unit::ConstRef>(range, pos, nullptr, _map);
}

std::vector<Unit::Ref> MapHelper::getAlliesWithin(Range range, ID pos, const PartyBase& party) {
	return getUnitsWithinHelper<allies, Unit::Ref>(range, pos, &party, _map);
}

std::vector<Unit::ConstRef> MapHelper::getAlliesWithin(Range range, ID pos, const PartyBase& party) const {
	return getUnitsWithinHelper<allies, Unit::ConstRef>(range, pos, &party, _map);
}

std::vector<Unit::Ref> MapHelper::getEnemiesWithin(Range range, ID pos, const PartyBase& party) {
	return getUnitsWithinHelper<enemies, Unit::Ref>(range, pos, &party, _map);
}

std::vector<Unit::ConstRef> MapHelper::getEnemiesWithin(Range range, ID pos, const PartyBase& party) const{
	return getUnitsWithinHelper<enemies, Unit::ConstRef>(range, pos, &party, _map);
}


std::vector<GridCell::Ref> MapHelper::getCellsWithin(Range range, ID pos) {
	return getCellsWithinHelper<all, GridCell::Ref>(range, pos, nullptr, _map);
}

std::vector<GridCell::ConstRef> MapHelper::getCellsWithin(Range range, ID pos) const{
	return getCellsWithinHelper<all, GridCell::ConstRef>(range, pos, nullptr, _map);
}

std::vector<GridCell::Ref> MapHelper::getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) {
	return getCellsWithinHelper<allies, GridCell::Ref>(range, pos, &party, _map);
}

std::vector<GridCell::ConstRef> MapHelper::getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) const{
	return getCellsWithinHelper<allies, GridCell::ConstRef>(range, pos, &party, _map);
}

std::vector<GridCell::Ref> MapHelper::getEnemyCellsWithin(Range range, ID pos, const PartyBase & party) {
	return getCellsWithinHelper<enemies, GridCell::Ref>(range, pos, &party, _map);
}

std::vector<GridCell::ConstRef> MapHelper::getEnemyCellsWithin(Range range, ID pos, const PartyBase & party) const{
	return getCellsWithinHelper<enemies, GridCell::ConstRef>(range, pos, &party, _map);
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


