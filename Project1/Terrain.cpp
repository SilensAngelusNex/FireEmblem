#include "Terrain.h"
Terrain::Terrain() :
	_name("~NULL~"), 
	_costs(MobilityList<std::optional<int>>({10, 10,10}))
{}
Terrain::~Terrain() = default;
