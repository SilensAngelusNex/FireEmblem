#pragma once
#include <array>
#include <set>
#include "IterableBitset.h"
#include "EnumSetIterator.h"

template<typename T, typename EnumType>
class EnumContainer {
public:
	using array = std::array<T, EnumType::size>;
private:
	array _values{};
public:
	EnumContainer() = default;
	explicit EnumContainer(array init_values);

	constexpr EnumContainer& operator+=(const EnumContainer& rhs);
	constexpr EnumContainer& operator-=(const EnumContainer& rhs);
	constexpr EnumContainer operator+(EnumContainer rhs) const;
	constexpr EnumContainer operator-(EnumContainer rhs) const;

	using iterator = std::_Array_iterator<T, EnumType::size> ;
	using const_iterator = std::_Array_const_iterator<T, EnumType::size>;
	iterator begin() {
		return _values.begin();
	}
	const_iterator begin() const {
		return _values.begin();
	}
	const_iterator cbegin() const {
		return _values.begin();
	}

	iterator end() {
		return _values.end();
	}
	const_iterator end() const {
		return _values.end();
	}
	const_iterator cend() const {
		return _values.end();
	}

	constexpr T operator[](EnumType i) const;
	constexpr T& operator[](EnumType i);
private:
	template<bool less, bool equal, bool greater>
	constexpr bool lexCompare(const EnumContainer<T, EnumType>& rhs) const;
public:
	constexpr bool operator==(const EnumContainer& rhs) const;
	constexpr bool operator!=(const EnumContainer& rhs) const;
	constexpr bool operator<=(const EnumContainer& rhs) const;
	constexpr bool operator>=(const EnumContainer& rhs) const;
	constexpr bool operator<(const EnumContainer& rhs) const;
	constexpr bool operator>(const EnumContainer& rhs) const;

	constexpr bool contains(T t) const;
	constexpr int size() const;
};

template<typename T, typename EnumType>
EnumContainer<T, EnumType>::EnumContainer(array init_values) :
	_values(init_values)
{}

template<typename T, typename EnumType>
constexpr EnumContainer<T, EnumType>& EnumContainer<T, EnumType>::operator+=(const EnumContainer<T, EnumType>& rhs) {
	for (EnumType i : EnumType::list) {
		_values[i.pos()] += rhs._values[i.pos()];
	}
	return *this;
}
template<typename T, typename EnumType>
constexpr EnumContainer<T, EnumType>& EnumContainer<T, EnumType>::operator-=(const EnumContainer<T, EnumType>& rhs) {
	for (EnumType i : EnumType::list) {
		_values[i.pos()] -= rhs._values[i.pos()];
	}
	return *this;
}

template<typename T, typename EnumType>
constexpr EnumContainer<T, EnumType> EnumContainer<T, EnumType>::operator+(EnumContainer<T, EnumType> rhs) const {
	return rhs += *this;
}
template<typename T, typename EnumType>
constexpr EnumContainer<T, EnumType> EnumContainer<T, EnumType>::operator-(EnumContainer<T, EnumType> rhs) const {
	return rhs -= *this;
}

template<typename T, typename EnumType>
constexpr T EnumContainer<T, EnumType>::operator[](EnumType i) const {
	return _values[i.pos()];
}
template<typename T, typename EnumType>
constexpr T& EnumContainer<T, EnumType>::operator[](EnumType i) {
	return _values[i.pos()];
}

template<typename T, typename EnumType>
template<bool less, bool equal, bool greater>
constexpr bool EnumContainer<T, EnumType>::lexCompare(const EnumContainer<T, EnumType>& rhs) const {
	for (int i = EnumType::size - 1; i >= 0; --i) {
		const T& l_val = _values[i];
		const T& r_val = rhs._values[i];

		if (l_val < r_val) {
			return less;
		}
		if (r_val < l_val) {
			return greater;
		}
	}
	return equal;
}

