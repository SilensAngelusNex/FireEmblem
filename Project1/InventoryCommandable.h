#pragma once

#include "InventoryViewable.h"


class InventoryCommandable : public InventoryViewable {
private:
	// Attach/detatch skills
public:
	void add(std::unique_ptr<Item> item);
	std::unique_ptr<Item> drop(size_t item_index);
	std::unique_ptr<Item> drop(Item& item);
	void swap(size_t i, size_t j);
	void swap(Item& a, Item& b);
	
	void equip(EquipSlot slot, size_t item_index);
	void equip(EquipSlot slot, Item& item);
	void equip(EquipSlot slot, std::unique_ptr<Item> item);
	void dequip(EquipSlot slot);
protected:
	explicit InventoryCommandable(Unit& owner);

	size_t findItem(Item& item);
	std::unique_ptr<Item> dequip0(EquipSlot slot);
	void equip0(EquipSlot slot, std::unique_ptr<Item> item);
};