#pragma once

#include <optional>

#include "ObservableDamage.h"
#include "Component.h"
#include "Stats.h"
#include "Inventory.h"
#include "Experience.h"
#include "optional_pair.h"
#include "AttackHelper.h"


class Unit;

class Combat : Component<Unit>, public ObservableDamage, private AttackContainer {
private:
	// Combat and Strike Skills
public:
	constexpr static int SPEED_DIFFERENCE_TO_DOUBLE = 3;

	explicit Combat(Unit& owner);

	void combat(Unit& defender, bool can_retaliate=true);
	bool doesAvoid(Unit& attacker);
	std::optional<int> strike(Unit& defender);
	int takeDamage(Damage dealt);
protected:
	optional_pair<int> do_combat(Unit& defender, bool can_retaliate=true);
};
