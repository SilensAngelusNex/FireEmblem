#pragma once

template<typename T>
inline bool operator== (const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) {
	return lhs.get() == rhs.get();
}
template<typename T>
inline bool operator< (const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) {
	return &lhs.get() < &rhs.get();
}
template<typename T>
inline bool operator> (const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) {
	return &lhs.get() > &rhs.get();
}
template<typename T>
inline bool operator<= (const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) {
	return &lhs.get() <= &rhs.get();
}
template<typename T>
inline bool operator>= (const std::reference_wrapper<T>& lhs, const std::reference_wrapper<T>& rhs) {
	return &lhs.get() >= &rhs.get();
}