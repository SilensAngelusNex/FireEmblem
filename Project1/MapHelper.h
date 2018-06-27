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
	
	std::vector<UnitRef> getUnits();
	std::vector<UnitRef> getAllies(const Unit& unit);
	std::vector<UnitRef> getEnemies(const Unit& unit);

	std::vector<UnitRef> getUnitsWithin(const Unit& unit, Range range);
	std::vector<UnitRef> getAlliesWithin(const Unit& unit, Range range);
	std::vector<UnitRef> getEnemiesWithin(const Unit& unit, Range range);

	std::vector<UnitRef> getUnitsWithin(Range range, GridCell& pos);
	std::vector<UnitRef> getAlliesWithin(Range range, GridCell& pos, const PartyBase& party);
	std::vector<UnitRef> getEnemiesWithin(Range range, GridCell& pos, const PartyBase& party);

	std::vector<CellRef> getCellsWithin(Range range, GridCell & pos);
	std::vector<CellRef> getAlliedCellsWithin(Range range, GridCell & pos, const PartyBase& party);
	std::vector<CellRef> getEnemyCellsWithin(Range range, GridCell & pos, const PartyBase& party);
	//std::vector<CellRef> getCellsWithin(Range range, GridCell& pos);
};

