#pragma once
#include "Tile.h"
#include "CellEdge.h"
#include <list>
#include <vector>

/** GridCell that composes the Map. Holds a Tile.
*/
class GridCell {
private:
	Tile _tile = Tile();
	std::list<CellEdge> _adjacent_cells = std::list<CellEdge>(); 
public:
	GridCell(const GridCell& cell) = default;
	GridCell(GridCell&& cell) = default;

	GridCell() = default;
	~GridCell() = default;
	GridCell(Tile tile);

	void addAdjacentCell(GridCell& new_cell);
	void addAdjacentCell(GridCell& new_cell, MobilityList<std::optional<int>> costs);
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

};
