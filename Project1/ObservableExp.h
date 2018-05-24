#pragma once

#include "Observable.h"
#include "ObserverExp.h"
#include "AttributeList.h"

class ObservableExp : public Observable<ObserverExp> {
protected:
	void notifyAllExp(int before, int after);
	void notifyAllLevel(int after, const AttributeList& growths);
	void notifyAllTier(int after);
};