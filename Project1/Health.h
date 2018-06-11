#pragma once
#include "Component.h"
#include "Damage.h"
#include "Healing.h"

class Unit;

class Health : Component<Unit> {
private:
	int _missing_hp;

	// Skills
public:
	explicit Health(Unit& owner);
	explicit Health(Unit& owner, int missing_hp);
	explicit Health(Unit& owner, int missing_hp);

	int takeDamage(Damage to_take);
	int heal(Healing to_heal);
	int percentRemaining() const;
	bool isDead() const;
	int getMaxHp() const;
	int getCurrentHp() const;
};