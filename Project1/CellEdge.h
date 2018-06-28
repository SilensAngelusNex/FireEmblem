#pragma once
class Mobility;
#include <array>
#include "MobilityList.h"
#include <optional>
#include "ID.h"
/**
Represents an Edge to a GridCell, basically a struct
*/
class CellEdge {
public:
	const ID _id;
private:
	const MobilityCostSet _costs = MobilityCostSet();
public:
	CellEdge(ID id, MobilityCostSet costs);
	CellEdge(const CellEdge& cell) = default;
	CellEdge(CellEdge&& cell) = default;

	std::optional<int> getCost(MobilityType mobility) const;
	std::optional<int> getCost(MobilitySet mobility_type) const;
	std::optional<int> getCost(MobilitySet mobility_type, bool intangible) const;

	bool operator==(const CellEdge & c) const;
	bool operator!=(const CellEdge & c) const;
};

