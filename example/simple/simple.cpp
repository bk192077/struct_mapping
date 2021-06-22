#include <iostream>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

struct Planet
{
	bool giant;
	long long surface_area;
	double mass;
	std::string satellite;
};

int main()
{
	struct_mapping::reg(&Planet::giant, "giant");
	struct_mapping::reg(&Planet::surface_area, "surface_area");
	struct_mapping::reg(&Planet::mass, "mass");
	struct_mapping::reg(&Planet::satellite, "satellite");

	Planet earth;

	std::istringstream json_data(R"json(
	{
		"giant": false,
		"surface_area": 510072000000000,
		"mass": 5.97237e24,
		"satellite": "Moon"
	}
	)json");

	struct_mapping::map_json_to_struct(earth, json_data);

	std::cout
		<< "earth" << std::endl
		<< " giant        : " << std::boolalpha << earth.giant << std::endl
		<< " surface_area : " << earth.surface_area << std::endl
		<< " mass         : " << earth.mass << std::endl
		<< " satellite    : " << earth.satellite << std::endl;
}
