#include "Terrain.h"
Terrain::Terrain() :
	_name("~NULL TERRAIN~"), 
	_costs(MobilityList<std::optional<int>>({10, 10,10, 1, 1}))
{}
