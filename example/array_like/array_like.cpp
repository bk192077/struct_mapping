#include "struct_mapping/struct_mapping.h"

#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

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

	std::ostringstream out_json_data;
	struct_mapping::map_struct_to_json(mib, out_json_data, "  ");

	std::cout << out_json_data.str() << std::endl;
}
