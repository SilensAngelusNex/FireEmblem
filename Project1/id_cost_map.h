#pragma once
#include <map>
#include "ID.h"
#include "logic_pair.h"
#include "GridCell.h"
class id_cost_map : public std::map<ID, CostID> {
public:
	const GridCell& _origin;
	id_cost_map(const GridCell& origin) :
		_origin(origin)
	{}

};

