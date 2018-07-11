#include "UnitCommandable.h"

UnitCommandable::UnitCommandable(std::unique_ptr<Unit> unit) :
	UnitViewable(std::move(unit))
{}

InventoryCommandable& UnitCommandable::getInventory() {
	return _ptr->getInventory();
}

BattleInfo& UnitCommandable::getBattleInfo() {
	return _ptr->getBattleInfo();
}

Combat& UnitCommandable::getCombat() {
	return _ptr->getCombat();
}

PartyBase* UnitCommandable::getParty() {
	return _ptr->getParty();
}

PartyBase* UnitCommandable::setParty(PartyBase* other_party) {
	return _ptr->setParty(other_party);
}

void UnitCommandable::add(std::unique_ptr<Item> item) {
	_ptr->getInventory().add(std::move(item));
}

std::unique_ptr<Item> UnitCommandable::drop(int item_index) {
	return _ptr->getInventory().drop(item_index);
}

std::unique_ptr<Item> UnitCommandable::drop(Item& item) {
	return _ptr->getInventory().drop(item);
}

void UnitCommandable::swap(int i, int j) {
	_ptr->getInventory().swap(i, j);
}

void UnitCommandable::swap(Item & a, Item & b) {
	_ptr->getInventory().swap(a, b);
}

void UnitCommandable::equip(EquipSlot slot, int item_index) {
	_ptr->getInventory().equip(slot, item_index);
}

void UnitCommandable::equip(EquipSlot slot, Item & item) {
	_ptr->getInventory().equip(slot, item);
}

void UnitCommandable::equip(EquipSlot slot, std::unique_ptr<Item> item) {
	_ptr->getInventory().equip(slot, std::move(item));
}

void UnitCommandable::dequip(EquipSlot slot) {
	_ptr->getInventory().dequip(slot);
}

int UnitCommandable::takeDamage(Damage to_take) {
	return _ptr->getBattleInfo().takeDamage(to_take);
}

int UnitCommandable::heal(Healing to_heal) {
	return _ptr->getBattleInfo().heal(to_heal);
}

void UnitCommandable::useMajor() {
	_ptr->getBattleInfo().useMajor();
}

void UnitCommandable::useMinor() {
	_ptr->getBattleInfo().useMinor();
}

void UnitCommandable::useMove(int used) {
	_ptr->getBattleInfo().useMove(used);
}

void UnitCommandable::useIndependent(BattleInfo::ActionId used) {
	_ptr->getBattleInfo().useIndependent(used);
}

void UnitCommandable::refresh() {
	_ptr->getBattleInfo().refresh();
}

void UnitCommandable::combat(Unit& defender) {
	_ptr->getCombat().combat(defender);
}

std::optional<int> UnitCommandable::strike(Unit& defender) {
	return _ptr->getCombat().strike(defender);
}
