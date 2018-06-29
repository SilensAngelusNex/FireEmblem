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

	using iterator = std::list<Unit::Ptr>::iterator;
	using const_iterator = std::list<Unit::Ptr>::const_iterator;

	std::string _party_name;
	std::list<Unit::Ptr> _units;

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
	const Party& getParty(Passkey<GridMap>) const;

	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
	bool operator!=(const PartyBase& other) const;

	PartyBase(const PartyBase& party) = delete;
	PartyBase& operator=(const PartyBase & party) = delete;
};

