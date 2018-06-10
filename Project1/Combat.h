#pragma once

#include <optional>

#include "ObservableDamage.h"
#include "Component.h"
#include "Stats.h"
#include "Inventory.h"
#include "Experience.h"
#include "optional_pair.h"

class Unit;

class Combat : Component<Unit>, public ObservableDamage {
private:
	// Combat and Strike Skills
public:
	explicit Combat(Unit& owner);

	void combat(Unit& defender);
	bool doesAvoid(Unit& attacker);
	std::optional<int> strike(Unit& defender);
	int takeDamage(Damage dealt);
protected:
	optional_pair<int, int> do_combat(Unit& defender);
};
