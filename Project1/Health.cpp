#include "Health.h"

HealthValues::HealthValues(int con) : HealthValues(con, 0, 0, false) {}
HealthValues::HealthValues(int con, int missing_hp) : HealthValues(con, missing_hp, 0, false) {}
HealthValues::HealthValues(int con, int missing_hp, int shield_hp) : HealthValues(con, missing_hp, shield_hp, false) {}

HealthValues::HealthValues(int con, int missing_hp, int shield_hp, bool has_divine_shield) :
	_total_hp(10 * con),
	_current_hp(_total_hp - missing_hp),
	_shield_hp(shield_hp),
	_has_divine_shield(has_divine_shield)
{}

int HealthValues::percentRemaining() {
	return 100 * _current_hp / _total_hp;
}


Health::Health(int con) :
	_values(con)
{}

Health::Health(HealthValues values) :
	_values(values)
{}

int Health::percentRemaining() {
	return _values.percentRemaining();
}

int Health::isDead() {
	return _values._current_hp <= 0;
}