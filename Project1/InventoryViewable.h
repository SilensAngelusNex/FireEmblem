#pragma once

#include <map>

#include "InventoryBase.h"
#include "Passkey.h"
#include "Range.h"


class InventoryViewable : public InventoryBase {
public:
	const Item& operator[](int item_index) const;
	const ItemEquip& operator[](EquipSlot slot) const;

	bool hasEquip(EquipSlot slot) const;

	std::map<MobilitySet, Range::DistanceSet> getAttackRanges() const;
	std::map<MobilitySet, Range::DistanceSet> getAssistRanges() const;

	int itemsHeld() const;

	int avoid(Passkey<Stats> /*unused*/) const;
	int dodge(Passkey<Stats> /*unused*/) const;
	int hit(Passkey<Stats> /*unused*/) const;
	int crit(Passkey<Stats> /*unused*/) const;
	int might(Passkey<Stats> /*unused*/) const;
	int atk_spd(Passkey<Stats> /*unused*/) const;
protected:
	explicit InventoryViewable(Unit& owner);
};
