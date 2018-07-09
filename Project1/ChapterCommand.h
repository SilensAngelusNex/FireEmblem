#pragma once
class Chapter;

template<typename Base>
class ChapterCommand : private Base {
public:
	ChapterCommand(Base&& base);
	void execute(); 
};

template<typename Base>
inline ChapterCommand<Base>::ChapterCommand(Base&& base) :
	Base(base)
{}

template<typename Base>
void ChapterCommand<typename Base>::execute() {
	if (Base::isValid()) {
		Base::doExecute();
	}
	else {
		std::cout << "Command invalid" << std::endl;
	}
}