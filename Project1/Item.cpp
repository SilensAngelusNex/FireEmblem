#include "Item.h"
#include "ItemEquip.h"

bool Item::is_equippable() const {
	return false;
}

void Item::equip(Unit& /*unit*/, EquipSlot /*slot*/) {
	throw GameException("Item cannot be equipped.");
}

ItemEquip& Item::getItemEquip() {
	Expects(is_equippable());
	return static_cast<ItemEquip&>(*this);
}

const ItemEquip& Item::getItemEquip() const {
	Expects(is_equippable());
	return static_cast<const ItemEquip&>(*this);
}
