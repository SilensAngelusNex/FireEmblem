#pragma once

#include "ObserverDamage.h"
#include "ObserverExp.h"
#include "Identity.h"

class ExpObserver : public ObserverExp {
public:
	void notifyExpUp(int before, int after) override;
	void notifyLevelUp(int after, const AttributeList& stat_gains) override;
	void notifyTierUp(int after) override;
};

class DmgObserver : public ObserverDamage {
public:
	void notifyMiss(const Identity&  name) override;
	void notifyDeflect(const Identity&  name) override;
	void notifyDamage(const Identity&  name, int dmg) override;
	void notifyCrit(const Identity&  name, int dmg) override;
	void notifyHeal(const Identity&  name, int heal) override;
};