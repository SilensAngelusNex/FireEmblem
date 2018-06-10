#pragma once
#include "GridCell.h"
//TODO(Torrey): Create Superclasses of this. EX: UnitPath has a unit to traverse the Map.
using CellCost = std::pair<int, GridCell*>;
class CellPath
{
	std::list<CellCost>_path = std::list<CellCost>();
	const MobilityList<bool> _traversal_vector;
public:
	CellPath(GridCell& head);
	CellPath(GridCell& head, MobilityList<bool> traversal_vector);
	CellPath(std::list<GridCell*> path, MobilityList<bool> traversal_vector);

	void addTail(GridCell& tail);

	int getCost();
	GridCell& getTail();

	GridCell & getHead();

	int getCost() const;
	const GridCell & getTail() const;

	const GridCell & getHead() const;

	using iterator = std::list<CellCost>::iterator;
	using const_iterator = std::list<CellCost>::iterator;
	iterator begin() { return _path.begin(); }
	iterator end() { return _path.end(); }

};

