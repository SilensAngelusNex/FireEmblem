#pragma once

#include <memory>
#include "Unit.h"


class UnitViewable {
protected:
	std::unique_ptr<Unit> _ptr;
	UnitViewable(std::unique_ptr<Unit> unit);

	~UnitViewable() = default;
public:
	[[deprecated("Call methods directly.")]]
	const Identity& getIdentity() const;
	[[deprecated("Call methods directly.")]]
	const Stats& getStats() const;
	[[deprecated("Call methods directly.")]]
	const Mobility& getMobility() const;
	[[deprecated("Call methods directly.")]]
	const Experience& getExperience() const;
	[[deprecated("Call methods directly.")]]
	const InventoryViewable& getInventory() const;
	[[deprecated("Call methods directly.")]]
	const BattleInfo& getBattleInfo() const;

	// Identity
	const std::string& getName() const;
	const PartyBase* getParty() const;

	// Stats
	const AttributeList& getAttribs() const;
	const AttributeList& getGrowths() const;
	const WeaponList& getWeaponProficiencies() const;
	int avoid() const;
	int dodge() const;
	int hit() const;
	int crit() const;
	int might() const;
	int atk_spd() const;

	// Experience
	int getExp() const;
	int getLevel() const;
	int getTier() const;

	// Inventory
	std::map<MobilitySet, Range::DistanceSet> getAttackRanges() const;
	std::map<MobilitySet, Range::DistanceSet> getAssistRanges() const;

	// Battle Info
	int percentRemaining() const;
	bool isDead() const;
	int getMaxHp() const;
	int getCurrentHp() const;

	bool hasMajor() const;
	bool hasMinor() const;
	int moveUsed() const;
	bool hasIndependent(BattleInfo::ActionId action) const;
	const std::set<BattleInfo::ActionId>& usedIndependents() const;

	// Subscript operators
	int operator[](AttribType stat) const;
	const ItemEquip& operator[](EquipSlot slot) const;
	const Item& operator[](size_t inventory_slot) const;

	// Equality
	bool operator==(const UnitViewable& that) const;
	bool operator!=(const UnitViewable& that) const;

	// Observable
	void attach(ObserverDamage& observer);
	void detach(ObserverDamage& observer);

	void attach(ObserverExp& observer);
	void detach(ObserverExp& observer);
};