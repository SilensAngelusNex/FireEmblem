#include "Experience.h"
#include "Unit.h"


Experience::Experience(Unit& owner, Dice<100>& dice) : Experience(owner, dice, 0) {}

Experience::Experience(Unit& owner, Dice<100>& dice, int level) :
	Component<Unit>(owner),
	_dice(dice),
	_exp(_EXP_PER_LEVEL * level)
{}


void Experience::gainExp(int gains) {
	while (gains > 0) {
		int current_exp = getExp();
		if (gains >= _EXP_PER_LEVEL - current_exp) {
			int change = _EXP_PER_LEVEL - current_exp;
			gains -= change;
			_exp += change;

			notifyAllExp(current_exp, _EXP_PER_LEVEL);
			levelUp();
		} else {
			_exp += gains;
			notifyAllExp(current_exp, getExp());
			gains = 0;
		}
	}
}

void Experience::gainCombatExp(Unit& enemy, std::optional<int> largest_strike) {
	int to_gain = 1;
	if (largest_strike && largest_strike >= 0) {
		int level_difference = enemy.getExperience().getLevel() - getLevel();
		int raw_exp = 10 + (level_difference * std::abs(level_difference)) / 3;

		int earned = std::max(5, raw_exp);
		if (largest_strike != 0) {
			to_gain = earned;
		}
		else {
			to_gain = earned / 2;
		}
	}
	gainExp(to_gain);
}

int Experience::getExp() const {
	return _exp % _EXP_PER_LEVEL;
}
int Experience::getLevel() const {
	return _exp / _EXP_PER_LEVEL;
}
int Experience::getTier() const {
	return _exp / (_EXP_PER_LEVEL * _LEVELS_PER_TIER);
}

void Experience::levelUp() {
	AttributeList growths = getLevelGrowths();
	notifyAllLevel(getLevel(), growths);
	_owner.getStats().getAttribs() += growths;

	if (getLevel() % _LEVELS_PER_TIER == 0) {
		// TODO(Weston): trigger class-change
		notifyAllTier(getTier());
	}
}
AttributeList Experience::getLevelGrowths() const {
	AttributeList result;
	const AttributeList& growth_rates = _owner.getStats().getGrowths();

	for (AttribType i : AttribType::list) {
		int growth_rate = growth_rates[i];
		while (growth_rate > 0) {
			if (_dice.roll() < std::min(growth_rate, _MAX_GROWTH_CHANCE)) {
				result[i]++;
			}
			growth_rate -= _MAX_GROWTH_CHANCE;
		}
	}
	return result;
}
