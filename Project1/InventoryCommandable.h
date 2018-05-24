#ifndef INVENTORY_COMMANDABLE_H
#define INVENTORY_COMMANDABLE_H

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
protected:
	explicit InventoryCommandable(Unit& owner);

	int findItem(Item& item);
	std::unique_ptr<Item> dequip0(EquipSlot slot);
	void equip0(EquipSlot slot, std::unique_ptr<Item> item);
};

#endif // !INVENTORY_COMMANDABLE_H