#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(President)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, mass)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(Earth)

MANAGED_FIELD_STRUCT(President, president)

END_MANAGED_STRUCT

int main() {
	Earth earth;

	std::istringstream json_data(R"json(
	{
		"president": {
			"name": "Agent K",
			"mass": 75.6
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(earth, json_data);

	std::cout << "earth.president:" << std::endl;
	std::cout << " name : " << earth.president.name << std::endl;
	std::cout << " mass : " << earth.president.mass << std::endl;
}
