#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

#include <string>

#include "ObserverDamage.h"
#include "ObserverExp.h"


class ExpObserver : public ObserverExp {
public:
	void notifyExpUp(int before, int after) override;
	void notifyLevelUp(int after, const AttributeList& stat_gains) override;
	void notifyTierUp(int after) override;
};

class DmgObserver : public ObserverDamage {
public:
	void notifyMiss(const std::string&  name) override;
	void notifyDeflect(const std::string&  name) override;
	void notifyDamage(const std::string&  name, int dmg) override;
	void notifyCrit(const std::string&  name, int dmg) override;
	void notifyHeal(const std::string&  name, int heal) override;
};

#endif // !TEST_OBSERVER_H