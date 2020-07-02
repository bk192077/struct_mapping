# StructMapping

![Release version](https://img.shields.io/badge/release-v0.4.0-blue.svg)

[документация на русском](/readme_ru.md)

English translation provided by [translate.google.com](https://translate.google.com)   

### Table of contents
- [Introduction](#introduction)
- [Compatibility](#compatibility)
- [Installation](#installation)
- [Usage](#usage)
	- [Implementing a scenario with a Person structure](#implementing_a_scenario_with_a_Person_structure)
	- [Mapping json to c ++ structure](#mapping_json_to_c_plus_plus_structure)
		- [Simple types example](#simple_types_example)
		- [Structure example](#structure_example)
		- [Sequence container example](#sequence_container_example)
		- [Associative container example](#associative_container_example)
		- [Mapping options](#options)
			- [Bounds](#options_bounds)
			- [Default](#options_default)
			- [NotEmpty](#options_not_empty)
			- [Options example](#options_example)
	- [Reverse mapping of c ++ structure to json](#reverse_mapping_of_c_plus_plus_structure_to_json)
	- [Registration of data members combined with initialization](#registration_of_data_members_combined_with_initialization)
- [Exceptions](#exceptions)

## Mapping json to and from a c++ structure <div id="introduction"></div>

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

## Compatibility <div id="compatibility"></div>

Compilation is required with -std=c++17 Mainly for:

* if constexpr
* static inline

Compiler | platform combinations on which StructMapping has been tested:

* GNU C++ 10.1.0 | Linux
* Visual C++ 2019 and Microsoft (R) C/C++ Optimizing Compiler Version 19.26.28806 for x64 | Windows 64-bit (except tests)

As types of member-data can be used

* bool
* char, unsigned char, short, unsigned short, int unsigned int, long, long long
* float, double
* std::string
* std::list
* std::vector
* std::map (the key can only be std::string)
* std::unordered_map (the key can only be std::string)
* std::multimap (the key can only be std::string)
* std::unordered_multimap (the key can only be std::string)
* c++ structure

## Installation <div id="installation"></div>

StructMapping is a header-only C++ library. All library files are in the `include` folder.

To build examples and run tests proceed with the steps below ([cmake](https://cmake.org/download/) required):

1. create directory called `build` in StructMapping source directory
2. change to `build` directory
3. run `cmake ..` command to configure your build
4. run `cmake --build .` command. On successful build you will find binary files for examples and tests (under windows tests are not build) in the `bin` directory
5. (not for windows) to run the tests run `ctest` (you can get detailed output using `ctest -V`)
6. it is possible to install library system-wide by running `cmake --install .` command from the build  tree with administrative privileges. This will install all files according to system preferences.

## Usage <div id="usage"></div>

### Implementing a scenario with a Person structure <div id="implementing_a_scenario_with_a_Person_structure"></div>

[example/person](/example/person/person.cpp)

define the structure

```cpp
struct Person {
 std::string name;
 int age;
 bool student;
};
```

register members

```cpp
struct_mapping::reg(&Person::name, "name");
struct_mapping::reg(&Person::age, "age");
struct_mapping::reg(&Person::student, "student");
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
std::cout <<
 person.name << " : " <<
 person.age << " : " <<
 std::boolalpha << person.student << std::endl;
```

Completed code

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

struct Person {
 std::string name;
 int age;
 bool student;
};

int main() {
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

 std::cout <<
  person.name << " : " <<
  person.age << " : " <<
  std::boolalpha << person.student << std::endl;
}
```

result

```cpp
Jeebs : 42 : true
```

### Mapping json to c ++ structure <div id="mapping_json_to_c_plus_plus_structure"></div>

To map json to a structure, it is necessary to register all data members of all structures that you want to mapped using for each field

```cpp
template<typename T, typename V, typename ... U, template<typename> typename ... Options>
inline void reg(V T::* ptr, std::string const & name, Options<U>&& ... options);
```

- `ptr` - pointer to data member
- `name` - member name
- `options` - [mapping options](#options)

and call the function

```cpp
template<typename T>
void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data);
```

- `result_struct` - reference to the resulting structure
- `json_data` - reference to json data input stream

During the mapping process, the correspondence between the types of data members and the types of set value is checked, and (for numbers) the set value is checked to get out of the range of values of the data member type. In case of type mismatch or out of range values [exceptions](#exceptions) are generated.

#### simple types example <div id="simple_types_example"></div>

[example/simple](/example/simple/simple.cpp)

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

struct Planet {
 bool giant;
 long long surface_area;
 double mass;
 std::string satellite;
};

int main() {
 struct_mapping::reg(&Planet::giant, "giant");
 struct_mapping::reg(&Planet::surface_area, "surface_area");
 struct_mapping::reg(&Planet::mass, "mass");
 struct_mapping::reg(&Planet::satellite, "satellite");

 Planet earth;

 std::istringstream json_data(R"json(
  {
   "giant": false,
   "surface_area": 510072000000000,
   "mass": 5.97237e24,
   "satellite": "Moon"
  }
 )json");

 struct_mapping::map_json_to_struct(earth, json_data);

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

#### structure example <div id="structure_example"></div>

[example/struct](/example/struct/struct.cpp)

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h"

struct President {
 std::string name;
 double mass;
};

struct Earth {
 President president;
};

int main() {
 struct_mapping::reg(&President::name, "name");
 struct_mapping::reg(&President::mass, "mass");

 struct_mapping::reg(&Earth::president, "president");

 Earth earth;

 std::istringstream json_data(R"json(
  {
   "president": {
    "name": "Agent K",
    "mass": 75.6
   }
  }
 )json");

 struct_mapping::map_json_to_struct(earth, json_data);

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

#### sequence container example <div id="sequence_container_example"></div>

[example/array](/example/array/array.cpp)

```cpp
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#include "struct_mapping/struct_mapping.h"

struct Friend {
 std::string name;
 std::list<int> counters;
};

struct MiB {
 std::list<Friend> friends;
 std::vector<std::list<std::string>> alien_groups;
 std::vector<std::list<std::vector<std::string>>> planet_groups;
};

int main() {
 struct_mapping::reg(&Friend::name, "name");
 struct_mapping::reg(&Friend::counters, "counters");

 struct_mapping::reg(&MiB::friends, "friends");
 struct_mapping::reg(&MiB::alien_groups, "alien_groups");
 struct_mapping::reg(&MiB::planet_groups, "planet_groups");

 std::istringstream json_data(R"json(
  {
   "friends": [
    {
     "name": "Griffin",
     "counters": [1,3,4]
    },
    {
     "name": "Boris",
     "counters": []
    },
    {
     "name": "Agent K",
     "counters": [42, 128]
    }
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

 MiB mib;

 struct_mapping::map_json_to_struct(mib, json_data);

 std::cout << "mib:" << std::endl;

 std::cout << " friends :" << std::endl;
 for (auto& f : mib.friends) {
  std::cout << "  name: [ " << f.name << " ], counters: [";
  for (auto& c : f.counters) {
   std::cout << c << ", ";
  }
  std::cout << "]" << std::endl;
 }

 std::cout << std::endl << " aliens_groups :" << std::endl;
 for (auto& alien : mib.alien_groups) {
  for (auto& name : alien) {
   std::cout << "  " << name << std::endl;
  }
  std::cout << std::endl;
 }

 std::cout << " planets_groups :" << std::endl;
 for (auto& group : mib.planet_groups) {
  std::cout << "  ---" << std::endl;
  for (auto& category : group) {
   for (auto& planet : category) {
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
  name: [ Griffin ], counters: [1, 3, 4, ]
  name: [ Boris ], counters: []
  name: [ Agent K ], counters: [42, 128, ]

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

#### associative container example <div id="associative_container_example"></div>

[example/map](/example/map/map.cpp)

```cpp
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>

#include "struct_mapping/struct_mapping.h"

struct Library {
 std::unordered_map<std::string, std::multimap<std::string, int>> counters;
 std::multimap<std::string, std::unordered_multimap<std::string, std::string>> books;
};

int main() {
 struct_mapping::reg(&Library::counters, "counters");
 struct_mapping::reg(&Library::books, "books");

 Library library;

 std::istringstream json_data(R"json(
  {
   "counters": {
    "first": {
     "112": 13,
     "142": 560,
     "112": 0
    },
    "second": {
     "2": 28,
     "20": 411
    },
    "third": {
    }
   },
   "books": {
    "asd": {
     "Leo": "aaa",
     "Leo": "bbb",
     "Mark": "ccc"
    },
    "wwert": {
     "Gogol": "ddd",
     "Tom": "eee"
    }
   }
  }
 )json");

 struct_mapping::map_json_to_struct(library, json_data);

 std::cout << "library:" << std::endl;

 std::cout << " counters :" << std::endl;
 for (auto [n1, v] : library.counters) {
  std::cout << "  " << n1 << " : ";
  for (auto [n2, c] : v) {
   std::cout << "[" << n2 << ", " << c << "], ";
  }
  std::cout << std::endl;
 }

 std::cout << " books :" << std::endl;
 for (auto [n1, v] : library.books) {
  std::cout << "  " << n1 << " : ";
  for (auto [n2, b] : v) {
   std::cout << "[" << n2 << ", " << b << "], ";
  }
  std::cout << std::endl;
 }

 std::cout << std::endl;
}
```

result

```cpp
library:
 counters :
  third : 
  second : [2, 28], [20, 411], 
  first : [112, 13], [112, 0], [142, 560], 
 books :
  asd : [Mark, ccc], [Leo, bbb], [Leo, aaa], 
  wwert : [Tom, eee], [Gogol, ddd],
```


#### Mapping options <div id="options"></div>

When registering a data member, you can specify one or more options that will customize the mapping.

##### Bounds <div id="options_bounds"></div>

Sets the range of values in which (including the limits of the range) the value to be set is located. Applicable for integer types and floating point types. The option accepts two parameters - the range limits. Throws an [exception](#exceptions) when the set during the mapping of the value goes out of bounds.

```cpp
Bounds{lower, upper}
```

Example of setting an option:

```cpp
reg(&Stage::engine_count, "engine_count", Bounds{1, 31});
```

##### Default <div id="options_default"></div>

Sets the default value for the data member. Applicable for bool, integer types, floating point types and strings. The option accepts one parameter - the default value.

```cpp
Default{default_value}
```

Example of setting an option:

```cpp
reg(&Stage::engine_count, "engine_count", Default{3});
```

##### NotEmpty <div id="options_not_empty"></div>

Notes that a data member cannot be set to an empty value. Applicable for strings. The option does not accept parameters. Throws an [exception](#exceptions) if, after completion of the mapping, the field value is an empty string.

Example of setting an option:

```cpp
reg(&Spacecraft::name, "name", NotEmpty{}));
```

##### Options example <div id="options_example"></div>

[example/options](/example/options/options.cpp)

```cpp
#include <iostream>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Stage {
 unsigned short engine_count;
 std::string fuel;
 long length;

 friend std::ostream & operator<<(std::ostream & os, const Stage & o) {
  os << " engine_count : " << o.engine_count << std::endl;
  os << " fuel         : " << o.fuel << std::endl;
  os << " length       : " << o.length << std::endl;

  return os;
 }
};

struct Spacecraft {
 bool in_development;
 std::string name;
 int mass;
 Stage first_stage;
 Stage second_stage;

 friend std::ostream & operator<<(std::ostream & os, const Spacecraft & o) {
  os << "in_development : " << std::boolalpha << o.in_development << std::endl;
  os << "name           : " << o.name << std::endl;
  os << "mass           : " << o.mass << std::endl << std::endl;
  os << "first stage: " << std::endl << o.first_stage << std::endl;
  os << "second stage: " << std::endl << o.second_stage << std::endl;

  return os;
 }
};

int main() {
 sm::reg(&Stage::engine_count, "engine_count", sm::Default{6}, sm::Bounds{1, 31});
 sm::reg(&Stage::fuel, "fuel", sm::Default{"subcooled"});
 sm::reg(&Stage::length, "length", sm::Default{50});

 sm::reg(&Spacecraft::in_development, "in_development", sm::Default{true});
 sm::reg(&Spacecraft::name, "name", sm::NotEmpty{});
 sm::reg(&Spacecraft::mass, "mass", sm::Default{5000000}, sm::Bounds{100000, 10000000});
 sm::reg(&Spacecraft::first_stage, "first_stage");
 sm::reg(&Spacecraft::second_stage, "second_stage");

 Spacecraft starship;

 std::istringstream json_data(R"json(
  {
   "name": "Vostok",
   "second_stage": {
     "engine_count": 31,
     "fuel": "compressed gas",
     "length": 70
   }
  }
 )json");

 sm::map_json_to_struct(starship, json_data);

 std::cout << starship << std::endl;
}
```

result

```cpp
in_development : true
name           : Vostok
mass           : 5000000

first stage: 
 engine_count : 6
 fuel         : subcooled
 length       : 50

second stage: 
 engine_count : 31
 fuel         : compressed gas
 length       : 70
```

### Reverse mapping of c ++ structure to json <div id="reverse_mapping_of_c_plus_plus_structure_to_json"></div>

For the structure to be mapped back to json, it is necessary to register all data members of all the structures that need to be mapped using for each field

```cpp
template<typename T, typename V, typename ... U, template<typename> typename ... Options>
inline void reg(V T::* ptr, std::string const & name, Options<U>&& ... options);
```

- `ptr` - pointer to data member
- `name` - member name
- `options` - [mapping options](#options)

and call the function

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

struct OceanPart {
 std::string name;
 double average_depth;
 std::vector<int> temperature;
};

struct OceanColor {
 std::string name;
};

struct Ocean {
 double water_volume;
 long long surface_area;
 bool liquid;
 std::string name;

 OceanColor color;

 std::vector<OceanPart> parts;
};

struct Planet {
 bool giant;
 long long surface_area;
 double mass;
 double volume;
 long long orbital_period;
 std::string name;
 bool terrestrial;
 std::string shape;

 Ocean ocean;
};

int main() {
 struct_mapping::reg(&OceanPart::name, "name");
 struct_mapping::reg(&OceanPart::average_depth, "average_depth");
 struct_mapping::reg(&OceanPart::temperature, "temperature");

 struct_mapping::reg(&OceanColor::name, "name");

 struct_mapping::reg(&Ocean::water_volume, "water_volume");
 struct_mapping::reg(&Ocean::surface_area, "surface_area");
 struct_mapping::reg(&Ocean::liquid, "liquid");
 struct_mapping::reg(&Ocean::name, "name");
 struct_mapping::reg(&Ocean::color, "color");
 struct_mapping::reg(&Ocean::parts, "parts");

 struct_mapping::reg(&Planet::giant, "giant");
 struct_mapping::reg(&Planet::surface_area, "surface_area");
 struct_mapping::reg(&Planet::mass, "mass");
 struct_mapping::reg(&Planet::volume, "volume");
 struct_mapping::reg(&Planet::orbital_period, "orbital_period");
 struct_mapping::reg(&Planet::name, "name");
 struct_mapping::reg(&Planet::terrestrial, "terrestrial");
 struct_mapping::reg(&Planet::shape, "shape");
 struct_mapping::reg(&Planet::ocean, "ocean");

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
 pacific.temperature = std::vector<int>{-3, 5, 12};

 OceanPart atlantic;
 atlantic.name = "Atlantic Ocean";
 atlantic.average_depth = 3.646;
 atlantic.temperature = std::vector<int>{-3, 0};

 earth.ocean.parts.push_back(pacific);
 earth.ocean.parts.push_back(atlantic);

 std::ostringstream json_data;
 struct_mapping::map_struct_to_json(earth, json_data, "  ");

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
        "average_depth": 4.28011,
        "temperature": [
          -3,
          5,
          12
        ]
      },
      {
        "name": "Atlantic Ocean",
        "average_depth": 3.646,
        "temperature": [
          -3,
          0
        ]
      }
    ]
  }
}
```

### Registration of data members combined with initialization <div id="registration_of_data_members_combined_with_initialization"></div>

In order not to take out the registration of data members from the structure, registration can be combined with initialization

[example/in_struct_reg](/example/in_struct_reg/in_struct_reg.cpp)

```cpp
#include <iostream>
#include <sstream>
#include <vector>

#include "struct_mapping/struct_mapping.h"

struct Planet {
 bool giant = [] {struct_mapping::reg(&Planet::giant, "giant"); return false;} ();
 long long surface_area = [] {struct_mapping::reg(&Planet::surface_area, "surface_area"); return 0;} ();
 double mass = [] {struct_mapping::reg(&Planet::mass, "mass"); return 0;} ();
 std::vector<std::string> satellites = [] {
  struct_mapping::reg(&Planet::satellites, "satellites"); return std::vector<std::string>{};} ();
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
```

To simplify the use of this method, three macros are defined

- BEGIN_STRUCT
- MEMBER
- END_STRUCT

#### BEGIN_STRUCT
Defines the begin of the structure and its name    

BEGIN_STRUCT(name)

```cpp
BEGIN_STRUCT(Planet)
```

#### MEMBER
Adds a data member, registers it, and initializes it with a default value:

MEMBER(type, name)

```cpp
MEMBER(bool, giant)
MEMBER(long long, surface_area)
MEMBER(double, mass)
MEMBER(std::vector<std::string>, satellites)
```

#### END_STRUCT
Defines the end of the structure

END_STRUCT

```cpp
END_STRUCT
```

[example/macro_reg](/example/macro_reg/macro_reg.cpp)

```cpp
#include <iostream>
#include <sstream>
#include <vector>

#include "struct_mapping/struct_mapping.h"

BEGIN_STRUCT(Planet)

MEMBER(bool, giant)
MEMBER(long long, surface_area)
MEMBER(double, mass)
MEMBER(std::vector<std::string>, satellites)

END_STRUCT

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
```

## Exceptions <div id="exceptions"></div>

StructMapping throws a `StructMappingException` exception during the mapping process

* when setting a value for an unregistered field (in json, the name of the value in the object does not correspond to any of the registered fields in the C ++ structure)
* when setting a value whose type does not match the type of field
* when setting a value that exceeds the limits set by the Bounds option
* with an empty string field, if the NotEmpty option was set for it
* when setting the Bounds option to a value that is outside the range of values for the field type
* when setting the Bounds option to values when the lower bound value is greater than the upper bound value
* when setting the Default option to a value that is outside the range of values for the field type
*	when reaching the end of the json stream, when parsing is not completed (the process of parsing an object, value, etc.)
* when a character is received in the json stream that is not valid at this position (for example, an array termination character, if the beginning character of the array was not received earlier)
* when conversion of json string representing number to number fails
