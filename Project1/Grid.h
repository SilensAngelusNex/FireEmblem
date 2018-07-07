#pragma once
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include "Party.h"
#include "ID.h"
#include "read_vector.h"


class GridCell;
class Unit;
class Mobility;
//Grid class. Holds a Matrix of GridCells. Should be initialized at the start of each chapter.
class Grid {
private:

	std::map<const Unit*, GridCell*> _unit_to_cell;
	std::map<const GridCell*, Unit*> _cell_to_unit;

	void insertAdjacencies();
	

protected:
	std::vector<std::vector<GridCell>> _grid;

	Grid(int width, int height);
	~Grid() = default;

public:
	
	Grid(const Grid& map) = delete;
	Grid& operator=(const Grid & map) = delete;
	Grid(Grid&& map) = default;
	Grid& operator=(Grid&& map) = default;
		
	void moveUnit(GridCell& start, GridCell& destination);
	void insertUnit(Unit& new_unit, GridCell& destination);
	void removeUnit(Unit& unit);
	
	void moveUnit(ID start, ID destination);
	void insertUnit(Unit& new_unit, ID destination);

	bool hasUnit(const GridCell& key) const;
	bool hasUnit(const Unit & key) const;
	bool hasUnit(ID index) const;

	Unit* getUnit(const GridCell& key);
	Unit* getUnit(ID index);
	std::vector<Unit::Ref> getUnits();
	GridCell* getCell(const Unit& key);

	const Unit* getUnit(const GridCell& key) const;
	const Unit* getUnit(ID index) const;
	const GridCell* getCell(const Unit& key) const;
	std::vector<Unit::ConstRef> getUnits() const;


	using GridRow = read_vector< std::vector<GridCell>>;
	using constGridRow = read_vector<const std::vector<GridCell>>;

	Unit& operator[](const GridCell& index);
	ID operator[](const Unit& index);
	GridCell& operator[](ID index);
	GridRow operator[](size_t index);

	const Unit& operator[](const GridCell& index) const;
	const ID operator[](const Unit& index) const;
	const GridCell& operator[](ID index) const;
	constGridRow operator[](size_t index) const;

};
