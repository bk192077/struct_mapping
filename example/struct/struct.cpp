#include "struct_mapping/struct_mapping.h"

#include <iostream>
#include <sstream>
#include <string>

struct President
{
	std::string name;
	double mass;
};

struct Earth
{
	President president;
};

int main()
{
	struct_mapping::reg(&President::name, "name");
	struct_mapping::reg(&President::mass, "mass");

	struct_mapping::reg(&Earth::president, "president");

	Earth earth;

	std::istringstream json_data(R"json(
	{
		"president": {
			"name": "Agent K",
			"mass": 75.6
		}
	}
	)json");

	struct_mapping::map_json_to_struct(earth, json_data);

	std::ostringstream out_json_data;
	struct_mapping::map_struct_to_json(earth, out_json_data, "  ");

	std::cout << out_json_data.str() << std::endl;
}
