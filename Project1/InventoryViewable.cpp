#include "InventoryViewable.h"

#include <gsl/gsl_assert>

#include "Stats.h"
#include "Unit.h"


InventoryViewable::InventoryViewable(Unit & owner) :
	InventoryBase(owner)
{}


const Item & InventoryViewable::operator[](int item_index) const {
	Expects(item_index < _number_items_held);
	return *_items[item_index];
}
const ItemEquip& InventoryViewable::operator[](EquipSlot slot) const {
	Expects(_equipment[slot] != nullptr);
	return *_equipment[slot];
}


struct AttackRanges { static Range getRange(const ItemEquip& item) { return item.getAttackRange(); } };
struct AssistRanges { static Range getRange(const ItemEquip& item) { return item.getAssistRange(); } };

std::map<RangeUtil::Movement, RangeUtil::Distances> InventoryViewable::getAttackRanges() const {
	return getRanges<AttackRanges>();
}
std::map<RangeUtil::Movement, RangeUtil::Distances> InventoryViewable::getAssistRanges() const {
	return getRanges<AssistRanges>();
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
