#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(Person)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(int, age)
MANAGED_FIELD(bool, student)

END_MANAGED_STRUCT

int main() {
 Person person;

 std::istringstream json_data(R"json(
  {
   "name": "Jeebs",
   "age": 42,
   "student": true
  }
 )json");

 struct_mapping::mapper::map_json_to_struct(person, json_data);

 std::cout << person.name << " : " << person.age << " : " << std::boolalpha << person.student << std::endl;
}
