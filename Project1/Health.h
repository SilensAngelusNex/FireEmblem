#pragma once

class HealthValues {
public:
	explicit HealthValues(int con);
	explicit HealthValues(int con, int missing_hp);
	explicit HealthValues(int con, int missing_hp, int shield_hp);
	explicit HealthValues(int con, int missing_hp, int shield_hp, bool has_divine_shield);

	int _total_hp;
	int _current_hp;
	int _shield_hp;
	bool _has_divine_shield;

	int percentRemaining();
};

class Health {
private:
	HealthValues _values;

	// Skills
public:
	explicit Health(int con);
	explicit Health(HealthValues values);

	int percentRemaining();
	int isDead();
};