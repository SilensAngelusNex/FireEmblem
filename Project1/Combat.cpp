#include "Combat.h"
#include "Unit.h"
#include <iostream>

Combat::Combat(Unit& owner) : Component<Unit>(owner) {}


void Combat::combat(Unit& defender) {
	std::pair<int, int> largest_strikes = do_combat(defender);

	_owner.getExperience().gainCombatExp(defender, largest_strikes.first);
	defender.getExperience().gainCombatExp(_owner, largest_strikes.second);
}

bool Combat::doesDodge(Unit& attacker) {
	CONTEXT& dice = _owner.getContext();

	int hit_chance = attacker.getStats().hit();
	int hit_roll = dice.rollX(2);
	int avo = _owner.getStats().avoid();

	if (hit_roll >= 2 * hit_chance - avo) {
		notifyAllMiss(_owner.getIdentity());
		return true;
	}

	hit_chance -= avo;
	if (hit_roll >= 2 * hit_chance) {
		notifyAllDeflect(_owner.getIdentity());
		return true;
	}

	return false;
}

int Combat::strike(Unit& defender) {
	CONTEXT& dice = _owner.getContext();

	if (defender.getCombat().doesDodge(_owner)) {
		return -1;
	}

	// trigger this strike skills
	// trigger defender struck skills

	int crit_chance = _owner.getStats().crit() - defender.getStats().dodge();
	if (dice.roll() < 2 * crit_chance) {
		return defender.getCombat().takeDamage(_owner.getInventoryInternal().getCritDamage(defender));
	}
	return defender.getCombat().takeDamage(_owner.getInventoryInternal().getNormalDamage(defender));
}

int Combat::takeDamage(Damage dealt) {
	int result = dealt.getDamageTo(_owner);
	// TODO(Weston): Reduce HP
	if (dealt.isCrit()) {
		notifyAllCrit(_owner.getIdentity(), result);
	}
	else {
		notifyAllDamage(_owner.getIdentity(), result);
	}
	return result;
}

std::pair<int, int> Combat::do_combat(Unit& defender) {
	// trigger this combat init skills
	// trigger defender defend combat skills

	std::pair<int, int> result = std::pair<int, int>(-1, -1);

	int spd_adv = _owner.getStats().atk_spd() - defender.getStats().atk_spd();

	result.first = std::max(result.first, strike(defender));
	result.second = std::max(result.second, defender.getCombat().strike(_owner));

	if (spd_adv > 3) {
		result.first = std::max(result.first, strike(defender));
	}
	if (spd_adv < -3) {
		result.second = std::max(result.second, defender.getCombat().strike(_owner));
	}

	return result;
}
