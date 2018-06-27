#pragma once
#include <map>
#include "ID.h"

template <typename iterator, typename grid>
class path_map_iter : public iterator {
private: 
	grid & _map;
public:
	path_map_iter(iterator&& parent, grid& map) :
		iterator(parent), 
		_map(map)
	{}
	//TODO(Torrey): make this generic
	std::pair<CellRef, std::pair<int, CellRef>> operator*() const{
		std::pair<ID, CostID> temp = iterator::operator*();
		return std::pair<CellRef, std::pair<int, CellRef>>(_map[temp.first], std::pair<int, CellRef>(temp.second.first, _map[temp.second.second]));
	}
};
