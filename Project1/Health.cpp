#include "Health.h"

#include <algorithm>

#include "Unit.h"

Health::Health(Unit& owner) :
	Health(owner, 0)
{}

Health::Health(Unit& owner, int missing_hp) :
	Component(owner),
	_missing_hp(missing_hp)
{}


int Health::takeDamage(Damage to_take) {
	// Pass Damage and/or difference by ref to skills
	//On taking damage, on dealing damage
	int difference = std::min(to_take.getDamageTo(_owner), getMaxHp() - _missing_hp);
	_missing_hp += difference;
	return difference;
}

int Health::heal(Healing to_heal) {
	// Pass Healing and/or difference by ref to skills
	// On heal, on healed
	int difference = std::min(to_heal.getHealingFor(_owner), _missing_hp);
	_missing_hp -= difference;
	return difference;
}

int Health::percentRemaining() const {
	int max = getMaxHp();
	return (200 * getCurrentHp() + max) / (2 * max);
}

bool Health::isDead() const {
	return getCurrentHp() <= 0;
}

int Health::getMaxHp() const {
	return 10 * _owner.getStats()[AttribType::values::CON];
}

int Health::getCurrentHp() const {
	return getMaxHp() - _missing_hp;
}

