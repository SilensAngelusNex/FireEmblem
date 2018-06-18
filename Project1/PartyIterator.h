#pragma once
#include <gsl/gsl_assert>

class PartyBase;
class Unit;
class party_iterator {
private:
	PartyBase& _party;
	size_t _index;
public:
	party_iterator(PartyBase& party);	
	party_iterator(PartyBase& party, int i);	
	party_iterator(const party_iterator& rhs);	
	party_iterator(party_iterator&& rhs);
		
	party_iterator & operator++();
	party_iterator operator++(int);
	party_iterator & operator--();
	party_iterator operator--(int);	
	Unit& operator*() const;
	
	bool operator==(const party_iterator& rhs) const;
	bool operator!=(const party_iterator& rhs) const;
};
class const_party_iterator {
private:
	const PartyBase & _party;
	size_t _index;
public:
	const_party_iterator(const PartyBase& const_party);
	const_party_iterator(const PartyBase& const_party, int i);
	const_party_iterator(const const_party_iterator& rhs);
	const_party_iterator(const_party_iterator&& rhs);

	const_party_iterator & operator++();
	const_party_iterator operator++(int);
	const_party_iterator & operator--();
	const_party_iterator operator--(int);
	const Unit& operator*() const;

	bool operator==(const const_party_iterator& rhs) const;
	bool operator!=(const const_party_iterator& rhs) const;
};

