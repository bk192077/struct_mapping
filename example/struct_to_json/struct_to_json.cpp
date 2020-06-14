#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(OceanPart)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, average_depth)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(OceanColor)

MANAGED_FIELD(std::string, name)

END_MANAGED_STRUCT


BEGIN_MANAGED_STRUCT(Ocean)

MANAGED_FIELD(double, water_volume)
MANAGED_FIELD(long long, surface_area)
MANAGED_FIELD(bool, liquid)
MANAGED_FIELD(std::string, name)

MANAGED_FIELD_STRUCT(OceanColor, color)

MANAGED_FIELD_ARRAY(OceanPart, parts)

END_MANAGED_STRUCT


BEGIN_MANAGED_STRUCT(Planet)

MANAGED_FIELD(bool, giant)
MANAGED_FIELD(long long, surface_area)
MANAGED_FIELD(double, mass)
MANAGED_FIELD(double, volume)
MANAGED_FIELD(long long, orbital_period)
MANAGED_FIELD(std::string, name)
MANAGED_FIELD(bool, terrestrial)
MANAGED_FIELD(std::string, shape)

MANAGED_FIELD_STRUCT(Ocean, ocean)

END_MANAGED_STRUCT

int main() {
	Planet earth;

	earth.giant = false;
	earth.terrestrial = true;
	earth.surface_area = 510072000;
	earth.orbital_period = 365 * 24 * 3600;
	earth.mass = 5.97237e24;
	earth.name = "Terra";
	earth.volume = 1.08321e12;
	earth.shape = "nearly spherical";

	earth.ocean.water_volume = 1332000000;
	earth.ocean.surface_area = 361132000;
	earth.ocean.liquid = true;
	earth.ocean.name = "World Ocean";
	earth.ocean.color.name = "blue";

	OceanPart pacific;
	pacific.name = "Pacific Ocean";
	pacific.average_depth = 4.280111;

	OceanPart atlantic;
	atlantic.name = "Atlantic Ocean";
	atlantic.average_depth = 3.646;

	earth.ocean.parts.get_data().push_back(pacific);
	earth.ocean.parts.get_data().push_back(atlantic);

	std::ostringstream json_data;
	struct_mapping::mapper::map_struct_to_json(earth, json_data, "  ");

	std::cout << json_data.str() << std::endl;
}
