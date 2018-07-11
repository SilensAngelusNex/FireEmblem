#pragma once

#include <string>

class PartyBase;

class Identity {
private:
	const std::string _name;
	PartyBase* _party;

public:
	Identity(std::string name, PartyBase* party=nullptr);

	const std::string& getName() const;
	PartyBase* getParty() const;
	PartyBase* setParty(PartyBase* new_party);
};