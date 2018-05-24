#pragma once

#include "InventoryBase.h"
#include "Passkey.h"


class InventoryViewable : public InventoryBase {
public:
	const Item& getItem(int item_index) const;
	const ItemEquip& getEquip(EquipSlot slot) const;

	int avoid(Passkey<Stats> key) const;
	int dodge(Passkey<Stats> key) const;
	int hit(Passkey<Stats> key) const;
	int crit(Passkey<Stats> key) const;
	int might(Passkey<Stats> key) const;
	int atk_spd(Passkey<Stats> key) const;
protected:
	explicit InventoryViewable(Unit& owner);
};