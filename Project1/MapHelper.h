#pragma once
#include "PartyBase.h"
#include "GridCell.h"
#include "Unit.h"
#include <vector>

#include "GridMap.h"

class Range;

class MapHelper {
protected:
	GridMap& _map;
	MapHelper(GridMap& map);
public:
	~MapHelper() = default;

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
	std::vector<GridCell::Ref> getAlliedCellsWithin(Range range, ID pos, const PartyBase& party);
	std::vector<GridCell::Ref> getEnemyCellsWithin(Range range, ID pos, const PartyBase& party);

	std::vector<Unit::ConstRef> getUnits() const;
	std::vector<Unit::ConstRef> getAllies(const Unit& unit) const;
	std::vector<Unit::ConstRef> getEnemies(const Unit& unit) const;

	std::vector<Unit::ConstRef> getUnitsWithin(const Unit& unit, Range range) const;
	std::vector<Unit::ConstRef> getAlliesWithin(const Unit& unit, Range range) const;
	std::vector<Unit::ConstRef> getEnemiesWithin(const Unit& unit, Range range) const;

	std::vector<Unit::ConstRef> getUnitsWithin(Range range, ID pos) const;
	std::vector<Unit::ConstRef> getAlliesWithin(Range range, ID pos, const PartyBase& party) const;
	std::vector<Unit::ConstRef> getEnemiesWithin(Range range, ID pos, const PartyBase& party) const;

	std::vector<GridCell::ConstRef> getCellsWithin(Range range, ID pos) const;
	std::vector<GridCell::ConstRef> getAlliedCellsWithin(Range range, ID pos, const PartyBase& party) const;
	std::vector<GridCell::ConstRef> getEnemyCellsWithin(Range range, ID pos, const PartyBase& party) const;

	 std::vector<ID> getCellIDsWithin(Range range, ID pos) const ;
	 std::vector<ID> getAlliedCellIDsWithin(Range range, ID pos, const PartyBase& party) const;
	 std::vector<ID> getEnemyCellIDsWithin(Range range, ID pos, const PartyBase& party) const;
};
