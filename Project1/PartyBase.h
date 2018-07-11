#pragma once

#include "Unit.h"

#include <list>

class GridMap;
class Party;
class party_iterator;

struct UnitData;
struct PartyData {
	std::string name;
	std::vector<UnitData> unit_data;
};
class PartyBase {
protected:

	using iterator = std::list<Unit::UniquePtr>::iterator;
	using const_iterator = std::list<Unit::UniquePtr>::const_iterator;

	std::string _party_name;
	std::list<Unit::UniquePtr> _units;

	PartyBase();
	PartyBase(std::string name);
	PartyBase(std::string name, std::vector<UnitData> unit_data);
	PartyBase(PartyData data);
	~PartyBase() = default;

	void insertUnit(UnitData unit);
	const_iterator getPosition(const Unit& unit) const;
	iterator getPosition(const Unit& unit);

public:
	Party& getParty(Passkey<GridMap> /*unused*/);
	const Party& getParty(Passkey<GridMap> /*unused*/) const;

	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
	bool operator!=(const PartyBase& other) const;

	PartyBase(const PartyBase& party) = delete;
	PartyBase& operator=(const PartyBase & party) = delete;
};

