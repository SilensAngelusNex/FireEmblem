#pragma once
#include <string>
//TODO: TURN INTO SOME KIND OF ENUM? NOT SURE
class Terrain
{
private:
	std::string _name;
public:
	Terrain();
	~Terrain();
	std::string getName()
	{
		return _name;
	};
};

