#pragma once
#include "Unit.h"

class Map;
class Party;
using UnitPtr = std::unique_ptr<Unit>;
struct UnitData;
struct PartyData
{
	std::string name;
	std::vector<UnitData> unit_data;
};
class PartyBase
{
private:
	std::vector<UnitPtr>::const_iterator getPosition(const Unit& unit) const;
	std::vector<UnitPtr>::iterator getPosition(const Unit& unit);
protected:
	std::string _party_name;
	std::vector<UnitPtr> _units;

	PartyBase();
	PartyBase(std::string name);
	PartyBase(std::string name, std::vector<UnitData> unit_data);
	PartyBase(PartyData data);
	void startTurn();
	bool isDone();
	void insertUnit(UnitData unit);
	void changeParty(Unit& unit, PartyBase& new_party);
public:
	Party& getParty(Passkey<Map> key);
	bool hasUnit(const Unit& unit) const;
};

