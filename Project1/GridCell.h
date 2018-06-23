#pragma once
#include "Tile.h"
#include "CellEdge.h"
#include "ID.h"
#include <list>
#include <vector>


/** GridCell that composes the Grid. Holds a Tile.
*/
using CellRef = std::reference_wrapper<GridCell>;
using constCellRef = std::reference_wrapper<const GridCell>;
class GridCell {
	Tile _tile = Tile();
	std::list<CellEdge> _adjacent_cells = std::list<CellEdge>(); 
public:
	const ID _id;
	GridCell(const GridCell& cell) = default;
	GridCell(GridCell&& cell) = default;

	~GridCell() = default;
	GridCell(Tile tile, ID id);

	void addAdjacentCell(GridCell& new_cell);
	void addAdjacentCell(GridCell& new_cell, MobilityCostSet costs);
	void removeAdjacentCell(const GridCell& delete_cell);

	Tile& getTile();
	std::list<CellEdge> getEdges();
	std::optional<CellEdge> getEdge(const GridCell& other_cell);
	std::vector<GridCell*> getAdjacentCells();

	bool isAdjacent(const GridCell& other_cell) const;
	bool isAdjacent(const GridCell& other_cell, MobilityType mobility) const;
	bool isAdjacent(const GridCell& other_cell, MobilitySet mobility) const;

	const Tile& getTile() const;
	const std::list<CellEdge> getEdges() const;
	const std::optional<CellEdge> getEdge(const GridCell & other_cell) const;
	const std::vector<GridCell*> getAdjacentCells() const;

	bool operator==(const GridCell& cell) const;
	bool operator!=(const GridCell& cell) const;
};
