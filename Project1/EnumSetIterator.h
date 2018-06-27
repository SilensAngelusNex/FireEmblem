#pragma once
#include "BitsetIterator.h"
#include "IterableBitset.h"

template<typename EnumType>
class enum_set_iterator : public set_bits_iterator<EnumType::size> {
public:
	enum_set_iterator(const set_bits_iterator<EnumType::size>& iter) :
		set_bits_iterator<EnumType::size>(iter)
	{}

	EnumType operator*() const {
		return EnumType::valueOf(set_bits_iterator<EnumType::size>::operator*());
	}
};

template<typename EnumType>
class bits_iterator_helper {
private:
	const IterableBitset<EnumType::size>& _values;
public:
	bits_iterator_helper(const IterableBitset<EnumType::size>& bits) :
		_values(bits)
	{}

	using const_iterator = enum_set_iterator<EnumType>;
	const_iterator begin() const {
		return const_iterator(_values.begin());
	}
	const_iterator cbegin() const {
		return const_iterator(_values.cbegin());
	}

	const_iterator end() const {
		return const_iterator(_values.end());
	}
	const_iterator cend() const {
		return const_iterator(_values.cend());
	}

	operator std::vector<EnumType>() const {
		std::vector<EnumType> result;
		for (EnumType t : *this) {
			result.push_back(t);
		}
		return result;
	}
};