#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "struct_mapping/struct_mapping.h"

BEGIN_STRUCT(Planet)

MEMBER(bool, giant)
MEMBER(long long, surface_area)
MEMBER_OPTIONS(
	double,
	mass,
	struct_mapping::Bounds{1.0e23, 1.0e27},
	struct_mapping::Default{1.0e25})
MEMBER(std::vector<std::string>, satellites)

END_STRUCT

int main()
{
	std::istringstream json_data(R"json(
	{
		"giant": false,
		"surface_area": 510072000000000,
		"satellites": ["Moon", "R24"]
	}
	)json");

	Planet earth;

	struct_mapping::map_json_to_struct(earth, json_data);

	std::cout
		<< "earth" << std::endl
		<< " giant        : " << std::boolalpha << earth.giant << std::endl
		<< " surface_area : " << earth.surface_area << std::endl
		<< " mass         : " << earth.mass << std::endl
		<< " satellite    : [ ";

	for (const auto& s : earth.satellites)
	{
		std::cout << s << ", ";
	}

	std::cout << "]" << std::endl;
}
