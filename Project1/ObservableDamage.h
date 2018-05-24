#ifndef OBSERVABLE_DAMAGE_H
#define OBSERVABLE_DAMAGE_H

#include <string>

#include "Observable.h"
#include "ObserverDamage.h"

class ObservableDamage : public Observable<ObserverDamage> {
protected:
	void notifyAllMiss(const std::string&  name);
	void notifyAllDeflect(const std::string&  name);
	void notifyAllDamage(const std::string&  name, int dealt);
	void notifyAllCrit(const std::string&  name, int dealt);
	void notifyAllHeal(const std::string&  name, int amount);
};

#endif // !OBSERVABLE_DAMAGE_H