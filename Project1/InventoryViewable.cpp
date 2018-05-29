#include <gsl/gsl_assert>

#include "InventoryViewable.h"
#include "Stats.h"
#include "Unit.h"


InventoryViewable::InventoryViewable(Unit & owner) :
	InventoryBase(owner)
{}


const Item& InventoryViewable::getItem(int item_index) const {
	Expects(item_index < _number_items_held);
	return *_items[item_index];
}
const ItemEquip& InventoryViewable::getEquip(EquipSlot slot) const {
	return *_equipment[slot];
}

int InventoryViewable::avoid(Passkey<Stats> key) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::avoid);
}
int InventoryViewable::dodge(Passkey<Stats> key) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::dodge);
}
int InventoryViewable::hit(Passkey<Stats> key) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::hit);
}
int InventoryViewable::crit(Passkey<Stats> key) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::crit);
}
int InventoryViewable::might(Passkey<Stats> key) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::might);
}
int InventoryViewable::atk_spd(Passkey<Stats> key) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::atk_spd);
}

