#pragma once
#include "PartyBase.h"


class Party: public PartyBase {
public:
	Party();
	Party(std::string name);
	Party(std::string name, std::vector<UnitData> unit_data);
	Party(PartyData data);

	std::vector<Unit::Ref> getUnits();
	std::vector<Unit::Ref> getOtherUnits(const Unit & unit);

	std::vector<Unit::ConstRef> getUnits() const;
	std::vector<Unit::ConstRef> getOtherUnits(const Unit& unit) const;

	void startTurn(PartyBase& turn_party);
	void insertUnit(Unit::UniquePtr unit);
	void insertUnit(UnitData unit);

	Unit::UniquePtr dropUnit(Unit& unit);
	//Unit::UniquePtr dropUnit(const iterator& pos);


	bool isDone() const;

	iterator begin() { return _units.begin(); }
	iterator end() { return _units.end(); }
	const_iterator cbegin() const { return _units.cbegin(); }
	const_iterator cend() const { return _units.cend(); }
};

