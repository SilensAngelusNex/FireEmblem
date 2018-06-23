#pragma once
#include "ID.h"
#include "CellPath.h"
#include <map>

class Grid;


class PathMap :
	private std::map<const ID, CellCost>
{
private:
	//Grid& _map;
public:
	PathMap(Grid& map);
	PathMap(const Grid& map);
	//using std::map<const ID, CellCost>::~map;
	using std::map<const ID, CellCost>::operator=;
	using std::map<const ID, CellCost>::get_allocator;

	//Iterator
	using std::map<const ID, CellCost>::iterator;
	using std::map<const ID, CellCost>::const_iterator;
	using std::map<const ID, CellCost>::begin;
	using std::map<const ID, CellCost>::cbegin;
	using std::map<const ID, CellCost>::end;
	using std::map<const ID, CellCost>::cend;

	//Element access;
	using std::map<const ID, CellCost>::at;
	using std::map<const ID, CellCost>::operator[];

	//Capacity
	using std::map<const ID, CellCost>::empty;
	using std::map<const ID, CellCost>::size;
	using std::map<const ID, CellCost>::max_size;


	//modifiers
	using std::map<const ID, CellCost>::clear;
	using std::map<const ID, CellCost>::insert;
	using std::map<const ID, CellCost>::insert_or_assign;
	using std::map<const ID, CellCost>::emplace;
	using std::map<const ID, CellCost>::emplace_hint;
	using std::map<const ID, CellCost>::try_emplace;
	using std::map<const ID, CellCost>::erase;
	using std::map<const ID, CellCost>::swap;
	using std::map<const ID, CellCost>::extract;
	using std::map<const ID, CellCost>::merge;

	//Lookup
	using std::map<const ID, CellCost>::count;
	using std::map<const ID, CellCost>::find;
	using std::map<const ID, CellCost>::equal_range;
	using std::map<const ID, CellCost>::lower_bound;
	using std::map<const ID, CellCost>::upper_bound;

	//Observers
	using std::map<const ID, CellCost>::key_comp;
	using std::map<const ID, CellCost>::value_comp;
};

