#pragma once
#include <list>
#include "logic_pair.h"
#include "GridCell.h"
class PathBase : public logic_pair<int, GridCell::Ref>
{
private:
	using CostCell = logic_pair<int, GridCell::Ref>;
public:

};

