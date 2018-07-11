#include "Identity.h"

Identity::Identity(std::string name, PartyBase* party) :
	_name(std::move(name)),
	_party(party)
{}

const std::string& Identity::getName() const {
	return _name;
}

PartyBase* Identity::getParty() const {
	return _party;
}

PartyBase* Identity::setParty(PartyBase* new_party) {
	std::swap(_party, new_party);
	return new_party;
}
