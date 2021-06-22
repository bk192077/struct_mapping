#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "struct_mapping/struct_mapping.h"

struct Friend
{
	std::string name;
	std::set<int> counters;

	bool operator==(const Friend& o) const
	{
		return name == o.name;
	}
};

struct FriendHash
{
	size_t operator()(const Friend& o) const
	{
		return static_cast<size_t>(o.name.size());
	}
};

struct MiB
{
	std::unordered_set<Friend, FriendHash> friends;
	std::vector<std::list<std::string>> alien_groups;
	std::vector<std::list<std::vector<std::string>>> planet_groups;
};

int main()
{
	struct_mapping::reg(&Friend::name, "name");
	struct_mapping::reg(&Friend::counters, "counters");

	struct_mapping::reg(&MiB::friends, "friends");
	struct_mapping::reg(&MiB::alien_groups, "alien_groups");
	struct_mapping::reg(&MiB::planet_groups, "planet_groups");

	std::istringstream json_data(R"json(
	{
		"friends": [
			{
				"name": "Griffin",
				"counters": [1,3,4]
			},
			{
				"name": "Boris",
				"counters": []
			},
			{
				"name": "Agent K",
				"counters": [42, 128]
			}
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

	MiB mib;

	struct_mapping::map_json_to_struct(mib, json_data);

	std::cout << "mib:" << std::endl;

	std::cout << " friends :" << std::endl;
	for (const auto& f : mib.friends)
	{
		std::cout << "  name: [ " << f.name << " ], counters: [";
		for (const auto& c : f.counters)
		{
			std::cout << c << ", ";
		}
		std::cout << "]" << std::endl;
	}

	std::cout << std::endl << " aliens_groups :" << std::endl;
	for (const auto& alien : mib.alien_groups)
	{
		for (const auto& name : alien)
		{
			std::cout << "  " << name << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << " planets_groups :" << std::endl;
	for (const auto& group : mib.planet_groups)
	{
		std::cout << "  ---" << std::endl;
		for (const auto& category : group)
		{
			for (const auto& planet : category)
			{
				std::cout << "   " << planet << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
