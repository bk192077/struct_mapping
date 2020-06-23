# StructMapping

![Release version](https://img.shields.io/badge/release-v0.3.0-blue.svg)

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

As types of member-data can be used

* bool
* char, unsigned char, short, unsigned short, int unsigned int, long, unsigned long, long long
* float, double
* std::string
* std::list
* std::vector
* std::map (the key can only be std::string)
* std::unordered_map (the key can only be std::string)
* std::multimap (the key can only be std::string)
* std::unordered_multimap (the key can only be std::string)
* c++ structure

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

### Mapping json to c ++ structure

To map json to a structure, it is necessary to register all data members of all structures that you want to mapped using for each field

```cpp
template<typename T, typename V>
inline void reg(V T::* ptr, std::string const & name);
```

- `ptr` - pointer to data member
- `name` - member name

and call the function

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

#### structure example

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

#### sequence  container example

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

#### associative container example

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

### Reverse mapping of c ++ structure to json

For the structure to be mapped back to json, it is necessary to register all data members of all the structures that need to be mapped using for each field

```cpp
template<typename T, typename V>
inline void reg(V T::* ptr, std::string const & name);
```

- `ptr` - pointer to data member
- `name` - member name

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

### Registration of data members combined with initialization

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

## Exceptions

StructMapping throws a `StructMappingException` exception during the mapping process

* when using a field with a nonexistent name for the structure (in json, the name of the value in the object does not correspond to any of the fields in the C ++ structure)
*	when reaching the end of the json stream, when parsing is not completed (the process of parsing an object, value, etc.)
* when a character is received in the json stream that is not valid at this position (for example, an array termination character, if the beginning character of the array was not received earlier)
* when conversion of json string representing number to number fails
