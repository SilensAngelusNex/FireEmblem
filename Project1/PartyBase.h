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
	using iterator = std::vector<UnitPtr>::iterator;
	using const_iterator = std::vector<UnitPtr>::const_iterator;
	iterator begin() { return _units.begin(); }
	iterator end() { return _units.end(); }
	const_iterator cbegin() const { return _units.cbegin(); }
	const_iterator cend() const { return _units.cend(); }
public:
	Party& getParty(Passkey<Map> key);
	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
};

