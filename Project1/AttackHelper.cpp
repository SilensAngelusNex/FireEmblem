#include "AttackHelper.h"
#include "GridMap.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
#include "GridCell.h"
#include "Range.h"



AttackHelper::AttackHelper(GridMap & map) :
	MapHelper(map)
{}

//Gets Units attackable from current position woth currently equipped weapon
std::vector<Unit::Ref> AttackHelper::getAttackableUnits(const Unit & unit) {
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		return getEnemiesWithin(unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange(), _map[unit], *unit.getParty());
	}
	return {};
}

//Gets Units attackable from current position woth currently equipped weapon
std::vector<Unit::ConstRef> AttackHelper::getAttackableUnits(const Unit & unit) const{
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		return getEnemiesWithin(unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange(), _map[unit], *unit.getParty());
	}
	return {};
}

//Gets if a Unit can attack another based on position, party, and equipped weapon
bool AttackHelper::canAttack(const Unit & attacker, const Unit & defender) const{
	std::vector<Unit::ConstRef> attackable_units = getAttackableUnits(attacker);
	return std::count(attackable_units.begin(), attackable_units.end(), defender) > 0;
}
