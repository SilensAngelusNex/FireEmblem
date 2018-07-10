#pragma once

#include "InventoryViewable.h"


class InventoryCommandable : public InventoryViewable {
private:
	// Attach/detatch skills
public:
	void add(std::unique_ptr<Item> item);
	std::unique_ptr<Item> drop(int item_index);
	std::unique_ptr<Item> drop(Item& item);
	void swap(int i, int j);
	void swap(Item& a, Item& b);
	
	void equip(EquipSlot slot, int item_index);
	void equip(EquipSlot slot, Item& item);
	void equip(EquipSlot slot, std::unique_ptr<Item> item);
	void dequip(EquipSlot slot);
	
	bool canEquip(EquipSlot slot, int item_index) const;
	bool canEquip(EquipSlot slot, const Item& item) const;
	bool canEquip(EquipSlot slot, const Item* item) const;

protected:
	explicit InventoryCommandable(Unit& owner);

	int findItem(const Item& item) const;
	std::unique_ptr<Item> dequip0(EquipSlot slot);
	void equip0(EquipSlot slot, std::unique_ptr<Item> item);
};