#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h" // inclusion of library files



#define MANAGED_STRUCT_NAME Spaceship // setting the structure name
BEGIN_MANAGED_STRUCT                  // beginning of the structure Spaceship

MANAGED_FIELD(std::string, color)     // the field definition of the type 'std::string' and name 'color'
MANAGED_FIELD(double, mass)           // the field definition of the type 'double' and name 'mass'

END_MANAGED_STRUCT                    // the end of the structure Spaceship
#undef MANAGED_STRUCT_NAME            // undefines MANAGED_STRUCT_NAME



#define MANAGED_STRUCT_NAME Person         // setting the structure name
BEGIN_MANAGED_STRUCT                       // beginning of the structure Person

MANAGED_FIELD(bool, alien)                 // the field definition of the type 'bool' and name 'alien'
MANAGED_FIELD(std::string, name)           // the field definition of the type 'std::string' and name 'name'
MANAGED_FIELD(int, age)                    // the field definition of the type 'int' and name 'age'

MANAGED_FIELD_STRUCT(Spaceship, spaceship) // the field definition of the type 'Spaceship' and name 'spaceship'

MANAGED_FIELD_ARRAY(std::string, friends)  // the field definition of the type 'array of std::string' and name 'friends'

END_MANAGED_STRUCT                         // the end of the structure Person
#undef MANAGED_STRUCT_NAME                 // undef MANAGED_STRUCT_NAME



int main() {
	Person person;

	std::istringstream json_data(R"json(
	{
		"alien": true,
		"name": "Jeebs",
		"age": 42,
		"spaceship": {
			"color": "red",
			"mass": 231.65
		},
		"friends": [
			"Griffin",
			"Boris",
			"Agent K"
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(person, json_data); // json_data -> person

	std::cout << "Person:" << std::endl;
	std::cout << " alien : " << std::boolalpha << person.alien << std::endl;
	std::cout << " name  : " << person.name << std::endl;
	std::cout << " age   : " << person.age << std::endl;
	std::cout << " spaceship :" << std::endl;
	std::cout << "  color : " << person.spaceship.color << std::endl;
	std::cout << "  mass  : " << person.spaceship.mass << std::endl;

	std::cout << " friends :" << std::endl;
	for (auto& f : person.friends.get_data()) {
		std::cout << "  " << f << std::endl;
	}
	std::cout << std::endl;
}
