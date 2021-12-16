#include "struct_mapping/struct_mapping.h"

#include <iostream>
#include <sstream>
#include <string>

struct Person
{
	std::string name;
	int age;
	bool student;
};

int main()
{
	struct_mapping::reg(&Person::name, "name");
	struct_mapping::reg(&Person::age, "age");
	struct_mapping::reg(&Person::student, "student");

	Person person;

 std::istringstream json_data(R"json(
  {
   "name": "Jeebs",
   "age": 42,
   "student": true
  }
 )json");

 struct_mapping::map_json_to_struct(person, json_data);

	std::ostringstream out_json_data;
	struct_mapping::map_struct_to_json(person, out_json_data, "  ");

	std::cout << out_json_data.str() << std::endl;
}
