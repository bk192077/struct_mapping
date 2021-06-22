#include <iostream>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

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

	std::cout
		<< "earth.president:" << std::endl
		<< " name : " << earth.president.name << std::endl
		<< " mass : " << earth.president.mass << std::endl;
}
