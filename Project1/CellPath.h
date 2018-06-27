#pragma once
#include <list>
#include "MobilityList.h"
#include "GridCell.h"
#include "ID.h"

//TODO(Torrey): Create Superclasses of this. EX: UnitPath has a unit to traverse the Grid.


/*
class CellPath
{
	std::list<CostID>_path = std::list<CostID>();
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

	using iterator = std::list<CostID>::iterator;
	using const_iterator = std::list<CostID>::const_iterator;
	iterator begin() { return _path.begin(); }
	iterator end() { return _path.end(); }
	const_iterator cbegin() const { return _path.cbegin(); }
	const_iterator cend() const { return _path.cend(); }
};

*/