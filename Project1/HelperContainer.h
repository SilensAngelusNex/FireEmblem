#pragma once

template<typename Helper>
class HelperContainer {
private:
	static Helper* _helper;
	static void setHelper(Helper& helper);
protected:
	Helper& getHelper();
	const Helper& getHelper() const;
	friend class Chapter;
};

template<typename Helper>
Helper* HelperContainer<Helper>::_helper;

template<typename Helper>
inline void HelperContainer<Helper>::setHelper(Helper& helper) {
	_helper = &helper;
}

template<typename Helper>
inline Helper& HelperContainer<Helper>::getHelper(){
	Expects(_helper != nullptr);
	return *_helper;
}

template<typename Helper>
inline const Helper& HelperContainer<Helper>::getHelper() const{
	Expects(_helper != nullptr);
	return *_helper;
}