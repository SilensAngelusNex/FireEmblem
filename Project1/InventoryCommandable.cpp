#include <gsl/gsl_assert>

#include "InventoryCommandable.h"

InventoryCommandable::InventoryCommandable(Unit& owner) :
	InventoryViewable(owner)
{}


void InventoryCommandable::add(std::unique_ptr<Item> item) {
	Expects(_number_items_held < _MAX_NUMBER_ITEMS);
	_items[_number_items_held] = std::move(item);
	_number_items_held++;
}

std::unique_ptr<Item> InventoryCommandable::drop(int item_index) {
	Expects(0 <= item_index && item_index < _number_items_held);
	std::unique_ptr<Item> result = std::move(_items[item_index]);

	while (item_index < _number_items_held - 1) {
		_items[item_index] = std::move(_items[item_index + 1]);
		item_index++;
	}

	_items[item_index] = nullptr;
	_number_items_held--;

	return result;
}

std::unique_ptr<Item> InventoryCommandable::drop(Item& item) {
	return drop(findItem(item));
}

void InventoryCommandable::swap(int i, int j) {
	// 0 <= (i, j) < _number_items_held
	Expects(0 <= i && i < _number_items_held && 0 <= j && j < _number_items_held);
	std::swap(_items[i], _items[j]);
}

void InventoryCommandable::swap(Item& a, Item& b) {
	int i = -1;
	int j = -1;

	int k = 0;
	while (k < _number_items_held) {
		if (_items[k].get() == &a) {
			i = k;
		}
		if (_items[k].get() == &b) {
			j = k;
		}
		k++;
	}

	// 0 <= (i, j) < _number_items_held
	Ensures(0 <= i && i < _number_items_held && 0 <= j && j < _number_items_held);
	std::swap(_items[i], _items[j]);
}

void InventoryCommandable::equip(EquipSlot slot, int item_index) {
	Expects(canEquip(slot, item_index));

	_items[item_index]->equip(_owner, slot);
	equip0(slot, drop(item_index));
}

void InventoryCommandable::equip(EquipSlot slot, Item& item) {
	Expects(canEquip(slot, item));

	item.equip(_owner, slot);
	equip0(slot, drop(item));
}

void InventoryCommandable::equip(EquipSlot slot, std::unique_ptr<Item> item) {
	Expects(canEquip(slot, item.get()));
	if (_equipment[slot] != nullptr) {
		dequip(slot);
	}
	item->equip(_owner, slot);
	equip0(slot, std::move(item));
}

void InventoryCommandable::dequip(EquipSlot slot) {
	Expects(canDequip(slot));
	add(dequip0(slot));
}

bool InventoryCommandable::canEquip(EquipSlot slot, int item_index) const{
	return item_index < _number_items_held && _items[item_index]->is_equippable();
}

bool InventoryCommandable::canEquip(EquipSlot slot, const Item& item) const{
	return findItem(item) < _number_items_held && item.is_equippable();
}

bool InventoryCommandable::canEquip(EquipSlot slot, const Item* item) const{
	return item->is_equippable() && (_equipment[slot] == nullptr || _number_items_held < _MAX_NUMBER_ITEMS);

}

bool InventoryCommandable::canDequip(EquipSlot slot) const {
	return _number_items_held < _MAX_NUMBER_ITEMS;// && _equipment_owners[slot] != nullptr; THIS IS BLACK MAGIC WTF WESTON WHY DOES THIS NOT COMPILE WTF
}

int InventoryCommandable::findItem(const Item& item) const{
	int result = _number_items_held;
	for (int i = 0; i < _number_items_held; i++) {
		if (_items[i].get() == &item) {
			result = i;
		}
	}
	Ensures(0 <= result && result < _number_items_held);
	return result;
}

std::unique_ptr<Item> InventoryCommandable::dequip0(EquipSlot slot) {
	Expects(_equipment_owners[slot] != nullptr);
	
	std::unique_ptr<Item> result = std::move(_equipment_owners[slot]);
	_equipment_owners[slot] = nullptr;
	_equipment[slot] = nullptr;

	// trigger dequip skills
	return result;
}

void InventoryCommandable::equip0(EquipSlot slot, std::unique_ptr<Item> item) {
	if (_equipment_owners[slot] != nullptr) {
		add(std::move(_equipment_owners[slot]));
	}
	_equipment_owners[slot] = std::move(item);

	// trigger equip skills
}