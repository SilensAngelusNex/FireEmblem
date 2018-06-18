#pragma once
#include "Unit.h"

class Map;
class Party;
using UnitPtr = std::unique_ptr<Unit>;
struct UnitData;
struct PartyData {
	std::string name;
	std::vector<UnitData> unit_data;
};
class PartyBase {
private:
	PartyBase(const PartyBase& party) = delete;
	PartyBase& operator=(const PartyBase & party) = delete;
protected:
	std::string _party_name;
	std::vector<UnitPtr> _units;

	PartyBase();
	PartyBase(std::string name);
	PartyBase(std::string name, std::vector<UnitData> unit_data);
	PartyBase(PartyData data);

	std::vector<UnitPtr>::const_iterator getPosition(const Unit& unit) const;
	std::vector<UnitPtr>::iterator getPosition(const Unit& unit);

	void insertUnit(UnitData unit);
	void insertUnit(Unit& unit);
public:
	Party& getParty(Passkey<Map> key);
	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
};

