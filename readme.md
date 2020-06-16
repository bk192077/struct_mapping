# StructMapping

![Release version](https://img.shields.io/badge/release-v0.2.0-blue.svg)

[документация на русском](/readme_ru.md)

English translation provided by [translate.google.com](https://translate.google.com)   

## Mapping json to and from a c++ structure

I would like to define a c++ structure

```cpp
struct Person {
 std::string name;
 int age;
 bool student;
} person;
```

pass the person instance to the mapping method along with json data

```cpp
map_json_to_struct(person, json_data)
```

then use the filled structure

```cpp
std::cout << person.name << " : " << person.age;
```

Or vice versa

```cpp
map_struct_to_json(person, json_data, "  ");
std::cout << json_data.str() << std::endl;
```

get Person as json

```cpp
{
 "name": "Agent K",
 "age": 42,
 "student": false
}
```

StructMapping is trying to solve these problems

## Compatibility

Compilation is required with -std=c++17 Mainly for:
* if constexpr
* static inline

Compiler | platform combinations on which StructMapping has been tested:

* GNU C++ 10.1.0 | Linux
* Clang 9 | Linux
* Visual C++ 2019 and Microsoft (R) C/C++ Optimizing Compiler Version 19.26.28806 for x64 | Windows 64-bit (except tests)

## Installation

StructMapping is a header-only C++ library. All library files are in the `include` folder.

To build examples and run tests proceed with the steps below ([cmake](https://cmake.org/download/) required):

1. create directory called `build` in StructMapping source directory
2. change to `build` directory
3. run `cmake ..` command to configure your build
4. run `cmake --build .` command. On successful build you will find binary files for examples and tests (under windows tests are not build) in the `bin` directory
5. (not for windows) to run the tests run `ctest` (you can get detailed output using `ctest -V`)
6. it is possible to install library system-wide by running `cmake --install .` command from the build  tree with administrative privileges. This will install all files according to system preferences.

## Usage

### Implementing a scenario with a Person structure

[example/person](/example/person/person.cpp)

define the structure

```cpp
BEGIN_MANAGED_STRUCT(Person)     // begin of structure

MANAGED_FIELD(std::string, name) // field with type 'std::string' and name 'name'
MANAGED_FIELD(int, age)          // field with type 'int' and name 'age'
MANAGED_FIELD(bool, student)     // field with type 'bool' and name 'student'

END_MANAGED_STRUCT               // end of structure
```

create an instance

```cpp
Person person;
```

set json data

```cpp
std::istringstream json_data(R"json(
{
 "name": "Jeebs",
 "age": 42,
 "student": true
}
)json");
```

pass the person instance to the mapping method along with json data

```cpp
mapper::map_json_to_struct(person, json_data);
```

use

```cpp
std::cout << person.name << " : " << person.age;
```

Completed code

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h" // inclusion of library files

BEGIN_MANAGED_STRUCT(Person)     // begin of structure

MANAGED_FIELD(std::string, name) // field with type 'std::string' and name 'name'
MANAGED_FIELD(int, age)          // field with type 'int' and name 'age'
MANAGED_FIELD(bool, student)     // field with type 'bool' and name 'student'

END_MANAGED_STRUCT               // end of structure

int main() {
 Person person;

 std::istringstream json_data(R"json(
  {
   "name": "Jeebs",
   "age": 42,
   "student": true
  }
 )json");

 struct_mapping::mapper::map_json_to_struct(person, json_data); // json_data -> person

 std::cout <<
  person.name << " : " <<
  person.age << " : " <<
  std::boolalpha << person.student <<
  std::endl;
}
```

result

```cpp
Jeebs : 42 : true
```

### Managed structure

For use in mapping, the structure must be defined using MANAGED macros:
- BEGIN_MANAGED_STRUCT
- MANAGED_FIELD
- MANAGED_FIELD_STRUCT
- MANAGED_FIELD_ARRAY
- END_MANAGED_STRUCT

#### BEGIN_MANAGED_STRUCT
Defines the begin of the structure and its name

BEGIN_MANAGED_STRUCT(structure name)

```cpp
BEGIN_MANAGED_STRUCT(Person)
```

#### MANAGED_FIELD
Adds a structure field when the field is one of the following types:
- bool
- integral types (char, int, ...)
- floating point types (float, double)
- std::string

MANAGED_FIELD(field type, field name)

```cpp
MANAGED_FIELD(bool, ready)
MANAGED_FIELD(int, size)
MANAGED_FIELD(double, speed)
MANAGED_FIELD(std::string, color)
```

#### MANAGED_FIELD_STRUCT
Adds a structure field when the field has a structure type:

MANAGED_FIELD_STRUCT(field type, field name)

```cpp
MANAGED_FIELD_STRUCT(President, president)
```

The field type here should be a managed structure. For example, in the Earth structure, the president field is of the President type, which you specified earlier.

```cpp
BEGIN_MANAGED_STRUCT(President) <-- define the structure President

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, mass)

END_MANAGED_STRUCT


BEGIN_MANAGED_STRUCT(Earth)

MANAGED_FIELD_STRUCT(President, president) <-- define a field with type President

END_MANAGED_STRUCT
```

#### MANAGED_FIELD_ARRAY
Adds a structure field when the field has an array type:

MANAGED_FIELD_ARRAY(array element type, field type)

```cpp
MANAGED_FIELD_ARRAY(std::string, friends)
```

array element type can be one of the following
- bool
- integral types (char, int, ...)
- floating point types (float, double)
- std::string
- managed structure
- array

real field type becomes `managed::ManagedArray<array element type>` Inside ManagedArray is std::vector, which will contain the values of the array. Reference to this vector can be obtained through the method
```cpp
std::vector<T> & ManagedArray::get_data();
````

for example
	

```cpp
mib.friends.get_data()[13] // array element at index thirteen
```

If you need an array whose elements are also arrays, you must use the same macro `MANAGED_FIELD_ARRAY` for the field, but the type of elements must be specified through the macro` MANAGED_ARRAY`

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), alien_groups)
```

Access to elements should take into account the nesting of vectors

```cpp
mib.alien_groups.get_data()[13].get_data()[42] // array element at index forty two in an array
                                               // at index thirteen
```

Array dimension can be increased

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(MANAGED_ARRAY(std::string)), planet_groups)
```

#### END_MANAGED_STRUCT
Defines the end of the structure.

END_MANAGED_STRUCT


```cpp
END_MANAGED_STRUCT
```

### Mapping json to c ++ structure

To map json to a structure, you must define a managed structure using MANAGED macros and call the function

```cpp
template<typename T>
void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data);
```

- `result_struct` - reference to the resulting structure
- `json_data` - reference to json data input stream

#### simple types example

[example/simple](/example/simple/simple.cpp)

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(Planet)

MANAGED_FIELD(bool, giant)
MANAGED_FIELD(long long, surface_area)
MANAGED_FIELD(double, mass)
MANAGED_FIELD(std::string, satellite)

END_MANAGED_STRUCT

int main() {
 Planet earth;

 std::istringstream json_data(R"json(
  {
   "giant": false,
   "surface_area": 510072000000000,
   "mass": 5.97237e24,
   "satellite": "Moon"
  }
 )json");

 struct_mapping::mapper::map_json_to_struct(earth, json_data);

 std::cout << "earth" << std::endl;
 std::cout << " giant        : " << std::boolalpha << earth.giant << std::endl;
 std::cout << " surface_area : " << earth.surface_area << std::endl;
 std::cout << " mass         : " << earth.mass << std::endl;
 std::cout << " satellite    : " << earth.satellite << std::endl;
}
```

result

```cpp
earth
 giant        : false
 surface_area : 510072000000000
 mass         : 5.97237e+24
 satellite    : Moon
```

#### structure example

[example/struct](/example/struct/struct.cpp)

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(President)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, mass)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(Earth)

MANAGED_FIELD_STRUCT(President, president)

END_MANAGED_STRUCT

int main() {
 Earth earth;

 std::istringstream json_data(R"json(
  {
   "president": {
    "name": "Agent K",
    "mass": 75.6
   }
  }
 )json");

 struct_mapping::mapper::map_json_to_struct(earth, json_data);

 std::cout << "earth.president:" << std::endl;
 std::cout << " name : " << earth.president.name << std::endl;
 std::cout << " mass : " << earth.president.mass << std::endl;
}
```

result

```cpp
earth.president:
 name : Agent K
 mass : 75.6
```

#### example of using arrays

[example/array](/example/array/array.cpp)


```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

BEGIN_MANAGED_STRUCT(MiB)

MANAGED_FIELD_ARRAY(std::string, friends)
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), alien_groups)
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(MANAGED_ARRAY(std::string)), planet_groups)

END_MANAGED_STRUCT

int main() {
 MiB mib;

 std::istringstream json_data(R"json(
  {
   "friends": [
    "Griffin",
    "Boris",
    "Agent K"
   ],
   "alien_groups": [
    [
     "Edgar the Bug",
     "Boris the Animal",
     "Charlie",
     "Serleena"
    ],
    [
     "Agent J",
     "Agent K",
     "Zed",
     "Griffin",
     "Roman the Fabulist"
    ]
   ],
   "planet_groups": [
    [
     [
      "Mercury",
      "Venus",
      "Earth",
      "Mars"
     ],
     [
      "Jupiter",
      "Saturn",
      "Uranus",
      "Neptune"
     ]
    ],
    [
     [
      "Titan",
      "Ganymede"
     ],
     [
      "Eris",
      "Titania"
     ]
    ]
   ]
  }
 )json");

 struct_mapping::mapper::map_json_to_struct(mib, json_data);

 std::cout << "mib:" << std::endl;

 std::cout << " friends :" << std::endl;
 for (auto& f : mib.friends.get_data()) {
  std::cout << "  " << f << std::endl;
 }

 std::cout << " aliens_groups :" << std::endl;
 for (auto& alien : mib.alien_groups.get_data()) {
  for (auto& name : alien.get_data()) {
   std::cout << "  " << name << std::endl;
  }
  std::cout << std::endl;
 }

 std::cout << " planets_groups :" << std::endl;
 for (auto& group : mib.planet_groups.get_data()) {
  std::cout << "  ---" << std::endl;
  for (auto& category : group.get_data()) {
   for (auto& planet : category.get_data()) {
    std::cout << "   " << planet << std::endl;
   }
   std::cout << std::endl;
  }
  std::cout << std::endl;
 }

 std::cout << std::endl;
}
```

result

```cpp
mib:
 friends :
  Griffin
  Boris
  Agent K
 aliens_groups :
  Edgar the Bug
  Boris the Animal
  Charlie
  Serleena

  Agent J
  Agent K
  Zed
  Griffin
  Roman the Fabulist

 planets_groups :
  ---
   Mercury
   Venus
   Earth
   Mars

   Jupiter
   Saturn
   Uranus
   Neptune


  ---
   Titan
   Ganymede

   Eris
   Titania
```

### Reverse mapping of c ++ structure to json

To reverse map the structure to json, you must define a managed structure using MANAGED macros and call the function

```cpp
template<typename T>
void map_struct_to_json(T & source_struct, std::basic_ostream<char> & json_data, std::string indent);
```

- `source_struct` - reference to the source structure
- `json_data` - reference to json data output stream
- `indent` - indentation (if set, makes the output format better readable)

[example/struct_to_json](/example/struct_to_json/struct_to_json.cpp)

```cpp
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
```

result

```cpp
{
  "giant": false,
  "surface_area": 510072000,
  "mass": 5.97237e+24,
  "volume": 1.08321e+12,
  "orbital_period": 31536000,
  "name": "Terra",
  "terrestrial": true,
  "shape": "nearly spherical",
  "ocean": {
    "water_volume": 1.332e+09,
    "surface_area": 361132000,
    "liquid": true,
    "name": "World Ocean",
    "color": {
      "name": "blue"
    },
    "parts": [
      {
        "name": "Pacific Ocean",
        "average_depth": 4.28011
      },
      {
        "name": "Atlantic Ocean",
        "average_depth": 3.646
      }
    ]
  }
}
```

## Exceptions

StructMapping throws a `StructMappingException` exception during the mapping process

* when using a field with a nonexistent name for the structure (in json, the name of the value in the object does not correspond to any of the fields in the C ++ structure)
* when you try to set the value of the wrong type for the array (in json, the type of the value in the array does not match the value type of the C ++ array)
*	when reaching the end of the json stream, when parsing is not completed (the process of parsing an object, value, etc.)
* when a character is received in the json stream that is not valid at this position (for example, an array termination character, if the beginning character of the array was not received earlier)
* when conversion of json string representing number to number fails

After an exception, the state of the managed structure is incomplete and cannot be used.
