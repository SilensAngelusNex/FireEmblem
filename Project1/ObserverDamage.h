#ifndef OBSERVER_DAMAGE_H
#define OBSERVER_DAMAGE_H

#include <string>
#include "Damage.h"

class ObserverDamage {
public:
	virtual void notifyMiss(const std::string&) = 0;
	virtual void notifyDeflect(const std::string&) = 0;
	virtual void notifyDamage(const std::string&, int) = 0;
	virtual void notifyCrit(const std::string&, int) = 0;
	virtual void notifyHeal(const std::string&, int) = 0;
};

#endif // !OBSERVER_DAMAGE_H
