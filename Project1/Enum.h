#pragma once
#include <gsl/gsl_assert>

#include <iostream>

template<typename E>
class Enum {
public:
	using values = E;

	constexpr static size_t positionOf(E value) {
		return static_cast<int>(value);
	}

	constexpr static size_t size = positionOf(E::ENUM_END);

private:
	using _array = std::array<E, size>;
public:
	constexpr static E valueOf(size_t i) {
		Expects(0 <= i && i < size);

		return static_cast<E>(i);
	}

private:
	inline static _array make_value_array() {
		_array result;
		for (size_t i = 0; i < size; i++) {
			result[i] = valueOf(i);
		}
		return result;
	}

public:
	inline static const _array list = make_value_array();
private:
	E _value;
public:
	constexpr Enum(E e) noexcept:
		_value(e)
	{}

	constexpr operator E() const noexcept {
		return _value;
	}

	constexpr size_t pos() const noexcept {
		return positionOf(_value);
	}
};
