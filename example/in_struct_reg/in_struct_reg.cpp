#include <iostream>
#include <sstream>
#include <vector>

#include "struct_mapping/struct_mapping.h"

struct Planet {
	bool giant = [] {struct_mapping::reg(&Planet::giant, "giant"); return false;} ();
	long long surface_area = [] {struct_mapping::reg(&Planet::surface_area, "surface_area"); return 0;} ();
	double mass = [] {struct_mapping::reg(&Planet::mass, "mass"); return 0;} ();
	std::vector<std::string> satellites = [] {struct_mapping::reg(&Planet::satellites, "satellites"); return std::vector<std::string>{};} ();
};

int main() {
	std::istringstream json_data(R"json(
	{
		"giant": false,
		"surface_area": 510072000000000,
		"mass": 5.97237e24,
		"satellites": ["Moon", "R24"]
	}
	)json");

	Planet earth;

	struct_mapping::map_json_to_struct(earth, json_data);

	std::cout << "earth" << std::endl;
	std::cout << " giant        : " << std::boolalpha << earth.giant << std::endl;
	std::cout << " surface_area : " << earth.surface_area << std::endl;
	std::cout << " mass         : " << earth.mass << std::endl;
	std::cout << " satellite    : [ ";
	for (auto & s : earth.satellites) std::cout << s << ", ";
	std::cout << "]" << std::endl;
}
