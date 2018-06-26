#pragma once
#include <gsl/gsl_assert>

template<typename iterator>
class unique_ptr_iter : public iterator {
public:
	unique_ptr_iter(iterator&& parent) :
		iterator(std::move(parent))
	{}

	auto& operator*() const {
		Expects(iterator::operator*() != nullptr);
		return *iterator::operator*();
	}
};

template<typename iterator>
class const_unique_ptr_iter : public iterator {
public:
	const_unique_ptr_iter(iterator&& parent) :
		iterator(std::move(parent))
	{}

	const auto& operator*() const {
		Expects(iterator::operator*() != nullptr);
		return *iterator::operator*();
	}
};