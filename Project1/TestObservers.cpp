#include <iostream>

#include "TestObservers.h"


void DmgObserver::notifyMiss(const std::string&  name) {
	std::cout << "The strike missed " << name << "!" << std::endl;
}

void DmgObserver::notifyDeflect(const std::string&  name) {
	std::cout << name << " deflected the strike!" << std::endl;
}

void DmgObserver::notifyDamage(const std::string&  name, int dmg) {
	std::cout << name << " took " << dmg << " damage." << std::endl;
}

void DmgObserver::notifyCrit(const std::string&  name, int dmg) {
	std::cout << name << " took " << dmg << " crit damage." << std::endl;
}

void DmgObserver::notifyHeal(const std::string&  name, int heal) {
	std::cout << name << " healed for " << heal << " points." << std::endl;
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
