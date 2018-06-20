#pragma once
class GridCell;
class Mobility;
#include <array>
#include "MobilityList.h"
#include <optional>
/**
Represents an Edge to a GridCell, basically a struct
*/
class CellEdge {
private:
	const MobilityCostSet _costs = MobilityCostSet();
public:
	CellEdge(const CellEdge& cell) = default;
	CellEdge(CellEdge&& cell) = default;

	GridCell& _cell;
	CellEdge(GridCell& cell, MobilityCostSet costs);
	std::optional<int> getCost(MobilityType mobility) const;
	std::optional<int> getCost(MobilitySet mobility_type) const;
	std::optional<int> getCost(MobilitySet mobility_type, bool intangible) const;

	bool operator==(const CellEdge & c) const;
	bool operator!=(const CellEdge & c) const;
};

