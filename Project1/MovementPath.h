#pragma once
#include <list>
#include "MobilityList.h"
#include "EnumContainer.h"
#include "GridCell.h"
#include "PathMap.h"


class MovementPath  {
private:
	using CostCell = logic_pair<int, GridCell>;
	using List = std::list<CostCell>;
	MobilitySet _mobility_set;
	List _path;
public:
	MovementPath();
	MovementPath(MobilitySet mobility);
	MovementPath(MobilitySet mobility, GridCell& head);
	//MovementPath(PathMap map, Gridell& destination);

	void addTail(GridCell& tail);
	int getCost() const;
	GridCell& getBack();
	const GridCell& getBack() const;

	
};

