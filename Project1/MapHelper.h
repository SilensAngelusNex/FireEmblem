#pragma once
#include "GridCell.h"
#include <vector>

class GridMap;
class PartyBase;
class Range;
class Unit;
using UnitRef = logical_reference_wrapper<Unit>;
using UnitConstRef = logical_reference_wrapper<const Unit>;

class MapHelper {
protected:
	GridMap& _map;
	MapHelper(GridMap& map);
public:
	~MapHelper() = default;

	std::vector<UnitRef> getUnits();
	std::vector<UnitRef> getAllies(Unit& unit);
	std::vector<UnitRef> getEnemies(Unit& unit);

	std::vector<UnitRef> getUnitsWithin(Unit& unit, Range range);
	std::vector<UnitRef> getAlliesWithin(Unit& unit, Range range);
	std::vector<UnitRef> getEnemiesWithin(Unit& unit, Range range);

	std::vector<UnitRef> getUnitsWithin(Range range, ID pos);
	std::vector<UnitRef> getAlliesWithin(Range range, ID pos, const PartyBase& party);
	std::vector<UnitRef> getEnemiesWithin(Range range, ID pos, const PartyBase& party);

	std::vector<GridCell::Ref> getCellsWithin(Range range, ID pos);
	std::vector<GridCell::Ref> getAlliedCellsWithin(Range range, ID pos, const PartyBase& party);
	std::vector<GridCell::Ref> getEnemyCellsWithin(Range range, ID pos, const PartyBase& party);

	std::vector<UnitConstRef> getUnits() const;
	std::vector<UnitConstRef> getAllies(const Unit& unit) const;
	std::vector<UnitConstRef> getEnemies(const Unit& unit) const;
	
	std::vector<UnitConstRef> getUnitsWithin(const Unit& unit, Range range) const;
	std::vector<UnitConstRef> getAlliesWithin(const Unit& unit, Range range) const;
	std::vector<UnitConstRef> getEnemiesWithin(const Unit& unit, Range range) const;

	std::vector<UnitConstRef> getUnitsWithin(Range range, ID pos) const;
	std::vector<UnitConstRef> getAlliesWithin(Range range, ID pos, const PartyBase& party) const;
	std::vector<UnitConstRef> getEnemiesWithin(Range range, ID pos, const PartyBase& party) const;

	std::vector<GridCell::ConstRef> getCellsWithin(Range range, ID pos) const;
	std::vector<GridCell::ConstRef> getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) const;
	std::vector<GridCell::ConstRef> getEnemyCellsWithin(Range range, ID pos, const PartyBase& party) const;

	 std::vector<ID> getCellIDsWithin(Range range, ID pos) const ;
	 std::vector<ID> getAlliedCellIDsWithin(Range range, ID pos, const PartyBase& party) const;
	 std::vector<ID> getEnemyCellIDsWithin(Range range, ID pos, const PartyBase& party) const;
};
