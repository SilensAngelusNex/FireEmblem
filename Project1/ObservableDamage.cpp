#include "ObservableDamage.h"

#include <algorithm>




void ObservableDamage::notifyAllMiss(const Identity& name) {
	std::for_each(
		_observers.begin(),
		_observers.end(), 
		[&name](ObserverDamage* observer){observer->notifyMiss(name);});
}

void ObservableDamage::notifyAllDeflect(const Identity& name) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name](ObserverDamage* observer) {observer->notifyMiss(name); });
}

void ObservableDamage::notifyAllDamage(const Identity& name, int dealt) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name, dealt](ObserverDamage* observer) {observer->notifyDamage(name, dealt); });
}

void ObservableDamage::notifyAllCrit(const Identity&  name, int dealt) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name, dealt](ObserverDamage* observer) {observer->notifyCrit(name, dealt); });
}

void ObservableDamage::notifyAllHeal(const Identity& name, int amount) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name, amount](ObserverDamage* observer) {observer->notifyHeal(name, amount); });
}