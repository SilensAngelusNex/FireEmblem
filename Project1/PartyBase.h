#pragma once
#include "Unit.h"
#include "PartyIterator.h"

class Map;
class Party;
class party_iterator;
using UnitPtr = std::unique_ptr<Unit>;
struct UnitData;
struct PartyData {
	std::string name;
	std::vector<UnitData> unit_data;
};
class PartyBase {
	friend class party_iterator;
	friend class const_party_iterator;
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
	using iterator = party_iterator;
	using const_iterator = const_party_iterator;
	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this); }
	const_iterator cbegin() const { return const_iterator(*this, 0); }
	const_iterator cend() const { return const_iterator(*this); }
public:
	Party& getParty(Passkey<Map> key);
	bool hasUnit(const Unit& unit) const;
	bool operator==(const PartyBase& other) const;
	bool operator!=(const PartyBase& other) const;

	PartyBase(const PartyBase& party) = delete;
	PartyBase& operator=(const PartyBase & party) = delete;
};

