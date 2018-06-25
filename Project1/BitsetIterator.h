#pragma once
#include <bitset>
#include <gsl/gsl_assert>

template<int size>
class set_bits_iterator {
private:
	const std::bitset<size>& _bits;
	int _index;
public:
	set_bits_iterator(const std::bitset<size>& b) : _bits(b), _index(size)
	{}

	set_bits_iterator(const std::bitset<size>& b, int i) : _bits(b), _index(i) {
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
		} while (index > 0 && !_bits[_index]);
		return *this;
	}
	set_bits_iterator operator--(int) {
		set_bits_iterator result(*this);
		--(*this);
		return result;
	}

	int operator*() const {
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
class static_size_index_iterator {
private:
	T& _container;
	int _index;
public:
	static_size_index_iterator(T& container) :
		_container(container),
		_index(_container.size())
	{}

	static_size_index_iterator(T& container, int i) :
		_container(container),
		_index(i)
	{
		Expects(i <= _container.size());
	}

	static_size_index_iterator(const static_size_index_iterator& rhs) :
		_container(rhs._container),
		_index(rhs._index)
	{}

	static_size_index_iterator(static_size_index_iterator&& rhs) :
		_container(rhs._container),
		_index(rhs._index)
	{}

	static_size_index_iterator& operator++() {
		Expects(_index < _container.size());
		++_index;
		return *this;
	}
	static_size_index_iterator operator++(int) {
		static_size_index_iterator result(*this);
		++(*this);
		return result;
	}
	static_size_index_iterator& operator--() {
		Expects(_index > 0);
		++_index;
		return *this;
	}
	static_size_index_iterator operator--(int) {
		static_size_index_iterator result(*this);
		--(*this);
		return result;
	}

	auto operator*() {
		return _container[_index];
	}

	auto operator*() const {
		return _container[_index];
	}

	bool operator==(const static_size_index_iterator& rhs) const {
		bool b = &_container == &rhs._container;
		bool i = _index == rhs._index;
		return  b && i;
	}
	bool operator!=(const static_size_index_iterator& rhs) const {
		bool b = &_container != &rhs._container;
		bool i = _index != rhs._index;
		return  b || i;
	}

	friend void swap(static_size_index_iterator& lhs, static_size_index_iterator& rhs) {
		Expects(&lhs._container == &rhs._container);
		swap(lhs._index, rhs._index);
	}
};
//
//template<int size>
//class const_bits_iterator {
//protected:
//	const std::bitset<size>& _bits;
//	int _index;
//public:
//	const_bits_iterator(const std::bitset<size>& b) :
//		_bits(b),
//		_index(size)
//	{}
//
//	const_bits_iterator(const std::bitset<size>& b, int i) :
//		_bits(b),
//		_index(i)
//	{}
//
//	const_bits_iterator(const const_bits_iterator& rhs) :
//		_bits(rhs._bits),
//		_index(rhs._index)
//	{}
//
//	const_bits_iterator(const_bits_iterator&& rhs) :
//		_bits(rhs._bits),
//		_index(rhs._index)
//	{}
//
//	const_bits_iterator& operator++() {
//		Expects(_index < size);
//		++_index;
//		return *this;
//	}
//	const_bits_iterator operator++(int) {
//		set_bits_iterator result(*this);
//		++(*this);
//		return result;
//	}
//	const_bits_iterator& operator--() {
//		Expects(_index > 0);
//		++_index;
//		return *this;
//	}
//	const_bits_iterator operator--(int) {
//		const_bits_iterator result(*this);
//		--(*this);
//		return result;
//	}
//
//	bool operator*() const {
//		return _bits[_index];
//	}
//
//	bool operator==(const const_bits_iterator& rhs) const {
//		bool b = &_bits == &rhs._bits;
//		bool i = _index == rhs._index;
//		return  b && i;
//	}
//	bool operator!=(const const_bits_iterator& rhs) const {
//		bool b = &_bits != &rhs._bits;
//		bool i = _index != rhs._index;
//		return  b || i;
//	}
//
//	friend void swap(const_bits_iterator& lhs, const_bits_iterator& rhs) {
//		Expects(&lhs._bits == &rhs._bits);
//		swap(lhs._index, rhs._index);
//	}
//};
//
//template<int size>
//class bits_iterator : public const_bits_iterator<size> {
//public:
//	typename std::bitset<size>::reference operator*() {
//		return _bits[_index];
//	}
//};