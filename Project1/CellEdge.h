#pragma once
class GridCell;
#include <array>
#include "MobilityList.h"
#include <optional>
/**
Represents an Edge to a GridCell, basically a struct
*/
class CellEdge {
private:
	const MobilityList<std::optional<int>> _costs;
	bool canPass(bool intangible);
public:
	GridCell * const _cell;
	CellEdge(GridCell* cell, MobilityList<std::optional<int>> costs);
	std::optional<int> getCost(MobilityType mobility);
	std::optional<int> getCost(MobilityList<bool> mobility_type, bool intangible);
	bool canTraverse(MobilityType mobility);
	bool operator==(const CellEdge & c) const;
};

