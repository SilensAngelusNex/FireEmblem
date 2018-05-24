#include "ObservableExp.h"
#include "AttributeList.h"

void ObservableExp::notifyAllExp(int before, int after) {
	for (ObserverExp* observer : _observers) {
		observer->notifyExpUp(before, after);
	}
}

void ObservableExp::notifyAllLevel(int after, const AttributeList& growths) {
	for (ObserverExp* observer : _observers) {
		observer->notifyLevelUp(after, growths);
	}
}

void ObservableExp::notifyAllTier(int after) {
	for (ObserverExp* observer : _observers) {
		observer->notifyTierUp(after);
	}
}