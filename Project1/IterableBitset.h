#pragma once
#include <array>
#include <bitset>
#include <gsl/gsl_assert>
#include <string>

template<int size>
std::string boolArrayToString(std::array<bool, size> init) {
	std::string result = std::string(size, '0');

	for (int i = 0; i < size; ++i) {
		if (init[i]) {
			result[size - (i + 1)] = '1';
		}
	}
	return result;
}

template<int size>
std::string vectorToString(std::vector<int> init) {
	Expects(std::find_if(init.begin(), init.end(), [](int i) {return i > size; }) == init.end());

	std::string result = std::string(size, '0');
	for (int i : init) {
		result[size - (i + 1)] = '1';
	}
	return result;
}

template<int size>
class IterableBitset {
private:
	std::bitset<size> _values;
public:
	IterableBitset(std::string init) {
		Expects(init.size() == size);
		_values = std::bitset<size>(init);
	}
	IterableBitset(std::array<bool, size> init) :
		IterableBitset(boolArrayToString(init))
	{}
	IterableBitset(std::vector<int> init) :
		IterableBitset(vectorToString<size>(init))
	{}

	const std::bitset<size> getBits() {
		return _values;
	}
private:
	class iterator {
	private:
		IterableBitset& _b;
		int _index;
	public:
		iterator(IterableBitset& b) : _b(b), _index(size)
		{}

		iterator(IterableBitset& b, int i) : _b(b), _index(i) {
			while (_index < size && !_b._values[_index]) {
				++_index;
			}
		}

		iterator& operator++() {
			do {
				++_index;
			} while (_index < size && !_b._values[_index]);
			return *this;
		}
		iterator operator++(int) {
			iterator result = { _index };
			++(*this);
			return result;
		}
		iterator& operator--() {
			do {
				--_index;
			} while (!_b._values[_index] && index > 0);
			return *this;
		}
		iterator operator--(int) {
			iterator result(*this);
			--(*this);
			return result;
		}

		int operator*() const {
			return _index;
		}

		bool operator==(const iterator& rhs) const {
			bool b = &_b == &rhs._b;
			bool i = _index == rhs._index;
			return  b && i;
		}
		bool operator!=(const iterator& rhs) const {
			bool b = &_b != &rhs._b;
			bool i = _index != rhs._index;
			return  b || i;
		}

		friend void swap(iterator& lhs, iterator& rhs) {
			swap(lhs._index, rhs._index);
		}

	};
public:
	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this);
	}
};
