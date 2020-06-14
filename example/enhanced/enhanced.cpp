#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(Satellite)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, radius)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(Planet)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(bool, populated)
MANAGED_FIELD(double, radius)
MANAGED_FIELD_ARRAY(Satellite, satellites)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(PhotosphericComposition)

MANAGED_FIELD(double, Hydrogen)
MANAGED_FIELD(double, Helium)
MANAGED_FIELD(double, Oxygen)
MANAGED_FIELD(double, Carbon)
MANAGED_FIELD(double, Iron)
MANAGED_FIELD(double, Neon)
MANAGED_FIELD(double, Nitrogen)
MANAGED_FIELD(double, Silicon)
MANAGED_FIELD(double, Magnesium)
MANAGED_FIELD(double, Sulphur)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(Star)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(long long, age)
MANAGED_FIELD(double, radius)
MANAGED_FIELD_STRUCT(PhotosphericComposition, photospheric_composition)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(PlanetSystem)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(long long, age)
MANAGED_FIELD(double, major_axis)
MANAGED_FIELD(bool, populated)
MANAGED_FIELD_STRUCT(Star, star)
MANAGED_FIELD_ARRAY(Planet, planets)
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), missions)

END_MANAGED_STRUCT

static void load(PlanetSystem & planet_system) {
	std::istringstream json_data(R"json(
	{
		"name": "solar system",
		"age": 4568000000,
		"major_axis": 4500000000,
		"populated": true,
		"star": {
			"name": "Sun",
			"age": 4600000000,
			"radius": 695700,
			"photospheric_composition": {
				"Hydrogen": 73.46,
				"Helium": 24.85,
				"Oxygen": 0.77,
				"Carbon": 0.29,
				"Iron": 0.16,
				"Neon": 0.12,
				"Nitrogen": 0.09,
				"Silicon": 0.07,
				"Magnesium": 0.05,
				"Sulphur": 0.04
			}
		},
		"planets": [
			{
				"name": "Mercury",
				"populated": false,
				"radius": 2440,
				"satellites": []
			},
			{
				"name": "Venus",
				"populated": false,
				"radius": 6052,
				"satellites": []
			},
			{
				"name": "Earth",
				"populated": true,
				"radius": 6371,
				"satellites": [
					{
						"name": "Moon",
						"radius": 1738
					}
				]
			},
			{
				"name": "Mars",
				"populated": false,
				"radius": 3390,
				"satellites": [
					{
						"name": "Phobos",
						"radius": 11.27
					},
					{
						"name": "Deimos",
						"radius": 6.2
					}
				]
			},
			{
				"name": "Jupiter",
				"populated": false,
				"radius": 71492,
				"satellites": [
					{
						"name": "Io",
						"radius": 1822
					},
					{
						"name": "Europa",
						"radius": 1561
					},
					{
						"name": "Ganymede",
						"radius": 2634
					},
					{
						"name": "Callisto",
						"radius": 2410
					}
				]
			},
			{
				"name": "Saturn",
				"populated": false,
				"radius": 58232,
				"satellites": [
					{
						"name": "Mimas",
						"radius": 198
					},
					{
						"name": "Enceladus",
						"radius": 252
					},
					{
						"name": "Tethys",
						"radius": 531
					}
				]
			},
			{
				"name": "Uranus",
				"populated": false,
				"radius": 25363,
				"satellites": [
					{
						"name": "Miranda",
						"radius": 236
					},
					{
						"name": "Ariel",
						"radius": 579
					},
					{
						"name": "Umbriel",
						"radius": 585
					}
				]
			},
			{
				"name": "Neptune",
				"populated": false,
				"radius": 24622,
				"satellites": [
					{
						"name": "Triton",
						"radius": 1354
					},
					{
						"name": "Nereid",
						"radius": 175
					}
				]
			}
		],
		"missions": [
			[
				"Lunar Orbiter",
				"Pioneer",
				"Ranger",
				"Surveyor",
				"Mariner"
			],
			[
				"Luna",
				"Venera",
				"Mars",
				"Salyut"
			],
			[
				"Venus Express",
				"Solar Orbiter",
				"Huygens"
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(planet_system, json_data);
}

static void print(PlanetSystem & planet_system) {
	std::cout << "PlanetSystem:" << std::endl;
	std::cout << " name       : " << planet_system.name << std::endl;
	std::cout << " age        : " << planet_system.age << std::endl;
	std::cout << " major_axis : " << planet_system.major_axis << std::endl;
	std::cout << " populated  : " << std::boolalpha << planet_system.populated << std::endl;
	std::cout << " star:" << std::endl;
	std::cout << "  name   : " << planet_system.star.name << std::endl;
	std::cout << "  age    : " << planet_system.star.age << std::endl;
	std::cout << "  radius : " << planet_system.star.radius << std::endl;
	std::cout << "  photospheric_composition:" << std::endl;
	std::cout << "   Hydrogen  : " << planet_system.star.photospheric_composition.Hydrogen << std::endl;
	std::cout << "   Helium    : " << planet_system.star.photospheric_composition.Helium << std::endl;
	std::cout << "   Oxygen    : " << planet_system.star.photospheric_composition.Oxygen << std::endl;
	std::cout << "   Carbon    : " << planet_system.star.photospheric_composition.Carbon << std::endl;
	std::cout << "   Iron      : " << planet_system.star.photospheric_composition.Iron << std::endl;
	std::cout << "   Neon      : " << planet_system.star.photospheric_composition.Neon << std::endl;
	std::cout << "   Nitrogen  : " << planet_system.star.photospheric_composition.Nitrogen << std::endl;
	std::cout << "   Silicon   : " << planet_system.star.photospheric_composition.Silicon << std::endl;
	std::cout << "   Magnesium : " << planet_system.star.photospheric_composition.Magnesium << std::endl;
	std::cout << "   Sulphur   : " << planet_system.star.photospheric_composition.Sulphur << std::endl;
	std::cout << " planets:" << std::endl;

	for (auto& planet : planet_system.planets.get_data()) {
		std::cout << "  [" << std::endl;
		std::cout << "   name      : " << planet.name << std::endl;
		std::cout << "   populated : " << planet.populated << std::endl;
		std::cout << "   radius    : " << planet.radius << std::endl;
		std::cout << "   satellites:" << std::endl;
		for (auto& satellite : planet.satellites.get_data()) {
			std::cout << "    {" << std::endl;
			std::cout << "     name   : " << satellite.name << std::endl;
			std::cout << "     radius : " << satellite.radius << std::endl;
			std::cout << "    }" << std::endl;
		}
		std::cout << "  ]" << std::endl;
	}

	std::cout << " missions:" << std::endl;
	for (auto& missions : planet_system.missions.get_data()) {
		std::cout << "  [" << std::endl;
		for (auto& mission : missions.get_data()) {
			std::cout << "    " << mission << std::endl;
		}
		std::cout << "  ]" << std::endl;
	}
}

int main() {
	PlanetSystem planet_system;

	load(planet_system);
	print(planet_system);
}
