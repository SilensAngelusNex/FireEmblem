#pragma once

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