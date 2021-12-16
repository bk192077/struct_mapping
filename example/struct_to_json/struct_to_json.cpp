#include "struct_mapping/struct_mapping.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct OceanPart
{
	std::string name;
	double average_depth;
	std::vector<int> temperature;
};

struct OceanColor
{
	std::string name;
};

struct Ocean
{
	double water_volume;
	long long surface_area;
	bool liquid;
	std::string name;

	OceanColor color;

	std::vector<OceanPart> parts;
};

struct Planet
{
	bool giant;
	long long surface_area;
	double mass;
	double volume;
	long long orbital_period;
	std::string name;
	bool terrestrial;
	std::string shape;

	Ocean ocean;
};

int main()
{
	struct_mapping::reg(&OceanPart::name, "name");
	struct_mapping::reg(&OceanPart::average_depth, "average_depth");
	struct_mapping::reg(&OceanPart::temperature, "temperature");

	struct_mapping::reg(&OceanColor::name, "name");
	
	struct_mapping::reg(&Ocean::water_volume, "water_volume");
	struct_mapping::reg(&Ocean::surface_area, "surface_area");
	struct_mapping::reg(&Ocean::liquid, "liquid");
	struct_mapping::reg(&Ocean::name, "name");
	struct_mapping::reg(&Ocean::color, "color");
	struct_mapping::reg(&Ocean::parts, "parts");

	struct_mapping::reg(&Planet::giant, "giant");
	struct_mapping::reg(&Planet::surface_area, "surface_area");
	struct_mapping::reg(&Planet::mass, "mass");
	struct_mapping::reg(&Planet::volume, "volume");
	struct_mapping::reg(&Planet::orbital_period, "orbital_period");
	struct_mapping::reg(&Planet::name, "name");
	struct_mapping::reg(&Planet::terrestrial, "terrestrial");
	struct_mapping::reg(&Planet::shape, "shape");
	struct_mapping::reg(&Planet::ocean, "ocean");

	Planet earth;

	earth.giant = false;
	earth.terrestrial = true;
	earth.surface_area = 510072000;
	earth.orbital_period = 365 * 24 * 3600;
	earth.mass = 5.97237e24;
	earth.name = "Terra";
	earth.volume = 1.08321e12;
	earth.shape = "nearly spherical";

	earth.ocean.water_volume = 1332000000;
	earth.ocean.surface_area = 361132000;
	earth.ocean.liquid = true;
	earth.ocean.name = "World Ocean";
	earth.ocean.color.name = "blue";

	OceanPart pacific;
	pacific.name = "Pacific Ocean";
	pacific.average_depth = 4.280111;
	pacific.temperature = std::vector<int>{-3, 5, 12};

	OceanPart atlantic;
	atlantic.name = "Atlantic Ocean";
	atlantic.average_depth = 3.646;
	atlantic.temperature = std::vector<int>{-3, 0};

	earth.ocean.parts.push_back(pacific);
	earth.ocean.parts.push_back(atlantic);

	std::ostringstream json_data;
	struct_mapping::map_struct_to_json(earth, json_data, "  ");

	std::cout << json_data.str() << std::endl;
}
