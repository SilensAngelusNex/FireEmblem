#pragma once
#include "ID.h"
#include "CellPath.h"
#include <map>


//TODO(Torrey): rename this class
template <typename grid, typename cell>
class Path_Map :
	private id_cost_map
{
private:
	using CostCell = logic_pair<int, std::reference_wrapper<cell>>;
	//private iterator class that replaces ID with CellRef
	template <typename iterator>
	class path_map_iter : public iterator {
	private:
		grid & _map;
	public:
		path_map_iter(iterator&& parent, grid& map) :
			iterator(parent),
			_map(map)
		{}
		std::pair<CellRef, CostCell> operator*() const {
			auto temp = iterator::operator*();
			return std::pair<CellRef, CostCell>(_map[temp.first], CostCell(temp.second.first, _map[temp.second.second]));
		}
	};

private:
	grid& _grid;
	CostCell convert(CostID pair) {
		return CostCell(pair.first, _grid[pair.second]);
	}
	
public:
	//Constructors
	Path_Map(grid& g) :
		id_cost_map(),
		_grid(g)
	{}
	Path_Map(grid& g, id_cost_map&& move) :
		id_cost_map(move),
		_grid(g)
	{}

	using id_cost_map::operator=;
	using id_cost_map::get_allocator;

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
		return convert((*this)[key._id]);
	}
	CostCell operator[](const GridCell&& key) {
		return convert((*this)[key._id]);
	}

	CostCell at(const GridCell& key) {
		return convert(this->at(key._id));
	}
	const CostCell at(const ID& key) const {
		return convert(this->at(key._id));
	}
	using id_cost_map::operator[];
	using id_cost_map::at;

	//Capacity
	using id_cost_map::empty;
	using id_cost_map::size;
	using id_cost_map::max_size;


	//modifiers
	using id_cost_map::clear;
	using id_cost_map::insert;
	using id_cost_map::insert_or_assign;
	using id_cost_map::emplace;
	using id_cost_map::emplace_hint;
	using id_cost_map::try_emplace;
	using id_cost_map::erase;
	using id_cost_map::swap;
	using id_cost_map::extract;
	using id_cost_map::merge;

	//Lookup
	using id_cost_map::count;
	using id_cost_map::find;
	using id_cost_map::equal_range;
	using id_cost_map::lower_bound;
	using id_cost_map::upper_bound;

	//Observers
	using id_cost_map::key_comp;
	using id_cost_map::value_comp;

};

class GridMap;
class GridCell;
using PathMap = Path_Map<GridMap, GridCell>;
using constPathMap = Path_Map<const GridMap, const GridCell>;
