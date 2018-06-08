#pragma once
#include "Tile.h"
#include <algorithm>
#include <list>
#include <optional>
/** GridCell that composes the Map. Holds a Tile.
*/
class GridCell {
private:
	Tile _tile = Tile();
	std::list<CellEdge> _adjacent_cells = std::list<CellEdge>(); 
public:
	GridCell() = default;
	~GridCell() = default;
	GridCell(Tile tile);

	void addAdjacentCell(GridCell& new_cell);
	void addAdjacentCell(GridCell& new_cell, MobilityList<std::optional<int>> costs);
	void removeAdjacentCell(GridCell& delete_cell);
	Tile& getTile();
	std::list<CellEdge> getEdges();
	std::optional<CellEdge> getEdge(GridCell& other_cell);
	std::vector<GridCell*> getAdjacentCells();

	bool isAdjacent(GridCell& other_cell) const;
	std::list<CellEdge> getEdges() const;
	const Tile& getTile() const;
	const std::optional<CellEdge> getEdge(GridCell & other_cell) const;

	bool operator==(const GridCell& cell) const;

	

};

