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
	std::optional<int> getCost(const MobilityType mobility_type) const;
	std::optional<int> getCost(const Mobility mobility) const;
	std::optional<int> getCost(const MobilitySet mobility_type) const;
	std::optional<int> getCost(const MobilitySet mobility_type, bool intangible) const;

	bool operator==(const CellEdge & c) const;
};

