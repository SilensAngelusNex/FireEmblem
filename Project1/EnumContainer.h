#pragma once

//TODO(Weston): Make this more generic so we can put strings and shit in it
template<typename EnumType>
class EnumContainer {
public:
	using array = std::array<int, EnumType::size>;
private:
	array _values{};
public:
	EnumContainer() = default;
	explicit EnumContainer(array init_values);

	EnumContainer& operator+=(const EnumContainer& rhs);
	EnumContainer& operator-=(const EnumContainer& rhs);

	bool operator==(const EnumContainer& rhs) const;
	bool operator!=(const EnumContainer& rhs) const;

	using iterator = std::_Array_iterator<int, EnumType::size> ;
	using const_iterator = std::_Array_const_iterator<int, EnumType::size>;
	iterator begin() {
		_values.begin();
	}
	const_iterator begin() const {
		_values.begin();
	}
	iterator end() {
		_values.end();
	}
	const_iterator end() const {
		_values.end();
	}

	int operator[](EnumType i) const;
	int& operator[](EnumType i);
};

template<typename EnumType>
EnumContainer<EnumType>::EnumContainer(array init_values) :
	_values(init_values)
{}

template<typename EnumType>
EnumContainer<EnumType>& EnumContainer<EnumType>::operator+=(const EnumContainer<EnumType>& rhs) {
	for (EnumType i : EnumType::list) {
		_values[i.pos()] += rhs._values[i.pos()];
	}
	return *this;
}
template<typename EnumType>
EnumContainer<EnumType>& EnumContainer<EnumType>::operator-=(const EnumContainer<EnumType>& rhs) {
	for (EnumType i : EnumType::list) {
		_values[i.pos()] -= rhs._values[i.pos()];
	}
	return *this;
}

template<typename EnumType>
bool EnumContainer<EnumType>::operator==(const EnumContainer<EnumType>& rhs) const {
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
template<typename EnumType>
bool EnumContainer<EnumType>::operator!=(const EnumContainer<EnumType>& rhs) const {
	return !this->operator==(rhs);
}


template<typename EnumType>
int EnumContainer<EnumType>::operator[](EnumType i) const {
	return _values[i.pos()];
}
template<typename EnumType>
int& EnumContainer<EnumType>::operator[](EnumType i) {
	return _values[i.pos()];
}

template<typename EnumType>
EnumContainer<EnumType> operator+(EnumContainer<EnumType> lhs, const EnumContainer<EnumType>& rhs) {
	return lhs += rhs;
}
template<typename EnumType>
EnumContainer<EnumType> operator-(EnumContainer<EnumType> lhs, const EnumContainer<EnumType>& rhs) {
	return lhs -= rhs;
}