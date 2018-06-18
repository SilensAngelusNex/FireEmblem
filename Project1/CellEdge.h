#pragma once
#include "MobilityList.h"
#include "Mobility.h"
#include <optional>

class GridCell;
//typedef bool(*boolFunc)(Unit* param);
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
	std::optional<int> getCost(MobilityList<bool> mobility_list) const;
	std::optional<int> getCost(MobilityList<bool> mobility_list, bool intangible) const;


	bool operator==(const CellEdge & c) const;
};

