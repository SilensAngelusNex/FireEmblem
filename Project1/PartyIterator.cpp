#include "PartyIterator.h"
#include "PartyBase.h"

party_iterator::party_iterator(PartyBase& party) : _party(party), _index(_party._units.size())
{}

party_iterator::party_iterator(PartyBase& party, int i) : _party(party), _index(i)
{}

party_iterator::party_iterator(const party_iterator& rhs) :
	_party(rhs._party),
	_index(rhs._index)
{}

party_iterator::party_iterator(party_iterator&& rhs) :
	_party(rhs._party),
	_index(rhs._index)
{}

party_iterator& party_iterator::operator++() {
	Expects(_index < _party._units.size());
	++_index;
	return *this;

}
party_iterator party_iterator::operator++(int) {
	party_iterator result(*this);
	++(*this);
	return result;
}
party_iterator & party_iterator::operator--() {
	Expects(_index > 0);
	--_index;
	return *this;

}
party_iterator party_iterator::operator--(int) {
	party_iterator result(*this);
	--(*this);
	return result;

}

Unit& party_iterator::operator*() const {
	return *_party._units[_index];

}

bool party_iterator::operator==(const party_iterator& rhs) const {
	bool b = _party == rhs._party;
	bool i = _index == rhs._index;
	return  b && i;

}
bool party_iterator::operator!=(const party_iterator& rhs) const {
	bool b = _party != rhs._party;
	bool i = _index != rhs._index;
	return  b || i;

}

const_party_iterator::const_party_iterator(const PartyBase& party) : _party(party), _index(_party._units.size())
{}

const_party_iterator::const_party_iterator(const PartyBase& party, int i) : _party(party), _index(i)
{}

const_party_iterator::const_party_iterator(const const_party_iterator& rhs) :
	_party(rhs._party),
	_index(rhs._index)
{}

const_party_iterator::const_party_iterator(const_party_iterator&& rhs) :
	_party(rhs._party),
	_index(rhs._index)
{}

const_party_iterator& const_party_iterator::operator++() {
	Expects(_index < _party._units.size());
	++_index;
	return *this;

}
const_party_iterator const_party_iterator::operator++(int) {
	const_party_iterator result(*this);
	++(*this);
	return result;
}
const_party_iterator & const_party_iterator::operator--() {
	Expects(_index > 0);
	--_index;
	return *this;

}
const_party_iterator const_party_iterator::operator--(int) {
	const_party_iterator result(*this);
	--(*this);
	return result;

}

const Unit& const_party_iterator::operator*() const {
	return *_party._units[_index];

}

bool const_party_iterator::operator==(const const_party_iterator& rhs) const {
	bool b = _party == rhs._party;
	bool i = _index == rhs._index;
	return  b && i;

}
bool const_party_iterator::operator!=(const const_party_iterator& rhs) const {
	bool b = _party != rhs._party;
	bool i = _index != rhs._index;
	return  b || i;

}
