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

	iterator begin() { return _units.begin(); }
	iterator end() { return _units.end(); }
	const_iterator cbegin() const { return _units.cbegin(); }
	const_iterator cend() const { return _units.cend(); }
};

