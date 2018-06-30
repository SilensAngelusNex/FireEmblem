#pragma once
/*
template<typename T>
void vectorSubtract(std::vector<std::reference_wrapper<T>>& a, std::vector<std::reference_wrapper<T>>& b) {
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	std::vector<std::reference_wrapper<T>> c = std::vector<std::reference_wrapper<T>>();
	std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(c, c.begin()));
	a = c;
};
*/