#include "Healing.h"

Healing::Healing(const Unit& source, int raw_amount) :
	_source(source),
	_raw_amount(raw_amount)
{}

int Healing::getHealingFor(const Unit& /*recipient*/) {
	// TODO(Torrey): Anything else we want here? Is there a common case when healing should be better or worse depending on target?
	return _raw_amount;
}

