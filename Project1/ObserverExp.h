#pragma once

#include "AttributeList.h"

class ObserverExp {
public:
	virtual void notifyExpUp(int, int) = 0;
	virtual void notifyLevelUp(int, const AttributeList&) = 0;
	virtual void notifyTierUp(int) = 0;
};