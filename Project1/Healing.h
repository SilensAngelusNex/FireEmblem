#pragma once

class Unit;


class Healing {
public:
	const Unit& _source;
	const int _raw_amount;
	explicit Healing(const Unit& source, int raw_amount);
	explicit Healing(const Unit& source, int raw_amount);

	int getHealingFor(const Unit& recipient);
};