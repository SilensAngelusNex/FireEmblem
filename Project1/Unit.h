#pragma once

#include <string>
#include <vector>

#include "Observable.h"
#include "ObserverDamage.h"
#include "ObserverExp.h"
#include "AttributeList.h"
#include "Damage.h"
#include "Inventory.h"
#include "Combat.h"
#include "Dice.h"
#include "Experience.h"
#include "Mobility.h"
#include "Health.h"
#include "PartyBase.h"
#include "BattleInfo.h"

class PartyBase;
using IDENTITY = std::string;
using CONTEXT = Dice<100>;
struct UnitData {
	IDENTITY name;
	CONTEXT& context;
	AttributeList stats;
};
class Unit : public Observable<ObserverDamage>, public Observable<ObserverExp> {
private:
	IDENTITY _id;
	CONTEXT& _context;

	Stats _stats;
	Experience _exp;
	Inventory _inv;
	Combat _combat;
	Mobility _mobility;
	BattleInfo _battle_info;

	//Location& _loc;
public:
	Unit(IDENTITY name, CONTEXT& context, AttributeList stats);
	Unit(UnitData data) : Unit(data.name, data.context, data.stats) {};

	// Viewable Unit
	const IDENTITY& getIdentity() const;
	const Stats& getStats() const;
	const Mobility& getMobility() const;
	const Experience& getExperience() const;
	const InventoryViewable& getInventory() const;
	const BattleInfo& getBattleInfo() const;

	// Commandable Unit
	InventoryCommandable& getInventory();
	BattleInfo& getBattleInfo();
	Combat& getCombat();
	void refresh();
	void newTurn();
	bool isTired() const;

	// Unit Internals
	Stats& getStats();
	Mobility& getMobility();
	Experience& getExperience();
	Inventory& getInventoryInternal();
	CONTEXT& getContext();
	PartyBase* _party;

	 
	// Observable
	void attach(ObserverDamage* observer) {
		_combat.attach(observer);
	}
	void attach(ObserverDamage& observer) {
		_combat.attach(observer);
	}
	void detach(ObserverDamage* observer) {
		_combat.detach(observer);
	}
	void detach(ObserverDamage& observer) {
		_combat.detach(observer);
	}
	
	void attach(ObserverExp* observer) {
		_exp.attach(observer);
	}
	void attach(ObserverExp& observer) {
		_exp.attach(observer);
	}
	void detach(ObserverExp* observer) {
		_exp.detach(observer);
	}
	void detach(ObserverExp& observer) {
		_exp.detach(observer);
	}
	bool operator==(const Unit& unit) const;
	bool operator!=(const Unit& unit) const;
};