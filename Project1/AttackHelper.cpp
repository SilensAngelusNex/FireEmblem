#include "AttackHelper.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
//#include "CellPath.h"
#include "GridCell.h"
#include "Range.h"



AttackHelper::AttackHelper(GridMap & map) :
	MapHelper(map)
{}

//Gets Units attackable from current position woth currently equipped weapon
std::vector<Unit::Ref> AttackHelper::getAttackableUnits(const Unit& unit) {
	return std::as_const(*this).getAttackableUnits(unit);
}

//Gets Units attackable from current position woth currently equipped weapon
const std::vector<Unit::Ref> AttackHelper::getAttackableUnits(const Unit & unit) const{
	Range range = Range();
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange();
	}
	return getEnemiesWithin(range, _map[unit], *unit.getParty());
}

//Gets if a Unit can attack another based on position, party, and equipped weapon
bool AttackHelper::canAttack(const Unit & attacker, const Unit & defender) const{
	std::vector<Unit::Ref> attackable_units = getAttackableUnits(attacker);
	return std::count(attackable_units.begin(), attackable_units.end(), defender) > 0;
}
