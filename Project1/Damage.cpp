#include <cmath>

#include "Damage.h"
#include "Unit.h"


Damage::Damage() : Damage(0, AttribType::values::DEF, false, 100, 0, 0) {}
Damage::Damage(int raw) : Damage(raw, AttribType::values::DEF, false, 100, 0, 0) {}
Damage::Damage(int raw, AttribType armor) : Damage(raw, armor, false, 100, 0, 0) {}
Damage::Damage(int raw, AttribType armor, bool crit) : Damage(raw, armor, crit, 100, 0, 0) {}
Damage::Damage(int raw, AttribType armor, bool crit, int final_percent) : Damage(raw, armor, crit, final_percent, 0, 0) {}
Damage::Damage(int raw, AttribType armor, bool crit, int final_percent, int flat_pen, int percent_pen) :
	_raw_damage(raw),
	_armor_type(armor),
	_is_crit(crit),
	_percent_final_damage(final_percent),
	_flat_pen(flat_pen),
	_percent_pen(percent_pen)
	{}

int Damage::getDamageTo(Unit& defender) {
	int armor = getArmor(defender);
	int resist = std::min(100, getPercentReduction(armor));
	int reduce = std::min(100, getFlatReduction(armor));
	
	int post_reduce = 10 * _raw_damage - reduce;
	int result = (post_reduce * resist) / 100;

	if (_is_crit) {
		// + 1 makes number rounded instead of truncated
		int crit_resist = (100 + resist + 1) / 2;
		result += (_raw_damage * crit_resist) / 10;
	}

	return _percent_final_damage * std::max(0, result) / 100;
}

int Damage::getRawDamage() {
	return _raw_damage;
}

bool Damage::isCrit() {
	return _is_crit;
}

int Damage::getFlatReduction(int armor) {
	return (10 * armor) / _FLAT_REDUX_CONSTANT - 10 * _flat_pen;
}

int Damage::getPercentReduction(int armor) {
	// The 1005 and / 10 makes the result be rounded instead of truncating.
	auto base_redux = static_cast<int>(1005 / (std::sqrt(armor / _PERCENT_REDUX_CONSTANT + 1) * 10));
	return base_redux * (100 - _percent_pen) / 100;
}

int Damage::getArmor(Unit& defender) {
	return defender.getStats().getAttribs()[_armor_type];
}