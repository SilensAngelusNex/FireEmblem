#pragma once
#include "PartyBase.h"


class Party: public PartyBase {
public:
	Party();
	Party(std::string name);
	Party(std::string name, std::vector<UnitData> unit_data);
	Party(PartyData data);

	std::vector<UnitRef> getUnits();
	std::vector<UnitRef> getOtherUnits(const Unit & unit);

	std::vector<constUnitRef> getUnits() const;
	std::vector<constUnitRef> getOtherUnits(const Unit& unit) const;

	void startTurn(PartyBase& turn_party);
	void insertUnit(UnitPtr unit);
	void insertUnit(UnitData unit);

	UnitPtr dropUnit(Unit& unit);
	//UnitPtr dropUnit(const iterator& pos);


	bool isDone() const;

	iterator begin() { return _units.begin(); }
	iterator end() { return _units.end(); }
	const_iterator cbegin() const { return _units.cbegin(); }
	const_iterator cend() const { return _units.cend(); }
};

