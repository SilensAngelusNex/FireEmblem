#pragma once

#include <string>
#include <stdexcept>

#include "AttributeList.h"

class Unit;
using GameException = std::runtime_error;

enum EquipSlot { ON_HAND, OFF_HAND, CHEST, EQUIP_SLOTS_ENUM_END };

/**
	
*/
class Item {
public:
	Item() = default;
	Item(const Item& a) = default;
	Item(Item&& a) = default;
	Item& operator=(const Item& rhs) = default;
	Item& operator=(Item&& rhs) = default;
	virtual ~Item() = default;

	virtual const std::string& getName() const = 0;

	virtual bool is_equippable() const {
		return false;
	}

	virtual void equip(Unit&  /*unit*/, EquipSlot  /*slot*/) {
		throw GameException("Item cannot be equipped.");
	}
};
