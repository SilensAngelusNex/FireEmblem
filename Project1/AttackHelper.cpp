#include "AttackHelper.h"
#include "CellEdge.h"
#include "Unit.h"
#include "Party.h"
//#include "CellPath.h"
#include "GridCell.h"
#include "Range.h"


/*
AttackHelper::AttackHelper(GridMap& map) :
	MapHelper(map)
{}

// Get Cells that a unit can attack without moving with Equipped Weapon
std::vector<ID> AttackHelper::getAttackableCellIDs(const Unit& unit) {
	return getAttackableCellIDs(unit, _map[unit]);
}

//Get Cells a Unit could attack with Equipped Weapon, if it were standing on cell
std::vector<ID> AttackHelper::getAttackableCellIDs(const Unit& unit, ID cell) {
	Range range = Range(); //sword //TODO(Torrey):get actual ranges from Unit
	if (unit.getInventory().hasEquip(EquipSlot::values::ON_HAND)) {
		range = unit.getInventory()[EquipSlot(EquipSlot::values::ON_HAND)].getAttackRange();
	}
	return getCellIDsWithin(range, cell);
}
*/