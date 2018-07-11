#pragma once

#include "Damage.h"
#include "Identity.h"

class ObserverDamage {
public:
	virtual void notifyMiss(const Identity&) = 0;
	virtual void notifyDeflect(const Identity&) = 0;
	virtual void notifyDamage(const Identity&, int) = 0;
	virtual void notifyCrit(const Identity&, int) = 0;
	virtual void notifyHeal(const Identity&, int) = 0;
};
