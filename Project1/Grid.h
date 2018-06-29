#pragma once
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "Party.h"
#include "ID.h"
/**
Grid class. Holds a Matrix of GridCells. Should be initialized at the start of each chapter.
*/
class GridCell;
class Unit;
class Mobility;

class Grid {
public:
	//vector wrapper that only allows [] op
	template<typename VecCell>
	class grid_row {
	private:
		VecCell& _row;
		grid_row(VecCell& row) : _row(row) {}
	public:
		auto& operator[](size_t index) { return _row[index];}
		const auto& operator[](size_t index) const { return _row[index];}
		friend class Grid;
	};
	using GridRow = grid_row < std::vector<GridCell>>;
	using constGridRow = grid_row<const std::vector<GridCell>>;
private:

	std::map<const Unit*, GridCell*> _unit_to_cell;
	std::map<const GridCell*, Unit*> _cell_to_unit;

	void insertAdjacencies();
	

protected:
	std::vector<std::vector<GridCell>> _grid;

	Grid(int width, int height);
	Grid(int width, int height, std::vector<PartyData> data);
	~Grid() = default;

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
	
	void moveUnit(ID& start, ID& destination);
	void insertUnit(Unit& new_unit, ID& destination);

	bool hasUnit(const GridCell& index) const;
	bool hasUnit(const Unit & unit) const;
	bool hasUnit(const ID& id) const;

	Unit* getUnit(const GridCell& index);
	Unit* getUnit(const ID& id);

	const Unit* getUnit(const GridCell& index) const;
	const Unit* getUnit(const ID& id) const;

	Unit& operator[](const GridCell& index);
	GridCell& operator[](const Unit& index);
	GridCell& operator[](const ID& index);
	GridRow operator[](size_t index);

	const Unit& operator[](const GridCell& index) const;
	const GridCell& operator[](const Unit& index) const;
	const GridCell& operator[](const ID& index) const;
	constGridRow operator[](size_t index) const;

};
