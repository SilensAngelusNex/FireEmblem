#pragma once
#include <list>
#include "MobilityList.h"
class GridCell;
//TODO(Torrey): Create Superclasses of this. EX: UnitPath has a unit to traverse the Grid.
using CellRef = std::reference_wrapper<GridCell>;
using CellCost = std::pair<int, CellRef>;

class CellPath
{
	std::list<CellCost>_path = std::list<CellCost>();
	const MobilitySet _traversal_vector;
public:
	CellPath(GridCell& head);
	CellPath(GridCell& head, MobilitySet traversal_vector);
	CellPath(std::list<CellRef> path, MobilitySet traversal_vector);

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

