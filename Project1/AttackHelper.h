#pragma once
#include "MapHelper.h"

class AttackHelper : private MapHelper {
public:
	AttackHelper(GridMap& map);
	std::vector<Unit::Ref> getAttackableUnits(const Unit& unit);
	std::vector<Unit::ConstRef> getAttackableUnits(const Unit& unit) const;
	bool canAttack(const Unit& attacker, const Unit& defender) const;
};

