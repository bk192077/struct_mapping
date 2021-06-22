#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Stage
{
	unsigned short engine_count;
	std::string fuel;
	long length;

	friend std::ostream& operator<<(std::ostream& os, const Stage& o)
	{
		os
			<< "  engine_count : " << o.engine_count << std::endl
			<< "  fuel         : " << o.fuel << std::endl
			<< "  length       : " << o.length << std::endl;

		return os;
	}
};

struct Spacecraft
{
	bool in_development;
	std::string name;
	int mass;
	std::map<std::string, Stage> stages;
	std::list<std::string> crew;
	std::set<int> ids;
	std::unordered_set<std::string> tools;

	friend std::ostream& operator<<(std::ostream& os, const Spacecraft& o)
	{
		os
			<< "in_development : " << std::boolalpha << o.in_development << std::endl
			<< "name           : " << o.name << std::endl
			<< "mass           : " << o.mass << std::endl
			<< "stages: " << std::endl;

		for (const auto& s : o.stages)
		{
			os << " " << s.first << std::endl << s.second;
		}

		os << "crew: " << std::endl;

		for (const auto& p : o.crew)
		{
			os << " " << p << std::endl;
		}

		os << "ids: " << std::endl;

		for (const auto& i : o.ids)
		{
			os << " " << i << std::endl;
		}

		os << "tools: " << std::endl;

		for (const auto& t : o.tools)
		{
			os << " " << t << std::endl;
		}

		return os;
	}
};

int main()
{
	sm::reg(&Stage::engine_count, "engine_count", sm::Default{6}, sm::Bounds{1, 31});
	sm::reg(&Stage::fuel, "fuel", sm::Default{"subcooled"});
	sm::reg(&Stage::length, "length", sm::Default{50});

	sm::reg(&Spacecraft::in_development, "in_development", sm::Required{});
	sm::reg(&Spacecraft::name, "name", sm::NotEmpty{});
	sm::reg(&Spacecraft::mass, "mass", sm::Default{5000000}, sm::Bounds{100000, 10000000});
	sm::reg(&Spacecraft::stages, "stages", sm::NotEmpty{});
	sm::reg(&Spacecraft::crew, "crew", sm::Default{std::list<std::string>{"Arthur", "Ford", "Marvin"}});
	sm::reg(&Spacecraft::ids, "ids", sm::Default{std::set<int>{14, 159}});
	sm::reg(&Spacecraft::tools, "tools", sm::NotEmpty{});

	Spacecraft starship;

	std::istringstream json_data(R"json(
	{
		"in_development": false,
		"name": "Vostok",
		"stages": {
			"first": {
				"engine_count": 31,
				"fuel": "compressed gas",
				"length": 70
			},
			"second": {}
		},
		"tools": [
			"Reverberating Carbonizer With Mutate Capacity",
			"Noisy Cricket",
			"The Series 4 De-Atomizer"
		]
	}
	)json");

	sm::map_json_to_struct(starship, json_data);

	std::cout << starship << std::endl;
}
