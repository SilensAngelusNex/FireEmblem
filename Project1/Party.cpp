#include "Party.h"

#include <utility>



Party::Party() : 
	Party("~NULL PARTY~")
{}

Party::Party(std::string name) : 
	Party(name, std::vector<UnitData>())
{}

Party::Party(std::string name, std::vector<UnitData> unit_data) :
	_party_name(std::move(name))
{
	for (UnitData data : unit_data) {
		_units.emplace_back(unit_data);
	}
}

Party::Party(PartyData data) :
	Party(data.name, data.unit_data)
{}

void Party::startTurn() {
	for (Unit& unit : _units) {
		//unit.refresh(); Maybe this should be accomplished with listeners
	}
}
/*Use this function to determine when to change turns
*/
bool Party::isDone() {
	bool isDone = false;
	for (Unit& a : _units) {
	//	isDone = isDone || unit.isDone() || unit.isDead();
	}
	return isDone;
}

bool Party::hasUnit(Unit * unit) {
	return std::count(_units.begin(), _units.end(), unit);
}

void Party::insertUnit(Unit& unit) {
	_units.push_back(unit);
}
