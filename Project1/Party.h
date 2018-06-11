#pragma once
#include "Unit.h"
#include "PartyBase.h"

class Party: public PartyBase
{
public:
	Party();
	Party(std::string name);
	Party(std::string name, std::vector<UnitData> unit_data);
	Party(PartyData data);
	Unit& getUnit(int index);
	std::vector<std::reference_wrapper<Unit>> getUnits();
	void startTurn();
	bool isDone();
	bool hasUnit(Unit& unit);
	void insertUnit(UnitData unit);
	void changeParty(Unit& unit, Party& party);
};

