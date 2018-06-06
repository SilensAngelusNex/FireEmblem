#pragma once
#include "Unit.h"
struct PartyData
{
	std::string name;
	std::vector<UnitData> unit_data;
};
class Party
{
	std::string _party_name;
	std::vector<Unit> _units;
public:
	Party();
	Party(std::string name);
	Party(std::string name, std::vector<UnitData> unit_data);
	Party(PartyData data);
	void startTurn();
	bool isDone();
	bool hasUnit(Unit* unit);
	void insertUnit(Unit & unit);
};

