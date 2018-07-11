#include "UnitViewable.h"

#include <gsl/gsl_assert>

UnitViewable::UnitViewable(std::unique_ptr<Unit> unit) :
	_ptr(std::move(unit))
{
	Expects(unit != nullptr);
}

const Identity& UnitViewable::getIdentity() const {
	return _ptr->getIdentity();
}

const Stats& UnitViewable::getStats() const {
	return _ptr->getStats();
}

const Mobility& UnitViewable::getMobility() const {
	return _ptr->getMobility();
}

const Experience& UnitViewable::getExperience() const {
	return _ptr->getExperience();
}

const InventoryViewable& UnitViewable::getInventory() const {
	return _ptr->getInventory();
}

const BattleInfo& UnitViewable::getBattleInfo() const {
	return _ptr->getBattleInfo();
}

const std::string& UnitViewable::getName() const {
	return _ptr->getIdentity().getName();
}

const PartyBase* UnitViewable::getParty() const {
	return _ptr->getParty();
}

const AttributeList& UnitViewable::getAttribs() const {
	return _ptr->getStats().getAttribs();
}

const AttributeList& UnitViewable::getGrowths() const {
	return _ptr->getStats().getGrowths();
}

const WeaponList & UnitViewable::getWeaponProficiencies() const {
	return _ptr->getStats().getWeaponProficiencies();
}

int UnitViewable::avoid() const {
	return _ptr->getStats().avoid();
}

int UnitViewable::dodge() const {
	return _ptr->getStats().dodge();
}

int UnitViewable::hit() const {
	return _ptr->getStats().hit();
}

int UnitViewable::crit() const {
	return _ptr->getStats().crit();
}

int UnitViewable::might() const {
	return _ptr->getStats().might();
}

int UnitViewable::atk_spd() const {
	return _ptr->getStats().atk_spd();
}

int UnitViewable::getExp() const {
	return _ptr->getExperience().getExp();
}

int UnitViewable::getLevel() const {
	return _ptr->getExperience().getLevel();
}

int UnitViewable::getTier() const {
	return _ptr->getExperience().getTier();
}

std::map<MobilitySet, Range::DistanceSet> UnitViewable::getAttackRanges() const {
	return _ptr->getInventory().getAttackRanges();
}

std::map<MobilitySet, Range::DistanceSet> UnitViewable::getAssistRanges() const {
	return _ptr->getInventory().getAssistRanges();
}

int UnitViewable::percentRemaining() const {
	return _ptr->getBattleInfo().percentRemaining();
}

bool UnitViewable::isDead() const {
	return _ptr->getBattleInfo().isDead();
}

int UnitViewable::getMaxHp() const {
	return _ptr->getBattleInfo().getMaxHp();
}

int UnitViewable::getCurrentHp() const {
	return _ptr->getBattleInfo().getCurrentHp();
}

bool UnitViewable::hasMajor() const {
	return _ptr->getBattleInfo().hasMajor();
}

bool UnitViewable::hasMinor() const {
	return _ptr->getBattleInfo().hasMinor();
}

int UnitViewable::moveUsed() const {
	return _ptr->getBattleInfo().moveUsed();
}

bool UnitViewable::hasIndependent(const BattleInfo::ActionId& action) const {
	return _ptr->getBattleInfo().hasIndependent(action);
}

const std::set<BattleInfo::ActionId>& UnitViewable::usedIndependents() const {
	return _ptr->getBattleInfo().usedIndependents();
}

int UnitViewable::operator[](AttribType stat) const {
	return _ptr->getStats()[stat];
}

const ItemEquip& UnitViewable::operator[](EquipSlot slot) const {
	return _ptr->getInventory()[slot];
}

const Item & UnitViewable::operator[](size_t inventory_slot) const {
	return _ptr->getInventory()[inventory_slot];
}

bool UnitViewable::operator==(const UnitViewable& that) const {
	return _ptr == that._ptr;
}

bool UnitViewable::operator!=(const UnitViewable& that) const {
	return _ptr != that._ptr;;
}

void UnitViewable::attach(ObserverDamage& observer) {
	_ptr->attach(observer);
}
void UnitViewable::detach(ObserverDamage& observer) {
	_ptr->detach(observer);
}

void UnitViewable::attach(ObserverExp& observer) {
	_ptr->attach(observer);
}
void UnitViewable::detach(ObserverExp& observer) {
	_ptr->detach(observer);
}
