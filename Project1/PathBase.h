#pragma once
#include <list>
#include "logic_pair.h"
#include "GridCell.h"
class PathBase 
{
protected:
	using CostCell = logic_pair<int, GridCell::Ref>;
	using List = std::list<CostCell>;
	List _path;

public:
	void push_back(GridCell& tail);

	GridCell & front();
	const GridCell& front() const;
	GridCell& back();
	const GridCell& back() const;

	using iterator = List::iterator;
	using const_iterator = List::const_iterator;
	iterator begin() { return _path.begin(); }
	iterator end() { return _path.end(); }
	const_iterator cbegin() { return _path.cbegin(); }
	const_iterator cend() { return _path.cend(); }
};

