#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "struct_mapping/struct_mapping.h"

struct Satellite
{
	std::string name;
	long radius;
};

struct Planet
{
	std::string name;
	bool populated;
	long radius;
	std::vector<Satellite> satellites;
};

struct PhotosphericComposition
{
	double Hydrogen;
	double Helium;
	double Oxygen;
	double Carbon;
	double Iron;
	double Neon;
	double Nitrogen;
	double Silicon;
	double Magnesium;
	double Sulphur;
};

struct Star
{
	std::string name;
	long long age;
	long radius;
	PhotosphericComposition photospheric_composition;
};

struct PlanetSystem
{
	std::string name;
	long long age;
	long long major_axis;
	bool populated;
	Star star;
	std::list<Planet> planets;
	std::map<std::string, std::list<std::string>> missions;
};

static void load(PlanetSystem& planet_system)
{
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
						"radius": 11
					},
					{
						"name": "Deimos",
						"radius": 6
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
		"missions": {
			"u": [
				"Lunar Orbiter",
				"Pioneer",
				"Ranger",
				"Surveyor",
				"Mariner"
			],
			"s": [
				"Luna",
				"Venera",
				"Mars",
				"Salyut"
			],
			"e": [
				"Venus Express",
				"Solar Orbiter",
				"Huygens"
			]
		}
	}
	)json");

	struct_mapping::map_json_to_struct(planet_system, json_data);
}

static void print(PlanetSystem& planet_system)
{
	std::cout
		<< "PlanetSystem:" << std::endl
		<< " name       : " << planet_system.name << std::endl
		<< " age        : " << planet_system.age << std::endl
		<< " major_axis : " << planet_system.major_axis << std::endl
		<< " populated  : " << std::boolalpha << planet_system.populated << std::endl
		<< " star:" << std::endl
		<< "  name   : " << planet_system.star.name << std::endl
		<< "  age    : " << planet_system.star.age << std::endl
		<< "  radius : " << planet_system.star.radius << std::endl
		<< "  photospheric_composition:" << std::endl
		<< "   Hydrogen  : " << planet_system.star.photospheric_composition.Hydrogen << std::endl
		<< "   Helium    : " << planet_system.star.photospheric_composition.Helium << std::endl
		<< "   Oxygen    : " << planet_system.star.photospheric_composition.Oxygen << std::endl
		<< "   Carbon    : " << planet_system.star.photospheric_composition.Carbon << std::endl
		<< "   Iron      : " << planet_system.star.photospheric_composition.Iron << std::endl
		<< "   Neon      : " << planet_system.star.photospheric_composition.Neon << std::endl
		<< "   Nitrogen  : " << planet_system.star.photospheric_composition.Nitrogen << std::endl
		<< "   Silicon   : " << planet_system.star.photospheric_composition.Silicon << std::endl
		<< "   Magnesium : " << planet_system.star.photospheric_composition.Magnesium << std::endl
		<< "   Sulphur   : " << planet_system.star.photospheric_composition.Sulphur << std::endl
		<< " planets:" << std::endl;

	for (const auto& planet : planet_system.planets)
	{
		std::cout
			<< "  [" << std::endl
			<< "   name      : " << planet.name << std::endl
			<< "   populated : " << planet.populated << std::endl
			<< "   radius    : " << planet.radius << std::endl
			<< "   satellites:" << std::endl;

		for (const auto& satellite : planet.satellites)
		{
			std::cout
				<< "    {" << std::endl
				<< "     name   : " << satellite.name << std::endl
				<< "     radius : " << satellite.radius << std::endl
				<< "    }" << std::endl;
		}
		std::cout << "  ]" << std::endl;
	}

	std::cout << " missions:" << std::endl;
	for (const auto& [name, missions] : planet_system.missions)
	{
		std::cout << "  " << name << " : [ ";
		for (const auto& mission : missions)
		{
			std::cout << mission << ", ";
		}
		std::cout << "]" << std::endl;
	}
}

int main()
{
	struct_mapping::reg(&Satellite::name, "name");
	struct_mapping::reg(&Satellite::radius, "radius");

	struct_mapping::reg(&Planet::name, "name");
	struct_mapping::reg(&Planet::populated, "populated");
	struct_mapping::reg(&Planet::radius, "radius");
	struct_mapping::reg(&Planet::satellites, "satellites");

	struct_mapping::reg(&PhotosphericComposition::Hydrogen, "Hydrogen");
	struct_mapping::reg(&PhotosphericComposition::Helium, "Helium");
	struct_mapping::reg(&PhotosphericComposition::Oxygen, "Oxygen");
	struct_mapping::reg(&PhotosphericComposition::Carbon, "Carbon");
	struct_mapping::reg(&PhotosphericComposition::Iron, "Iron");
	struct_mapping::reg(&PhotosphericComposition::Neon, "Neon");
	struct_mapping::reg(&PhotosphericComposition::Nitrogen, "Nitrogen");
	struct_mapping::reg(&PhotosphericComposition::Silicon, "Silicon");
	struct_mapping::reg(&PhotosphericComposition::Magnesium, "Magnesium");
	struct_mapping::reg(&PhotosphericComposition::Sulphur, "Sulphur");

	struct_mapping::reg(&Star::name, "name");
	struct_mapping::reg(&Star::age, "age");
	struct_mapping::reg(&Star::radius, "radius");
	struct_mapping::reg(&Star::photospheric_composition, "photospheric_composition");

	struct_mapping::reg(&PlanetSystem::name, "name");
	struct_mapping::reg(&PlanetSystem::age, "age");
	struct_mapping::reg(&PlanetSystem::major_axis, "major_axis");
	struct_mapping::reg(&PlanetSystem::populated, "populated");
	struct_mapping::reg(&PlanetSystem::star, "star");
	struct_mapping::reg(&PlanetSystem::planets, "planets");
	struct_mapping::reg(&PlanetSystem::missions, "missions");

	PlanetSystem planet_system;

	load(planet_system);
	print(planet_system);
}
