#pragma once
#include "ID.h"
#include "id_cost_map.h"
//#include "GridMap.h" DO NOT INCLUDE THIS
#include <map>


template <typename grid>
class path_map : public id_cost_map
{
private:
	using cell_ref = decltype(std::declval<grid>().operator[](std::declval<ID&>()));
	using CostCell = logic_pair<int, cell_ref>;
	//private iterator class that replaces ID with GridCell::Ref
	template <typename iterator>
	class path_map_iter : public iterator {
	private:
		grid & _map;
	public:
		path_map_iter(iterator&& parent, grid& map) :
			iterator(parent),
			_map(map)
		{}
		std::pair<cell_ref, CostCell> operator*() const {
			auto temp = iterator::operator*();
			return std::pair<cell_ref, CostCell>(_map[temp.first], CostCell(temp.second.first, _map[temp.second.second]));
		}
	};

private:
	grid& _grid;
	CostCell convert(CostID pair) {
		return CostCell(pair.first, _grid[pair.second]);
	}
	
public:
	//Constructors
	path_map(grid& g, GridCell& origin) :
		id_cost_map(origin),
		_grid(g)
	{}
	path_map(grid& g, id_cost_map&& move) :
		id_cost_map(move),
		_grid(g)
	{}



	//Iterator
	using iterator = path_map_iter<id_cost_map::iterator>;
	using const_iterator = path_map_iter<id_cost_map::const_iterator>;

	iterator begin() { return iterator(id_cost_map::begin(), _grid); }
	const iterator begin() const { return iterator(id_cost_map::begin(), _grid); }
	const_iterator cbegin() const noexcept { return const_iterator(id_cost_map::cbegin(), _grid); }
	iterator   end() { return iterator(  id_cost_map::end(), _grid); }
	const iterator end() const { return iterator(id_cost_map::end(), _grid); }
	const_iterator cend() const noexcept { return const_iterator(id_cost_map::cend(), _grid); }

	//Element access;

	CostCell operator[](const GridCell& key) {
		return convert(id_cost_map::operator[](key._id));
	}
	CostCell operator[](const GridCell&& key) {
		return convert(id_cost_map::operator[](key._id));
	}

	CostCell at(const GridCell& key) {
		return convert(id_cost_map::at(key._id));
	}
	const CostCell at(const ID& key) const {
		return convert(id_cost_map::at(key._id));
	}
};

class GridMap;
class GridCell;
using PathMap = path_map<GridMap>;
using constPathMap = path_map<const GridMap>;
