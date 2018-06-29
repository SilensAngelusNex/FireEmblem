#pragma once
#include "PartyBase.h"
#include "GridCell.h"
#include "Unit.h"
#include <vector>

class GridMap;
class Range;

class MapHelper
{
protected:
	GridMap& _map;
	MapHelper(GridMap& map);
	~MapHelper() = default;
public:
	
	std::vector<Unit::Ref> getUnits();
	std::vector<Unit::Ref> getAllies(const Unit& unit);
	std::vector<Unit::Ref> getEnemies(const Unit& unit);

	std::vector<Unit::Ref> getUnitsWithin(const Unit& unit, Range range);
	std::vector<Unit::Ref> getAlliesWithin(const Unit& unit, Range range);
	std::vector<Unit::Ref> getEnemiesWithin(const Unit& unit, Range range);

	std::vector<Unit::Ref> getUnitsWithin(Range range, ID pos);
	std::vector<Unit::Ref> getAlliesWithin(Range range, ID pos, const PartyBase& party);
	std::vector<Unit::Ref> getEnemiesWithin(Range range, ID pos, const PartyBase& party);

	std::vector<GridCell::Ref> getCellsWithin(Range range, ID pos);
	std::vector<GridCell::Ref> getAlliedCellsWithin(Range range, ID, const PartyBase& party);
	std::vector<GridCell::Ref> getEnemyCellsWithin(Range range, ID, const PartyBase& party);
	//std::vector<GridCell::Ref> getCellsWithin(Range range, GridCell& pos);
};

