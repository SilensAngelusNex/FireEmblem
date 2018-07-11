#include <iostream>

#include "TestObservers.h"


void DmgObserver::notifyMiss(const Identity&  name) {
	std::cout << "The strike missed " << name.getName() << "!" << std::endl;
}

void DmgObserver::notifyDeflect(const Identity&  name) {
	std::cout << name.getName() << " deflected the strike!" << std::endl;
}

void DmgObserver::notifyDamage(const Identity&  name, int dmg) {
	std::cout << name.getName() << " took " << dmg << " damage." << std::endl;
}

void DmgObserver::notifyCrit(const Identity&  name, int dmg) {
	std::cout << name.getName() << " took " << dmg << " crit damage." << std::endl;
}

void DmgObserver::notifyHeal(const Identity&  name, int heal) {
	std::cout << name.getName() << " healed for " << heal << " points." << std::endl;
}


void ExpObserver::notifyExpUp(int before, int after) {
	std::cout << "Exp:\t" << before << " -> " << after << std::endl;
}

void ExpObserver::notifyLevelUp(int after, const AttributeList&  /*stat_gains*/) {
	std::cout << "Level:\t" << after - 1 << " -> " << after << std::endl;
}

void ExpObserver::notifyTierUp(int after) {
	std::cout << "Tier:\t" << after - 1 << " -> " << after << std::endl;
}
