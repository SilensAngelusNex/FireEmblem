#pragma once

#include <map>

#include "InventoryBase.h"
#include "Passkey.h"
#include "Range.h"


class InventoryViewable : public InventoryBase {
public:
	const Item& operator[](int item_index) const;
	const ItemEquip& operator[](EquipSlot slot) const;

	std::map<MobilitySet, Range::DistanceSet> getAttackRanges() const;
	std::map<MobilitySet, Range::DistanceSet> getAssistRanges() const;

	int avoid(Passkey<Stats> /*unused*/) const;
	int dodge(Passkey<Stats> /*unused*/) const;
	int hit(Passkey<Stats> /*unused*/) const;
	int crit(Passkey<Stats> /*unused*/) const;
	int might(Passkey<Stats> /*unused*/) const;
	int atk_spd(Passkey<Stats> /*unused*/) const;
protected:
	explicit InventoryViewable(Unit& owner);
	template<typename RangeGetter>
	std::map<MobilitySet, Range::DistanceSet> getRanges() const;
};

template<typename RangeGetter>
inline std::map<MobilitySet, Range::DistanceSet> InventoryViewable::getRanges() const {
	std::map<MobilitySet, Range::DistanceSet> result;

	for (ItemEquip* e : _equipment) {
		if (e != nullptr) {
			Range range = RangeGetter::getRange(*e);
			result[range._type] |= range._range;
		}
	}

	for (int i = 0; i < _number_items_held; ++i) {
		const Item& item = *_items[i];
		if (item.is_equippable()) {
			const ItemEquip& itemEquip = item.getItemEquip();
			if (itemEquip.can_equip(_owner)) {
				Range range = RangeGetter::getRange(itemEquip);
				result[range._type] |= range._range;
			}
		}
	}
	// Remove null movement type
	return result;
}
