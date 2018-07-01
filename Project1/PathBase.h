#pragma once
#include <list>
#include "logic_pair.h"
#include "GridCell.h"
class PathBase 
{
protected:
	using CostCell = logic_pair<int, GridCell>;
	using List = std::list<CostCell>;
	List _path;

public:
	void addTail(GridCell& tail);

	GridCell & front();
	const GridCell& front() const;
	GridCell& back();
	const GridCell& back() const;
};

