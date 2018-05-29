#pragma once

#include "AttributeList.h"
#include "Dice.h"
#include "Component.h"
#include "ObservableExp.h"
#include "Stats.h"
class Unit;

class Experience : Component<Unit>, public ObservableExp {
private:
	constexpr static int _EXP_PER_LEVEL = 100;
	constexpr static int _LEVELS_PER_TIER = 20;
	constexpr static int _MAX_GROWTH_CHANCE = 80;
	// For attributes with higher than 80 growth rate (or whatever MAX_GROWTH_CHANCE is), a dice check
	// for growth is made with 80% chance of success, then checks proceed with original rate minus 80
	// Ex. Growth of 250 will roll 4 checks total with growth percentages: 80, 80, 80, 10

	Dice<100>& _dice;
	// TODO(Weston): Add caps for exp/level
	int _exp;
public:
	Experience(Unit& owner, Dice<100>& dice);
	Experience(Unit& owner, Dice<100>& dice, int level);

	void gainExp(int gains);
	void gainCombatExp(Unit& enemy, int largest_strike);

	int getExp() const;
	int getLevel() const;
	int getTier() const;
protected:
	void levelUp();
	AttributeList getLevelGrowths() const;
};
