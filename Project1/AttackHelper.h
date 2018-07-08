#pragma once
#include "MapHelper.h"
#include "HelperContainer.h"
class AttackHelper : private MapHelper {
public:
	AttackHelper(GridMap& map);
	std::vector<UnitRef> getAttackableUnits(const Unit& unit);
	std::vector<UnitConstRef> getAttackableUnits(const Unit& unit) const;
	bool canAttack(const Unit& attacker, const Unit& defender) const;
};

using AttackContainer = HelperContainer<AttackHelper>;