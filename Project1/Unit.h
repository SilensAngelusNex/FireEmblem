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

using IDENTITY = std::string;
using CONTEXT = Dice<100>;

class Unit : public Observable<ObserverDamage>, public Observable<ObserverExp> {
private:
	IDENTITY _id;
	CONTEXT& _context;

	Stats _stats;
	Experience _exp;
	Inventory _inv;
	Combat _combat;
	Health _health;
	Mobility _mobility;

	//Location& _loc;
public:
	Unit(IDENTITY name, CONTEXT& context, AttributeList stats);

	// Viewable Unit
	const IDENTITY& getIdentity() const;
	const Stats& getStats() const;
	const Mobility& getMobility() const;
	const Experience& getExperience() const;
	const InventoryViewable& getInventory() const;
	const Health& getHealth() const;
	//virtual const Location& getLocation() const;

	// Commandable Unit
	InventoryCommandable& getInventory();
	//virtual Location& getLocation();
	Combat& getCombat();
	Health& getHealth();

	// Unit Internals
	Stats& getStats();
	Mobility& getMobility();
	Experience& getExperience();
	Inventory& getInventoryInternal();
	CONTEXT& getContext();

	// Movement
	//Point position() const = 0;
	//void move(std::vector<Point>) = 0;
	//std::map<Point, std::vector<Point>> possibleMoves() const = 0;
	//std::set<Point, std::vector<Point>> possibleAttacks() const = 0;
	 
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
};