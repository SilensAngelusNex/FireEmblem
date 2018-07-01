#pragma once
#include <map>
#include "ID.h"
#include "logic_pair.h"
#include "GridCell.h"
class id_cost_map : private std::map<const ID, CostID>
{
private:
	using Map = std::map<const ID, CostID>;
public:
	const GridCell& _origin;
	id_cost_map(const GridCell& origin) :
		_origin(origin)
	{}
	id_cost_map() = delete;

	using Map::operator=;
	using Map::get_allocator;

	using Map::operator[];
	using Map::at;

	//Capacity
	using Map::empty;
	using Map::size;
	using Map::max_size;

	//Iterator
	using Map::iterator;
	using Map::const_iterator;
	using Map::begin;
	using Map::cbegin;
	using Map::end;
	using Map::cend;

	//modifiers
	using Map::clear;
	using Map::insert;
	using Map::insert_or_assign;
	using Map::emplace;
	using Map::emplace_hint;
	using Map::try_emplace;
	using Map::erase;
	using Map::swap;
	using Map::extract;
	using Map::merge;

	//Lookup
	using Map::count;
	using Map::find;
	using Map::equal_range;
	using Map::lower_bound;
	using Map::upper_bound;

	//Observers
	using Map::key_comp;
	using Map::value_comp;
};

