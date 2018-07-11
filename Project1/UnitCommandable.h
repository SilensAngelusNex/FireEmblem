#pragma once

#include "UnitViewable.h"

class UnitCommandable : public UnitViewable {
public:
	UnitCommandable(std::unique_ptr<Unit> unit);
	~UnitCommandable() = default;

	[[deprecated("Call methods directly.")]]
	InventoryCommandable& getInventory();
	[[deprecated("Call methods directly.")]]
	BattleInfo& getBattleInfo();
	[[deprecated("Call methods directly.")]]
	Combat& getCombat();
	
	// Identity
	PartyBase* getParty();
	PartyBase* setParty(PartyBase* other_party);

	// Inventory
	void add(std::unique_ptr<Item> item);
	std::unique_ptr<Item> drop(size_t item_index);
	std::unique_ptr<Item> drop(Item& item);
	void swap(size_t i, size_t j);
	void swap(Item& a, Item& b);

	void equip(EquipSlot slot, size_t item_index);
	void equip(EquipSlot slot, Item& item);
	void equip(EquipSlot slot, std::unique_ptr<Item> item);
	void dequip(EquipSlot slot);

	// Battle Info
	int takeDamage(Damage to_take);
	int heal(Healing to_heal);

	void useMajor();
	void useMinor();
	void useMove(int used);
	void useIndependent(BattleInfo::ActionId used);
	void refresh();

	//Combat
	void combat(Unit& defender);
	std::optional<int> strike(Unit& defender);
};