#include <algorithm>
#include <gsl/gsl_assert>

#include "Inventory.h"
#include "Unit.h"


Inventory::Inventory(Unit& owner) :
	InventoryCommandable(owner)
{}


void Inventory::equipInternal(EquipSlot slot, ItemEquip* to_equip) {
	_equipment[slot] = to_equip;
}

Damage Inventory::getNormalDamage(const Unit& defender) {
	if (_equipment[ON_HAND] != nullptr && _equipment[ON_HAND]->is_weapon()) {
		return _equipment[ON_HAND]->get_normal_damage(_owner, defender);
	}
	return Damage(_stats->getAttribs()[AttribType::values::STR], AttribType::values::DEF);
	
}

Damage Inventory::getCritDamage(const Unit& defender) {
	if (_equipment[ON_HAND] != nullptr && _equipment[ON_HAND]->is_weapon()) {
		return _equipment[ON_HAND]->get_crit_damage(_owner, defender);
	}
	return Damage(2 * _stats->getAttribs()[AttribType::values::STR], AttribType::values::DEF);
}


