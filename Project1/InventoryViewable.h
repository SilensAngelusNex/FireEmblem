#pragma once

#include <map>

#include "InventoryBase.h"
#include "Passkey.h"
#include "Range.h"


class InventoryViewable : public InventoryBase {
public:
	const Item& operator[](int item_index) const;
	const ItemEquip& operator[](EquipSlot slot) const;

	std::map<RangeUtil::Movement, RangeUtil::Distances> getAttackRanges() const;
	std::map<RangeUtil::Movement, RangeUtil::Distances> getAssistRanges() const;

	int avoid(Passkey<Stats> key) const;
	int dodge(Passkey<Stats> key) const;
	int hit(Passkey<Stats> key) const;
	int crit(Passkey<Stats> key) const;
	int might(Passkey<Stats> key) const;
	int atk_spd(Passkey<Stats> key) const;
protected:
	explicit InventoryViewable(Unit& owner);
	template<typename RangeGetter>
	std::map<RangeUtil::Movement, RangeUtil::Distances> getRanges() const;
};

template<typename RangeGetter>
inline std::map<RangeUtil::Movement, RangeUtil::Distances> InventoryViewable::getRanges() const {
	std::map<RangeUtil::Movement, RangeUtil::Distances> result;

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
