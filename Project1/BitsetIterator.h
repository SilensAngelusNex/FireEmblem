#pragma once
#include <bitset>
#include <gsl/gsl_assert>

template<size_t size>
class set_bits_iterator {
private:
	const std::bitset<size>& _bits;
	size_t _index;
public:
	set_bits_iterator(const std::bitset<size>& b) : _bits(b), _index(size)
	{}

	set_bits_iterator(const std::bitset<size>& b, size_t i) : _bits(b), _index(i) {
		while (_index < size && !_bits[_index]) {
			++_index;
		}
	}

	set_bits_iterator(const set_bits_iterator& rhs) :
		_bits(rhs._bits),
		_index(rhs._index)
	{}

	set_bits_iterator(set_bits_iterator&& rhs) :
		_bits(rhs._bits),
		_index(rhs._index)
	{}



	set_bits_iterator& operator++() {
		Expects(_index < size);
		do {
			++_index;
		} while (_index < size && !_bits[_index]);
		return *this;
	}
	set_bits_iterator operator++(int) {
		set_bits_iterator result(*this);
		++(*this);
		return result;
	}
	set_bits_iterator& operator--() {
		Expects(_index > 0); // And greater than first set bit
		do {
			--_index;
		} while (_index > 0 && !_bits[_index]);
		return *this;
	}
	set_bits_iterator operator--(int) {
		set_bits_iterator result(*this);
		--(*this);
		return result;
	}

	size_t operator*() const {
		return _index;
	}

	bool operator==(const set_bits_iterator& rhs) const {
		bool b = &_bits == &rhs._bits;
		bool i = _index == rhs._index;
		return  b && i;
	}
	bool operator!=(const set_bits_iterator& rhs) const {
		bool b = &_bits != &rhs._bits;
		bool i = _index != rhs._index;
		return  b || i;
	}


	friend void swap(set_bits_iterator& lhs, set_bits_iterator& rhs) {
		Expects(&lhs._bits == &rhs._bits);
		swap(lhs._index, rhs._index);
	}
};

template<typename T>
class index_iterator {
private:
	T& _container;
	size_t _index;
public:
	index_iterator(T& container) :
		_container(container),
		_index(_container.size())
	{}

	index_iterator(T& container, size_t i) :
		_container(container),
		_index(i)
	{
		Expects(i <= _container.size());
	}

	index_iterator(const index_iterator& rhs) :
		_container(rhs._container),
		_index(rhs._index)
	{}

	index_iterator(index_iterator&& rhs) :
		_container(rhs._container),
		_index(rhs._index)
	{}

	index_iterator& operator++() {
		Expects(_index < _container.size());
		++_index;
		return *this;
	}
	index_iterator operator++(int) {
		index_iterator result(*this);
		++(*this);
		return result;
	}
	index_iterator& operator--() {
		Expects(_index > 0);
		++_index;
		return *this;
	}
	index_iterator operator--(int) {
		index_iterator result(*this);
		--(*this);
		return result;
	}

	decltype(auto) operator*() const {
		return _container[_index];
	}

	bool operator==(const index_iterator& rhs) const {
		bool b = &_container == &rhs._container;
		bool i = _index == rhs._index;
		return  b && i;
	}
	bool operator!=(const index_iterator& rhs) const {
		bool b = &_container != &rhs._container;
		bool i = _index != rhs._index;
		return  b || i;
	}

	friend void swap(index_iterator& lhs, index_iterator& rhs) {
		Expects(&lhs._container == &rhs._container);
		swap(lhs._index, rhs._index);
	}
};
