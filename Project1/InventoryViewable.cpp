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
	Expects(hasEquip(slot));
	return *_equipment[slot];
}

bool InventoryViewable::hasEquip(EquipSlot slot) const {
	return _equipment[slot] != nullptr;
}


struct AttackRanges { static Range getRange(const ItemEquip& item) { return item.getAttackRange(); } };
struct AssistRanges { static Range getRange(const ItemEquip& item) { return item.getAssistRange(); } };

std::map<MobilitySet, Range::DistanceSet> InventoryViewable::getAttackRanges() const {
	return getRanges<AttackRanges>();
}
std::map<MobilitySet, Range::DistanceSet> InventoryViewable::getAssistRanges() const {
	return getRanges<AssistRanges>();
}


int InventoryViewable::avoid(Passkey<Stats> /*unused*/) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::avoid);
}
int InventoryViewable::dodge(Passkey<Stats> /*unused*/) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::dodge);
}
int InventoryViewable::hit(Passkey<Stats> /*unused*/) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::hit);
}
int InventoryViewable::crit(Passkey<Stats> /*unused*/) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::crit);
}
int InventoryViewable::might(Passkey<Stats> /*unused*/) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::might);
}
int InventoryViewable::atk_spd(Passkey<Stats> /*unused*/) const {
	return stats_help(_owner.getStats().getAttribs(), &ItemEquip::atk_spd);
}
