#include <iostream>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

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

 std::cout << person.name << " : " << person.age << " : " << std::boolalpha << person.student << std::endl;
}
