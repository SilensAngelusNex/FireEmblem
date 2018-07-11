#pragma once

#include <string>
#include <vector>

#include "Observable.h"
#include "ObserverDamage.h"
#include "ObserverExp.h"
#include "AttributeList.h"
#include "Damage.h"
#include "Identity.h"
#include "Inventory.h"
#include "Combat.h"
#include "Dice.h"
#include "Experience.h"
#include "Mobility.h"
#include "Health.h"
#include "BattleInfo.h"
#include "logical_reference_wrapper.h"

class PartyBase;
using CONTEXT = Dice<100>;
struct UnitData {
	std::string name;
	CONTEXT& context;
	AttributeList stats;
};
class Unit : public ObservableDamage, public ObservableExp {
private:
	Identity _id;
	CONTEXT& _context;
	Stats _stats;
	Experience _exp;
	Inventory _inv;
	Combat _combat;
	Mobility _mobility;
	BattleInfo _battle_info;

public:
	Unit(std::string id, CONTEXT& context, AttributeList stats);
	Unit(Identity id, CONTEXT& context, AttributeList stats);
	Unit(UnitData data);

	// Viewable Unit
	const Identity& getIdentity() const;
	const Stats& getStats() const;
	const Mobility& getMobility() const;
	const Experience& getExperience() const;
	const InventoryViewable& getInventory() const;
	const PartyBase* getParty() const;
	const BattleInfo& getBattleInfo() const;
	using ObservableDamage::attach;
	using ObservableDamage::detach;
	using ObservableExp::attach;
	using ObservableExp::detach;



	// Commandable Unit
	InventoryCommandable& getInventory();
	BattleInfo& getBattleInfo();
	Combat& getCombat();
	// Move into identity component
	PartyBase* getParty();
	PartyBase* setParty(PartyBase* other_party);
	// Move into into battle info component
	void refresh();
	void newTurn();
	bool isTired() const;

	// Unit Internals
	Stats& getStats();
	Mobility& getMobility();
	Experience& getExperience();
	Inventory& getInventoryInternal();
	CONTEXT& getContext();


	bool operator==(const Unit& unit) const;
	bool operator!=(const Unit& unit) const;

	using Ref = logical_reference_wrapper<Unit>;
	using ConstRef = logical_reference_wrapper<const Unit>;
	using UniquePtr = std::unique_ptr<Unit>;
};
