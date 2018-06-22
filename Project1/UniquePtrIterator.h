#pragma once
#include <gsl/gsl_assert>

template<typename iterator, typename T>
class unique_ptr_iter : public iterator {
public:
	unique_ptr_iter(iterator&& parent) :
		iterator(std::move(parent))
	{}

	T& operator*() const {
		Expects(iterator::operator*() != nullptr);
		return *iterator::operator*();
	}
};

template<typename iterator, typename T>
class const_unique_ptr_iter : public iterator {
public:
	const_unique_ptr_iter(iterator&& parent) :
		iterator(std::move(parent))
	{}

	const T& operator*() const {
		Expects(iterator::operator*() != nullptr);
		return *iterator::operator*();
	}
};
