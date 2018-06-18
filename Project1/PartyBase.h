#pragma once
#include "Unit.h"
#include <list>

class Map;
class Party;
class party_iterator;
using UnitRef = std::reference_wrapper<Unit>;
using constUnitRef = std::reference_wrapper<const Unit>;
struct UnitData;
struct PartyData {
	std::string name;
	std::vector<UnitData> unit_data;
};
class PartyBase {
protected:
	using iterator = std::list<Unit>::iterator;
	using const_iterator = std::list<Unit>::const_iterator;

	std::string _party_name;
	std::list<Unit> _units;

	PartyBase();
	PartyBase(std::string name);
	PartyBase(std::string name, std::vector<UnitData> unit_data);
	PartyBase(PartyData data);

	const_iterator getPosition(const Unit& unit) const;
	iterator getPosition(const Unit& unit);

	void insertUnit(UnitData unit);
	void insertUnit(Unit& unit);

	iterator begin() { return _units.begin(); }
	iterator end() { return _units.end(); }
	const_iterator cbegin() const { return _units.cbegin(); }
	const_iterator cend() const { return _units.cend(); }
public:
	Party& getParty(Passkey<Map> key);
	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
	bool operator!=(const PartyBase& other) const;

	PartyBase(const PartyBase& party) = delete;
	PartyBase& operator=(const PartyBase & party) = delete;
};

