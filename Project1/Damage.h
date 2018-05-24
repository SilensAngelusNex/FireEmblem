#pragma once

#define PERCENT_REDUX_CONSTANT 5.0
#define FLAT_REDUX_CONSTANT 2

#include "AttributeList.h"

class Unit;

class Damage {
protected:
	int _raw_damage;
	AttribType _armor_type;
	bool _is_crit;

	int _percent_final_damage;
	int _flat_pen;
	int _percent_pen;

	//TODO(Weston): Add super-effective bonuses
public:
	Damage();
	explicit Damage(int raw);
	explicit Damage(int raw, AttribType armor);
	explicit Damage(int raw, AttribType armor, bool crit);
	explicit Damage(int raw, AttribType armor, bool crit, int final_percent);
	explicit Damage(int raw, AttribType armor, bool crit, int final_percent, int flat_pen, int percent_pen);

	virtual int getDamageTo(Unit& defender);
	virtual int getRawDamage();
	virtual bool isCrit();
protected:
	int getFlatReduction(int armor);
	int getPercentReduction(int armor);
	virtual int getArmor(Unit& defender);
};