template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::operator==(const EnumContainer<T, EnumType>& rhs) const {
	return this->lexCompare<false, true, false>(rhs);
}
template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::operator!=(const EnumContainer<T, EnumType>& rhs) const {
	return this->lexCompare<true, false, true>(rhs);
}
template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::operator<=(const EnumContainer<T, EnumType>& rhs) const {
	return this->lexCompare<true, true, false>(rhs);
}
template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::operator>=(const EnumContainer<T, EnumType>& rhs) const {
	return this->lexCompare<false, true, true>(rhs);
}
template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::operator<(const EnumContainer<T, EnumType>& rhs) const {
	return this->lexCompare<true, false, false>(rhs);
}
template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::operator>(const EnumContainer<T, EnumType>& rhs) const {
	return this->lexCompare<false, false, true>(rhs);
}

template<typename T, typename EnumType>
constexpr bool EnumContainer<T, EnumType>::contains(T t) const {
	return std::find(begin(), end(), t) != end();
}

template<typename T, typename EnumType>
constexpr int EnumContainer<T, EnumType>::size() const {
	return EnumType::size;
}



template<typename EnumType>
class EnumContainer<bool, EnumType> {
public:
	using array = std::array<bool, EnumType::size>;
private:
	using container = IterableBitset<EnumType::size>;
	container _values;
public:
	EnumContainer() = default;
	explicit EnumContainer(array init_values);
	explicit EnumContainer(EnumType set_type);
	EnumContainer(std::set<EnumType> set_types);

	constexpr EnumContainer& operator+=(const EnumContainer& rhs);
	constexpr EnumContainer& operator-=(const EnumContainer& rhs);
	constexpr EnumContainer& operator&=(const EnumContainer& rhs);
	constexpr EnumContainer& operator|=(const EnumContainer& rhs);
	constexpr EnumContainer& operator^=(const EnumContainer& rhs);

	constexpr EnumContainer operator+(EnumContainer rhs) const;
	constexpr EnumContainer operator-(EnumContainer rhs) const;
	constexpr EnumContainer operator&(EnumContainer rhs) const;
	constexpr EnumContainer operator|(EnumContainer rhs) const;
	constexpr EnumContainer operator^(EnumContainer rhs) const;
	constexpr EnumContainer operator~() const;

	using const_iterator = index_iterator<const container>;
	using iterator = index_iterator<container>;

	const bits_iterator_helper<EnumType> get_set_bits() const;

	iterator begin() {
		return iterator(_values, 0);
	}
	const_iterator begin() const {
		return const_iterator(_values, 0);
	}
	const_iterator cbegin() const {
		return const_iterator(_values, 0);
	}

	iterator end() {
		return iterator(_values);
	}
	const_iterator end() const {
		return const_iterator(_values);
	}
	const_iterator cend() const {
		return const_iterator(_values);
	}

	constexpr bool operator[](EnumType i) const;
	using reference = typename IterableBitset<EnumType::size>::reference;
	constexpr reference operator[](EnumType i);
private:
	template<bool less, bool equal, bool greater>
	constexpr bool lexCompare(const EnumContainer& rhs) const;
public:
	constexpr bool operator==(const EnumContainer& rhs) const;
	constexpr bool operator!=(const EnumContainer& rhs) const;
	constexpr bool operator<=(const EnumContainer& rhs) const;
	constexpr bool operator>=(const EnumContainer& rhs) const;
	constexpr bool operator<(const EnumContainer& rhs) const;
	constexpr bool operator>(const EnumContainer& rhs) const;

	constexpr bool contains(bool t) const;
	constexpr int size() const;
};


template<typename EnumType>
EnumContainer<bool, EnumType>::EnumContainer(array init_values) :
	_values(init_values)
{}

template<typename EnumType>
inline EnumContainer<bool, EnumType>::EnumContainer(EnumType set_type) :
	_values()
{
	(*this)[set_type] = true;
}

template<typename EnumType>
inline EnumContainer<bool, EnumType>::EnumContainer(std::set<EnumType> set_types) :
	_values()
{
	for (EnumType t : set_types) {
		(*this)[t] = true;
	}
}

