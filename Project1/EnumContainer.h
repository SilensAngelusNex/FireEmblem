#pragma once
#include <array>

template<typename T, typename EnumType>
class EnumContainer {
public:
	using array = std::array<T, EnumType::size>;
private:
	array _values{};
public:
	EnumContainer() = default;
	explicit EnumContainer(array init_values);

	EnumContainer& operator+=(const EnumContainer& rhs);
	EnumContainer& operator-=(const EnumContainer& rhs);

	bool operator==(const EnumContainer& rhs) const;
	bool operator!=(const EnumContainer& rhs) const;

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

	T operator[](EnumType i) const;
	T& operator[](EnumType i);
};

template<typename T, typename EnumType>
EnumContainer<T, EnumType>::EnumContainer(array init_values) :
	_values(init_values)
{}

template<typename T, typename EnumType>
EnumContainer<T, EnumType>& EnumContainer<T, EnumType>::operator+=(const EnumContainer<T, EnumType>& rhs) {
	for (EnumType i : EnumType::list) {
		_values[i.pos()] += rhs._values[i.pos()];
	}
	return *this;
}
template<typename T, typename EnumType>
EnumContainer<T, EnumType>& EnumContainer<T, EnumType>::operator-=(const EnumContainer<T, EnumType>& rhs) {
	for (EnumType i : EnumType::list) {
		_values[i.pos()] -= rhs._values[i.pos()];
	}
	return *this;
}

template<typename T, typename EnumType>
bool EnumContainer<T, EnumType>::operator==(const EnumContainer<T, EnumType>& rhs) const {
	if (this == &rhs) {
		return true;
	}
	for (EnumType i : EnumType::list) {
		if (_values[i.pos()] != rhs._values[i.pos()]) {
			return false;
		}
	}
	return true;
}
template<typename T, typename EnumType>
bool EnumContainer<T, EnumType>::operator!=(const EnumContainer<T, EnumType>& rhs) const {
	return !this->operator==(rhs);
}


template<typename T, typename EnumType>
T EnumContainer<T, EnumType>::operator[](EnumType i) const {
	return _values[i.pos()];
}
template<typename T, typename EnumType>
T& EnumContainer<T, EnumType>::operator[](EnumType i) {
	return _values[i.pos()];
}

template<typename T, typename EnumType>
EnumContainer<T, EnumType> operator+(EnumContainer<T, EnumType> lhs, const EnumContainer<T, EnumType>& rhs) {
	return lhs += rhs;
}
template<typename T, typename EnumType>
EnumContainer<T, EnumType> operator-(EnumContainer<T, EnumType> lhs, const EnumContainer<T, EnumType>& rhs) {
	return lhs -= rhs;
}