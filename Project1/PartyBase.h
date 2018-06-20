#pragma once
#include "Unit.h"
#include <list>

class Grid;
class Party;
class party_iterator;
using UnitRef = std::reference_wrapper<Unit>;
using constUnitRef = std::reference_wrapper<const Unit>;
using UnitPtr = std::unique_ptr<Unit>;
struct UnitData;
struct PartyData {
	std::string name;
	std::vector<UnitData> unit_data;
};
class PartyBase {
protected:

	using iterator = std::list<UnitPtr>::iterator;
	using const_iterator = std::list<UnitPtr>::const_iterator;

	std::string _party_name;
	std::list<UnitPtr> _units;

	PartyBase();
	PartyBase(std::string name);
	PartyBase(std::string name, std::vector<UnitData> unit_data);
	PartyBase(PartyData data);
	~PartyBase() = default;

	void insertUnit(UnitData unit);
	const_iterator getPosition(const Unit& unit) const;
	iterator getPosition(const Unit& unit);

public:
	Party& getParty(Passkey<Grid> key);

	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
	bool operator!=(const PartyBase& other) const;

	PartyBase(const PartyBase& party) = delete;
	PartyBase& operator=(const PartyBase & party) = delete;
};

