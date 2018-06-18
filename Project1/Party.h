#pragma once
#include "PartyBase.h"

class Party: public PartyBase {
public:
	Party();
	Party(std::string name);
	Party(std::string name, std::vector<UnitData> unit_data);
	Party(PartyData data);
	Unit& getUnit(int index);
	std::vector<std::reference_wrapper<Unit>> getUnits();
	std::vector<std::reference_wrapper<Unit>> getOtherUnits(Unit& unit);
	void startTurn(PartyBase party_turn);
	bool isDone();
	bool hasUnit(Unit& unit);
	void insertUnit(UnitData unit);
	void changeParty(Unit& unit, Party& party);
};

