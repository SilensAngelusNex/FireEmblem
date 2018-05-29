#pragma once

#include "Component.h"
#include "Item.h"
#include "ItemEquip.h"

class Unit;
class Stats;

class InventoryBase : protected Component<Unit> {
protected:
	template<typename T>
	using EquipArray = EnumContainer<T, EquipSlot>;
	constexpr static int _MAX_NUMBER_ITEMS = 5;

	EquipArray<ItemEquip*> _equipment{};
	EquipArray<std::unique_ptr<Item>> _equipment_owners{};
	std::array<std::unique_ptr<Item>, _MAX_NUMBER_ITEMS> _items{};
	int _number_items_held{0};
public:
	InventoryBase(const InventoryBase& that) = delete;
	InventoryBase& operator=(const InventoryBase& that) = delete;
protected:
	explicit InventoryBase(Unit& owner);
	InventoryBase(InventoryBase&& that) = default;
	InventoryBase& operator=(InventoryBase&& that);
	~InventoryBase() = default;

	int stats_help(const AttributeList& stats, int (ItemEquip::*get_stats)(const AttributeList&) const) const;
};