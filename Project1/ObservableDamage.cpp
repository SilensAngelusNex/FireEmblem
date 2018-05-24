#include "ObservableDamage.h"

#include <algorithm>


void ObservableDamage::notifyAllMiss(const std::string& name) {
	std::for_each(
		_observers.begin(),
		_observers.end(), 
		[&name](ObserverDamage* observer){observer->notifyMiss(name);});
}

void ObservableDamage::notifyAllDeflect(const std::string&  name) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name](ObserverDamage* observer) {observer->notifyMiss(name); });
}

void ObservableDamage::notifyAllDamage(const std::string&  name, int dealt) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name, dealt](ObserverDamage* observer) {observer->notifyDamage(name, dealt); });
}

void ObservableDamage::notifyAllCrit(const std::string&  name, int dealt) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name, dealt](ObserverDamage* observer) {observer->notifyCrit(name, dealt); });
}

void ObservableDamage::notifyAllHeal(const std::string&  name, int amount) {
	std::for_each(
		_observers.begin(),
		_observers.end(),
		[&name, amount](ObserverDamage* observer) {observer->notifyHeal(name, amount); });
}