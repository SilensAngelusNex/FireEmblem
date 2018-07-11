#pragma once

#include "Observable.h"
#include "ObserverDamage.h"
#include "Identity.h"

class ObservableDamage : public Observable<ObserverDamage> {
protected:
	void notifyAllMiss(const Identity&  name);
	void notifyAllDeflect(const Identity&  name);
	void notifyAllDamage(const Identity&  name, int dealt);
	void notifyAllCrit(const Identity&  name, int dealt);
	void notifyAllHeal(const Identity&  name, int amount);
};