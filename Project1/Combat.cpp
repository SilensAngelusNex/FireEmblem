#include "Combat.h"
#include "Unit.h"
#include "AttackHelper.h"
#include <iostream>

Combat::Combat(Unit& owner) : Component<Unit>(owner) {}


void Combat::combat(Unit& defender, bool can_retaliate) {
	Expects(&_owner != &defender);
	optional_pair<int> largest_strikes = do_combat(defender, can_retaliate);

	_owner.getExperience().gainCombatExp(defender, largest_strikes.first);
	defender.getExperience().gainCombatExp(_owner, largest_strikes.second);
}

bool Combat::doesAvoid(Unit& attacker) {
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

std::optional<int> Combat::strike(Unit& defender) {
	CONTEXT& dice = _owner.getContext();

	if (defender.getCombat().doesAvoid(_owner)) {
		return {};
	}

	auto strike = [&dice](Unit& attacker, Unit& defender) {
		int crit_chance = attacker.getStats().crit() - defender.getStats().dodge();
		if (dice.roll() < 2 * crit_chance) {
			return attacker.getInventoryInternal().getCritDamage(defender);
		}
		return attacker.getInventoryInternal().getNormalDamage(defender);
	};

	// Pass lambda to combat skills
	// On strike, on struck
	return defender.getCombat().takeDamage(strike(_owner, defender));
}

int Combat::takeDamage(Damage dealt) {
	int result = _owner.getHealth().takeDamage(dealt);
	// TODO(Weston): Move these into Health so we can remove this function
	if (dealt.isCrit()) {
		notifyAllCrit(_owner.getIdentity(), result);
	}
	else {
		notifyAllDamage(_owner.getIdentity(), result);
	}
	return result;
}

optional_pair<int, int> Combat::do_combat(Unit& defender, bool can_retaliate) {
	auto combat = [can_retaliate](Unit& attacker, Unit& defender) {

		optional_pair<int> result;
		int spd_adv = attacker.getStats().atk_spd() - defender.getStats().atk_spd();

		result.first = std::max(result.first, attacker.getCombat().strike(defender));

		if (can_retaliate && !defender.getHealth().isDead()) {
			result.second = std::max(result.second, defender.getCombat().strike(attacker));
		}
		if (spd_adv > SPEED_DIFFERENCE_TO_DOUBLE && !attacker.getHealth().isDead()) {
			result.first = std::max(result.first, attacker.getCombat().strike(defender));
		}
		if (can_retaliate && spd_adv < -SPEED_DIFFERENCE_TO_DOUBLE && !defender.getHealth().isDead()) {
			result.second = std::max(result.second, defender.getCombat().strike(attacker));
		}
		return result;
	};

	// Pass lambda to combat skills
	// On attack, on attacked, during combat
	return combat(_owner, defender);
}
