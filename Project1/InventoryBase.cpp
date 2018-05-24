#include <numeric>

#include "InventoryBase.h"
#include "ItemEquip.h"
#include "Unit.h"

InventoryBase::InventoryBase(Unit & owner) :
	Component<Unit>(owner)
{}

void InventoryBase::init() {
	_stats = &_owner.getStats();
}

InventoryBase& InventoryBase::operator=(InventoryBase&& that) {
	_stats = that._stats;
	_equipment = that._equipment;
	_equipment_owners = std::move(that._equipment_owners);
	_items = std::move(that._items);
	_number_items_held = that._number_items_held;
	return *this;
}

int InventoryBase::stats_help(const AttributeList& stats, int(ItemEquip::*get_stats)(const AttributeList&) const) const {
	return std::accumulate(
		_equipment.cbegin(),
		_equipment.cend(),
		0,
		[&stats, get_stats](int result, ItemEquip* equip) {
		return result + (equip != nullptr ? (equip->*get_stats)(stats) : 0);
	});
}