template<typename EnumType>
constexpr EnumContainer<bool, EnumType>& EnumContainer<bool, EnumType>::operator+=(const EnumContainer<bool, EnumType>& rhs) {
	this->_values |= rhs._values;
	return *this;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType>& EnumContainer<bool, EnumType>::operator-=(const EnumContainer<bool, EnumType>& rhs) {
	this->_values &= ~rhs._values;
	return *this;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType>& EnumContainer<bool, EnumType>::operator&=(const EnumContainer<bool, EnumType>& rhs) {
	this->_values &= rhs._values;
	return *this;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType>& EnumContainer<bool, EnumType>::operator|=(const EnumContainer<bool, EnumType>& rhs) {
	this->_values |= rhs._values;
	return *this;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType>& EnumContainer<bool, EnumType>::operator^=(const EnumContainer<bool, EnumType>& rhs) {
	this->_values ^= rhs._values;
	return *this;
}

template<typename EnumType>
constexpr EnumContainer<bool, EnumType> EnumContainer<bool, EnumType>::operator+(EnumContainer<bool, EnumType> rhs) const {
	rhs += *this;
	return rhs;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType> EnumContainer<bool, EnumType>::operator-(EnumContainer<bool, EnumType> rhs) const {
	rhs -= *this;
	return rhs;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType> EnumContainer<bool, EnumType>::operator&(EnumContainer<bool, EnumType> rhs) const {
	rhs &= *this;
	return rhs;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType> EnumContainer<bool, EnumType>::operator|(EnumContainer<bool, EnumType> rhs) const {
	rhs |= *this;
	return rhs;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType> EnumContainer<bool, EnumType>::operator^(EnumContainer<bool, EnumType> rhs) const {
	rhs ^= *this;
	return rhs;
}
template<typename EnumType>
constexpr EnumContainer<bool, EnumType> EnumContainer<bool, EnumType>::operator~() const {
	EnumContainer<bool, EnumType> result;
	result._values = ~this->_values;
	return result;
}

template<typename EnumType>
inline const bits_iterator_helper<EnumType> EnumContainer<bool, EnumType>::get_set_bits() const {
	return bits_iterator_helper<EnumType>(_values);
}

template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator[](EnumType i) const {
	return _values[i.pos()];
}
template<typename EnumType>
constexpr typename EnumContainer<bool, EnumType>::reference EnumContainer<bool, EnumType>::operator[](EnumType i) {
	return _values[i.pos()];
}

template<typename EnumType>
template<bool less, bool equal, bool greater>
constexpr bool EnumContainer<bool, EnumType>::lexCompare(const EnumContainer<bool, EnumType>& rhs) const {
	for (int i = EnumType::size - 1; i >= 0; --i) {
		bool l_val = _values[i];
		bool r_val = rhs._values[i];
		bool different = l_val ^ r_val;
	
		if (different) {
			if (r_val) {
				return less;
			}
			if (l_val) {
				return greater;
			}
		}
	}
	return equal;
}

template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator==(const EnumContainer<bool, EnumType>& rhs) const {
	return this->lexCompare<false, true, false>(rhs);
}
template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator!=(const EnumContainer<bool, EnumType>& rhs) const {
	return this->lexCompare<true, false, true>(rhs);
}
template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator<=(const EnumContainer<bool, EnumType>& rhs) const {
	return this->lexCompare<true, true, false>(rhs);
}
template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator>=(const EnumContainer<bool, EnumType>& rhs) const {
	return this->lexCompare<false, true, true>(rhs);
}
template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator<(const EnumContainer<bool, EnumType>& rhs) const {
	return this->lexCompare<true, false, false>(rhs);
}
template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::operator>(const EnumContainer<bool, EnumType>& rhs) const {
	return this->lexCompare<false, false, true>(rhs);
}

template<typename EnumType>
constexpr bool EnumContainer<bool, EnumType>::contains(bool t) const {
	return std::find(begin(), end(), t) != end();
}

template<typename EnumType>
constexpr int EnumContainer<bool, EnumType>::size() const {
	return EnumType::size;
}