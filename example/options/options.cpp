#include <iostream>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Stage {
	unsigned short engine_count;
	std::string fuel;
	long length;

	friend std::ostream & operator<<(std::ostream & os, const Stage & o) {
		os << " engine_count : " << o.engine_count << std::endl;
		os << " fuel         : " << o.fuel << std::endl;
		os << " length       : " << o.length << std::endl;

		return os;
	}
};

struct Spacecraft {
	bool in_development;
	std::string name;
	int mass;
	Stage first_stage;
	Stage second_stage;

	friend std::ostream & operator<<(std::ostream & os, const Spacecraft & o) {
		os << "in_development : " << std::boolalpha << o.in_development << std::endl;
		os << "name           : " << o.name << std::endl;
		os << "mass           : " << o.mass << std::endl << std::endl;
		os << "first stage: " << std::endl << o.first_stage << std::endl;
		os << "second stage: " << std::endl << o.second_stage << std::endl;

		return os;
	}
};

int main() {
	sm::reg(&Stage::engine_count, "engine_count", sm::Default{6}, sm::Bounds{1, 31});
	sm::reg(&Stage::fuel, "fuel", sm::Default{"subcooled"});
	sm::reg(&Stage::length, "length", sm::Default{50});

	sm::reg(&Spacecraft::in_development, "in_development", sm::Default{true});
	sm::reg(&Spacecraft::name, "name", sm::NotEmpty{});
	sm::reg(&Spacecraft::mass, "mass", sm::Default{5000000}, sm::Bounds{100000, 10000000});
	sm::reg(&Spacecraft::first_stage, "first_stage");
	sm::reg(&Spacecraft::second_stage, "second_stage");

	Spacecraft starship;

	std::istringstream json_data(R"json(
	{
		"name": "Vostok",
		"second_stage": {
			"engine_count": 31,
			"fuel": "compressed gas",
			"length": 70
		}
	}
	)json");

	sm::map_json_to_struct(starship, json_data);

	std::cout << starship << std::endl;
}
