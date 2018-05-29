#pragma once

#include "ObservableDamage.h"
#include "Component.h"
#include "Stats.h"
#include "Inventory.h"
#include "Experience.h"

class Unit;

class Combat : Component<Unit>, public ObservableDamage {
private:
	// Combat and Strike Skills
public:
	explicit Combat(Unit& owner);

	void combat(Unit& defender);
	bool doesDodge(Unit& attacker);
	int strike(Unit& defender);
	int takeDamage(Damage dealt);
protected:
	std::pair<int, int> do_combat(Unit& defender);
};
