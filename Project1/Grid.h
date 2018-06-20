#pragma once
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "CellPath.h"
#include "Party.h"
/**
Grid class. Holds a Matrix of GridCells. Should be initialized at the start of each chapter.
*/
class GridCell;
class Unit;
class Mobility;

class Grid {
public:
	//vector wrapper that only allows [] op
	class grid_row {
	private:
		std::vector<GridCell>& _row;
		grid_row(std::vector<GridCell>& row);
		~grid_row() = default;
	public:
		GridCell& operator[](size_t index);
		const GridCell& operator[](size_t index) const;
		friend class Grid;
	};
	//const vector wrapper that only allows [] op
	class const_grid_row {
	private:
		const std::vector<GridCell>& _row;
		const_grid_row(const std::vector<GridCell>& row);
		~const_grid_row() = default;
	public:
		const GridCell& operator[](size_t index) const;
		friend class Grid;
	};
private:

	std::map<const Unit*, GridCell*> _unit_to_cell;
	std::map<const GridCell*, Unit*> _cell_to_unit;

	void insertAdjacencies();
	

protected:
	std::vector<std::vector<GridCell>> _grid;

	Grid(int width, int height);
	Grid(int width, int height, std::vector<PartyData> data);
	~Grid() = default;

	Unit* getUnit(const GridCell& index);
	const Unit* getUnit(const GridCell& index) const;
public:
	
	std::list<Party> _parties;

	Grid(const Grid& map) = delete;
	Grid& operator=(const Grid & map) = delete;
	Grid(Grid&& map) = default;
	Grid& operator=(Grid&& map) = default;
		
	void insertParty(PartyData data);
	void moveUnit(GridCell& start, GridCell& destination);
	void insertUnit(Unit& new_unit, GridCell& destination);
	void removeUnit(Unit& unit);
	
	bool hasUnit(const GridCell & index) const;
	bool hasUnit(const Unit & unit) const;

	Unit& operator[](const GridCell& index);
	GridCell& operator[](const Unit& index);
	grid_row operator[](size_t index);

	const Unit& operator[](const GridCell& index) const;
	const GridCell& operator[](const Unit& index) const;
	const_grid_row operator[](size_t index) const;

};
