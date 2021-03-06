#pragma once

#include <string>
#include <stdexcept>

#include "AttributeList.h"

class Unit;
using GameException = std::runtime_error;

enum _EQUIP_SLOTS { ON_HAND, OFF_HAND, CHEST, ENUM_END };
using EquipSlot = Enum<_EQUIP_SLOTS>;


class ItemEquip;
class Item {
public:
	Item() = default;
	Item(const Item& a) = default;
	Item(Item&& a) = default;
	Item& operator=(const Item& rhs) = default;
	Item& operator=(Item&& rhs) = default;
	virtual ~Item() = default;

	virtual const std::string& getName() const = 0;

	virtual bool is_equippable() const;
	virtual void equip(Unit& /*unit*/, EquipSlot /*slot*/);

	ItemEquip& getItemEquip();
	const ItemEquip& getItemEquip() const;
};
