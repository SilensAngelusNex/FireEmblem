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

std::unique_ptr<Item> InventoryCommandable::drop(size_t item_index) {
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

void InventoryCommandable::swap(size_t i, size_t j) {
	// 0 <= (i, j) < _number_items_held
	Expects(0 <= i && i < _number_items_held && 0 <= j && j < _number_items_held);
	std::swap(_items[i], _items[j]);
}

void InventoryCommandable::swap(Item& a, Item& b) {
	size_t i = _number_items_held;
	size_t j = _number_items_held;

	for (size_t k = 0; k < _number_items_held; ++k) {
		if (_items[k].get() == &a) {
			i = k;
		}
		if (_items[k].get() == &b) {
			j = k;
		}
	}

	// 0 <= (i, j) < _number_items_held
	Ensures(i < _number_items_held && j < _number_items_held);
	std::swap(_items[i], _items[j]);
}

void InventoryCommandable::equip(EquipSlot slot, size_t item_index) {
	Expects(item_index < _number_items_held && _items[item_index]->is_equippable());

	_items[item_index]->equip(_owner, slot);
	equip0(slot, drop(item_index));
}

void InventoryCommandable::equip(EquipSlot slot, Item& item) {
	Expects(findItem(item) < _number_items_held && item.is_equippable());

	item.equip(_owner, slot);
	equip0(slot, drop(item));
}

void InventoryCommandable::equip(EquipSlot slot, std::unique_ptr<Item> item) {
	Expects(item->is_equippable() && (_equipment[slot] == nullptr || _number_items_held < _MAX_NUMBER_ITEMS));
	if (_equipment[slot] != nullptr) {
		dequip(slot);
	}
	item->equip(_owner, slot);
	equip0(slot, std::move(item));
}

void InventoryCommandable::dequip(EquipSlot slot) {
	Expects(_number_items_held < _MAX_NUMBER_ITEMS);
	add(dequip0(slot));
}

size_t InventoryCommandable::findItem(Item& item) {
	size_t result = _number_items_held;
	for (size_t i = 0; i < _number_items_held; i++) {
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