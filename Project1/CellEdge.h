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
	const MobilityList<std::optional<int>> _costs = MobilityList<std::optional<int>>();
	bool canPass(bool intangible) const;
public:
	CellEdge(const CellEdge& cell) = default;
	CellEdge(CellEdge&& cell) = default;

	GridCell& _cell;
	CellEdge(GridCell& cell, MobilityList<std::optional<int>> costs);
	std::optional<int> getCost(MobilityType mobility_type) const;
	std::optional<int> getCost(Mobility mobility);
	std::optional<int> getCost(MobilitySet mobility_type) const;
	std::optional<int> getCost(MobilitySet mobility_type, bool intangible) const;

	bool operator==(const CellEdge & c) const;
};

