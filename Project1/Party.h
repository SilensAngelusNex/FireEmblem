#pragma once
#include "PartyBase.h"

class Party: public PartyBase {
public:
	Party();
	Party(std::string name);
	Party(std::string name, std::vector<UnitData> unit_data);
	Party(PartyData data);

	Unit& getUnit(int index);
	std::vector<std::reference_wrapper<Unit>> getUnits();
	std::vector<std::reference_wrapper<Unit>> getOtherUnits(const Unit& unit);

	const Unit& getUnit(int index) const;
	const std::vector<std::reference_wrapper<Unit>> getUnits() const;
	const std::vector<std::reference_wrapper<Unit>> getOtherUnits(const Unit& unit) const;

	void startTurn(PartyBase& turn_party);
	void insertUnit(Unit& unit);
	bool isDone() const;

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this); }
	const_iterator cbegin() const { return const_iterator(*this, 0); }
	const_iterator cend() const { return const_iterator(*this); }
};

