#pragma once

#include "Component.h"
#include "Item.h"
#include "ItemEquip.h"

class Unit;
class Stats;

#define INVENTORY_MAX_NUMBER_ITEMS 5

class InventoryBase : public Component<Unit> {
private:
	template<typename T>
	using EquipArray = EnumContainer<T, EquipSlot>;
protected:
	Stats* _stats;

	EquipArray<ItemEquip*> _equipment{};
	EquipArray<std::unique_ptr<Item>> _equipment_owners{};
	std::array<std::unique_ptr<Item>, INVENTORY_MAX_NUMBER_ITEMS> _items{};

	int _number_items_held{0};
public:
	void init();

	InventoryBase(const InventoryBase& that) = delete;
	InventoryBase& operator=(const InventoryBase& that) = delete;
protected:
	explicit InventoryBase(Unit& owner);
	InventoryBase(InventoryBase&& that) = default;
	InventoryBase& operator=(InventoryBase&& that);
	~InventoryBase() = default;

	int stats_help(const AttributeList& stats, int (ItemEquip::*get_stats)(const AttributeList&) const) const;
};