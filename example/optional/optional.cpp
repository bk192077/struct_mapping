#include "struct_mapping/struct_mapping.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

struct Engine
{
	int age;
};

struct Car
{
	std::optional<Engine> engine;
	std::optional<std::string> name;
	std::optional<int> max_speed;
};

int main()
{
	struct_mapping::reg(&Engine::age, "age");
	
	struct_mapping::reg(&Car::engine, "engine");
	struct_mapping::reg(&Car::name, "name", struct_mapping::NotEmpty{});
	struct_mapping::reg(&Car::max_speed, "max_speed", struct_mapping::Bounds{0, 100});

	std::istringstream json_data(R"json(
	{
		"engine": 
		{
			"age": 42
		},
		"name": "Mercedes"
	}
	)json");

	Car car;

	struct_mapping::map_json_to_struct(car, json_data);

	std::ostringstream out_json_data;
	struct_mapping::map_struct_to_json(car, out_json_data, "  ", false);
	std::cout << out_json_data.str() << std::endl;
}
