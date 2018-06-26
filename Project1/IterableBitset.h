#pragma once
#include <array>
#include <bitset>
#include <gsl/gsl_assert>
#include <string>
#include <vector>

#include "BitsetIterator.h"

template<size_t n>
inline std::string boolArrayToString(std::array<bool, n> init) {
	std::string result = std::string(n, '0');

	for (size_t i = 0; i < n; ++i) {
		if (init[i]) {
			result[n - (i + 1)] = '1';
		}
	}
	return result;
}

template<size_t n>
inline std::string vectorToString(std::vector<int> init) {
	Expects(std::find_if(init.begin(), init.end(), [](int i) {return 0 > i || i > static_cast<int>(n); }) == init.end());

	std::string result = std::string(n, '0');
	for (int i : init) {
		result[n - static_cast<size_t>(i + 1)] = '1';
	}
	return result;
}

template<size_t n>
inline std::string vectorToString(std::vector<size_t> init) {
	Expects(std::find_if(init.begin(), init.end(), [](size_t i) {return i > n; }) == init.end());

	std::string result = std::string(n, '0');
	for (int i : init) {
		result[n - (i + 1)] = '1';
	}
	return result;
}

template<size_t n>
class IterableBitset {
private:
	std::bitset<n> _values;

	constexpr IterableBitset(std::bitset<n> init) :
		_values(init)
	{}
public:
	constexpr IterableBitset() :
		_values()
	{}
	constexpr IterableBitset(size_t set_bit) : IterableBitset() {
		Expects(set_bit < n);
		_values[set_bit] = true;
	}
	IterableBitset(std::string init) {
		Expects(init.size() == n);
		_values = std::bitset<n>(init);
	}
	IterableBitset(std::array<bool, n> init) :
		IterableBitset(boolArrayToString<n>(init))
	{}
	IterableBitset(std::vector<int> init) :
		IterableBitset(vectorToString<n>(init))
	{}
	IterableBitset(std::vector<size_t> init) :
		IterableBitset(vectorToString<n>(init))
	{}

	constexpr const std::bitset<n> getBits() const {
		return _values;
	}

	using reference = typename std::bitset<n>::reference;
	
	constexpr reference operator[](size_t i) {
		return _values[i];
	}

	constexpr bool operator[](size_t i) const {
		return _values[i];
	}

	constexpr IterableBitset& operator&=(const IterableBitset& rhs) {
		_values &= rhs._values;
		return *this;
	}
	constexpr IterableBitset& operator|=(const IterableBitset& rhs) {
		_values |= rhs._values;
		return *this;
	}
	constexpr IterableBitset& operator^=(const IterableBitset& rhs) {
		_values ^= rhs._values;
		return *this;
	}

	constexpr IterableBitset operator&(IterableBitset rhs) const {
		rhs &= _values;
		return rhs;
	}
	constexpr IterableBitset operator|(IterableBitset rhs) const {
		rhs |= _values;
		return rhs;
	}
	constexpr IterableBitset operator^(IterableBitset rhs) const {
		rhs ^= _values;
		return rhs;
	}
	constexpr IterableBitset operator~() const {
		return IterableBitset(~_values);
	}

private:
	template<bool less, bool equal, bool greater>
	constexpr bool bitCompareHelp(const IterableBitset& rhs) const {
		for (int i = n - 1; i >= 0; --i) {
			bool l_bit = _values[i];
			bool r_bit = rhs._values[i];
			bool different = l_bit ^ r_bit;

			if (different) {
				if (r_bit) {
					return less;
				}
				return greater;
			}
		}
		return equal;
	}
public:
	constexpr bool operator==(const IterableBitset& rhs) const {
		return _values == rhs._values;
	}
	constexpr bool operator!=(const IterableBitset& rhs) const {
		return _values != rhs._values;
	}
	constexpr bool operator<(const IterableBitset& rhs) const {
		return this->bitCompareHelp<true, false, false>(rhs);
	}
	constexpr bool operator<=(const IterableBitset& rhs) const {
		return this->bitCompareHelp<true, true, false>(rhs);
	}
	constexpr bool operator>(const IterableBitset& rhs) const {
		return this->bitCompareHelp<false, false, true>(rhs);
	}
	constexpr bool operator>=(const IterableBitset& rhs) const {
		return this->bitCompareHelp<false, true, true>(rhs);
	}

	constexpr size_t size() const {
		return n;
	}

	using const_iterator = set_bits_iterator<n>;

	const_iterator begin() const {
		return const_iterator(this->_values, 0);
	}
	const_iterator end() const {
		return const_iterator(this->_values);
	}
	const_iterator cbegin() const {
		return const_iterator(this->_values, 0);
	}
	const_iterator cend() const {
		return const_iterator(this->_values);
	}
};
