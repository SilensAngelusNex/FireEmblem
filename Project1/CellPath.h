#pragma once
#include <list>
#include "MobilityList.h"
#include "GridCell.h"
#include "ID.h"

//TODO(Torrey): Create Superclasses of this. EX: UnitPath has a unit to traverse the Grid.

using CellCost = std::pair<int, ID>;
using constCellCost = std::pair<int, constCellRef>;
/*
class CellPath
{
	std::list<CellCost>_path = std::list<CellCost>();
	const MobilitySet _traversal_vector;
public:
	CellPath(std::list<ID> path, MobilitySet traversal_vector);

	void addTail(GridCell& tail);

	int getCost();
	GridCell& getTail();

	GridCell & getHead();

	int getCost() const;
	const GridCell & getTail() const;

	const GridCell & getHead() const;

	using iterator = std::list<CellCost>::iterator;
	using const_iterator = std::list<CellCost>::const_iterator;
	iterator begin() { return _path.begin(); }
	iterator end() { return _path.end(); }
	const_iterator cbegin() const { return _path.cbegin(); }
	const_iterator cend() const { return _path.cend(); }
};

*/