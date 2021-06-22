#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Reentry_module
{
	double total_mass;
};

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
	Reentry_module reentry_module;
	std::map<std::string, Stage> stages;
	std::list<std::string> crew;

	friend std::ostream& operator<<(std::ostream& os, const Spacecraft& o)
	{
		os
			<< "in_development : " << std::boolalpha << o.in_development << std::endl
			<< "name           : " << o.name << std::endl
			<< "mass           : " << o.mass << std::endl
			<< "reentry_module : " << std::endl
			<< " total_mass : " << o.reentry_module.total_mass << std::endl
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

		return os;
	}
};

int main()
{
	sm::reg(&Reentry_module::total_mass, "total_mass", sm::Default{145});

	sm::reg(&Stage::engine_count, "engine_count", sm::Default{6});
	sm::reg(&Stage::fuel, "fuel", sm::Default{"subcooled"});
	sm::reg(&Stage::length, "length", sm::Default{50});

	sm::reg(&Spacecraft::in_development, "in_development", sm::Default{true});
	sm::reg(&Spacecraft::name, "name", sm::Default{"Vostok"});
	sm::reg(&Spacecraft::mass, "mass", sm::Default{5000000});
	sm::reg(&Spacecraft::reentry_module, "reentry_module", sm::Default{Reentry_module{2900.42}});
	sm::reg(&Spacecraft::stages, "stages", sm::Default{std::map<std::string, Stage>{
		{
			"first",
			{
				31,
				"compressed gas",
				70
			}
		}
	}});
	sm::reg(&Spacecraft::crew, "crew", sm::Default{std::list<std::string>{"Arthur", "Ford", "Marvin"}});

	Spacecraft starship;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	sm::map_json_to_struct(starship, json_data);

	std::cout << starship << std::endl;
}
