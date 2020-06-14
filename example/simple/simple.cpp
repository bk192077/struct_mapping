#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(Planet)

MANAGED_FIELD(bool, giant)
MANAGED_FIELD(long long, surface_area)
MANAGED_FIELD(double, mass)
MANAGED_FIELD(std::string, satellite)

END_MANAGED_STRUCT

int main() {
	Planet earth;

	std::istringstream json_data(R"json(
	{
		"giant": false,
		"surface_area": 510072000000000,
		"mass": 5.97237e24,
		"satellite": "Moon"
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(earth, json_data);

	std::cout << "earth" << std::endl;
	std::cout << " giant        : " << std::boolalpha << earth.giant << std::endl;
	std::cout << " surface_area : " << earth.surface_area << std::endl;
	std::cout << " mass         : " << earth.mass << std::endl;
	std::cout << " satellite    : " << earth.satellite << std::endl;
}
