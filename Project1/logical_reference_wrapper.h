#pragma once
#include <functional>
template<typename T>
class logical_reference_wrapper : public std::reference_wrapper<T> {
public:
	using std::reference_wrapper<T>::reference_wrapper;
	using std::reference_wrapper<T>::get;
	using std::reference_wrapper<T>::operator=;
	using std::reference_wrapper<T>::operator();

	bool operator== (const std::reference_wrapper<T>& rhs) const {
		return get() == rhs.get();
	}
	bool operator!= (const std::reference_wrapper<T>& rhs) const {
		return get() != rhs.get();
	}
	bool operator> (const std::reference_wrapper<T>& rhs) const {
		return get() > rhs.get();
	}
	bool operator< (const std::reference_wrapper<T>& rhs) const {
		return get() < rhs.get();
	}
	bool operator>= (const std::reference_wrapper<T>& rhs) const {
		return get() >= rhs.get();
	}
	bool operator<= (const std::reference_wrapper<T>& rhs) const {
		return get() <= rhs.get();
	}
	bool operator== (const T& rhs) const {
		return get() == rhs;
	}
	bool operator!= (const T& rhs) const {
		return get() != rhs;
	}
	bool operator< (const T& rhs) const {
		return get() < rhs;
	}
	bool operator> (const T& rhs) const {
		return get() > rhs;
	}
	bool operator<= (const T& rhs) const {
		return get() <= rhs;
	}
	bool operator>= (const T& rhs) const {
		return get() >= rhs;
	}

};