#pragma once
#include "GridCell.h"
#include <optional>
#include <array>

class GridCell;
class CellEdge {
private:
	const MobilityList<std::optional<int>> _costs = MobilityList<std::optional<int>>();
	bool canPass(bool intangible) const;
public:
	CellEdge(const CellEdge& cell) = default;
	CellEdge(CellEdge&& cell) = default;

	GridCell& _cell;
	CellEdge(GridCell& cell, MobilityList<std::optional<int>> costs);
	std::optional<int> getCost(MobilityType mobility) const;
	std::optional<int> getCost(MobilityList<bool> mobility_type) const;
	std::optional<int> getCost(MobilityList<bool> mobility_type, bool intangible) const;

	bool operator==(const CellEdge & c) const;
};

