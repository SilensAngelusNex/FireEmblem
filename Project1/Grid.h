#pragma once
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "Party.h"
#include "ID.h"
#include "read_vector.h"
/**
Grid class. Holds a Matrix of GridCells. Should be initialized at the start of each chapter.
*/
class GridCell;
class Unit;
class Mobility;

class Grid {
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
	bool hasUnit(const Unit & index) const;
	bool hasUnit(const ID& index) const;

	Unit* getUnit(const GridCell& index);
	Unit* getUnit(const ID& index);
	GridCell* getCell(const Unit& index);

	const Unit* getUnit(const GridCell& index) const;
	const Unit* getUnit(const ID& index) const;
	const GridCell* getCell(const Unit& index) const;


	using GridRow = read_vector< std::vector<GridCell>>;
	using constGridRow = read_vector<const std::vector<GridCell>>;

	Unit& operator[](const GridCell& index);
	ID operator[](const Unit& index);
	GridCell& operator[](const ID& index);
	GridRow operator[](size_t index);

	const Unit& operator[](const GridCell& index) const;
	const ID operator[](const Unit& index) const;
	const GridCell& operator[](const ID& index) const;
	constGridRow operator[](size_t index) const;

};
