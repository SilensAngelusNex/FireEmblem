#pragma once

#include "InventoryCommandable.h"
#include "Damage.h"
#include "Stats.h"

class Unit;

class Inventory : public InventoryCommandable {
public:
	explicit Inventory(Unit& owner);

	void equipInternal(EquipSlot slot, ItemEquip* to_equip);
	Damage getNormalDamage(const Unit& defender);
	Damage getCritDamage(const Unit& defender);
};