#pragma once
#include "MapHelper.h"
#include "MoveHelper.h"
#include <vector>
#include "GridMap.h"
#include "MapHelper.h"
#include "reference_logic.h"
#include "GridCell.h"
#include "ID.h"

class Unit;
class GridCell;
class AttackHelper :
	private MapHelper
{
public:
	AttackHelper(GridMap& map);

	std::vector<Unit::Ref> getAttackableUnits(const Unit& unit);
	const std::vector<Unit::Ref> getAttackableUnits(const Unit& unit) const;

	bool canAttack(const Unit& attacker, const Unit& defender) const;
};

