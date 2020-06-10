#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

#define MANAGED_STRUCT_NAME MiB
BEGIN_MANAGED_STRUCT

MANAGED_FIELD_ARRAY(std::string, friends)
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), alien_groups)
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(MANAGED_ARRAY(std::string)), planet_groups)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

int main() {
	MiB mib;

	std::istringstream json_data(R"json(
	{
		"friends": [
			"Griffin",
			"Boris",
			"Agent K"
		],
		"alien_groups": [
			[
				"Edgar the Bug",
				"Boris the Animal",
				"Charlie",
				"Serleena"
			],
			[
				"Agent J",
				"Agent K",
				"Zed",
				"Griffin",
				"Roman the Fabulist"
			]
		],
		"planet_groups": [
			[
				[
					"Mercury",
					"Venus",
					"Earth",
					"Mars"
				],
				[
					"Jupiter",
					"Saturn",
					"Uranus",
					"Neptune"
				]
			],
			[
				[
					"Titan",
					"Ganymede"
				],
				[
					"Eris",
					"Titania"
				]
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(mib, json_data);

	std::cout << "mib:" << std::endl;

	std::cout << " friends :" << std::endl;
	for (auto& f : mib.friends.get_data()) {
		std::cout << "  " << f << std::endl;
	}

	std::cout << " aliens_groups :" << std::endl;
	for (auto& alien : mib.alien_groups.get_data()) {
		for (auto& name : alien.get_data()) {
			std::cout << "  " << name << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << " planets_groups :" << std::endl;
	for (auto& group : mib.planet_groups.get_data()) {
		std::cout << "  ---" << std::endl;
		for (auto& category : group.get_data()) {
			for (auto& planet : category.get_data()) {
				std::cout << "   " << planet << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
