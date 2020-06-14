# StructMapping

![Release version](https://img.shields.io/badge/release-v0.2.0-blue.svg)

[документация на русском](/readme_ru.md)

English translation provided by [translate.google.com](https://translate.google.com)   

## Mapping data in json format on a c++ structure

Ideally, I would like to define a c++ structure

```cpp
struct Person {
 std::string name;
 int age;
 bool student;
} person;
```

pass person instance to mapping method along with json_data

```cpp
map_json_to_struct(person, json_data)
```

then just use the filled structure

```cpp
std::cout << person.name << " : " << person.age;
```

StructMapping is trying to solve this problem. To provide a scenario as close as possible to the above, StructMapping requires the developer to define the structure fields in a special way.

## Compatibility

Compilation is required with -std=c++17 Mainly for:
* if constexpr
* static inline

Compiler / platform combinations on which StructMapping has been tested:

* GNU C++ 10.1.0 на Linux
* Clang 9 на Linux

## Installation

StructMapping is a header-only C++ library. All library files are in the `include` folder.

To build examples and run tests proceed with the steps below:

1. create directory called `build` in StructMapping source directory
2. change to `build` directory
3. run `cmake ..` command to configure your build
4. run `cmake --build .` command. On successful build you will find compiled test and example binaries in `bin` directory
5. to run the tests run `ctest` (you can get detailed output using `ctest -V`)
6. it is possible to install library system-wide by running `cmake --install .` command from the build  tree with administrative privileges. This will install all files according to system preferences.

## Usage

**managed structure** - structure defined using MANAGED macros   
**managed array** - array defined using MANAGED macros

#### Implementing a scenario with a Person structure

[example/person](/example/person/person.cpp)

define the structure

```cpp
#define MANAGED_STRUCT_NAME Person // define a macro that sets the name of the structure
BEGIN_MANAGED_STRUCT               // define the beginning of the structure

MANAGED_FIELD(std::string, name)   // define a field with type 'std::string' and name 'name'
MANAGED_FIELD(int, age)            // define a field with type 'int' and name 'age'
MANAGED_FIELD(bool, student)       // define a field with type 'bool' and name 'student'

END_MANAGED_STRUCT                 // define the end of the structure
#undef MANAGED_STRUCT_NAME         // undef the macro that specified the name of the structure so
                                   // that there are no warnings on overriding the macro in the future
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
struct_mapping::mapper::map_json_to_struct(person, json_data);
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

#define MANAGED_STRUCT_NAME Person // define a macro that sets the name of the structure
BEGIN_MANAGED_STRUCT               // define the beginning of the structure

MANAGED_FIELD(std::string, name)   // define a field with type 'std::string' and name 'name'
MANAGED_FIELD(int, age)            // define a field with type 'int' and name 'age'
MANAGED_FIELD(bool, student)       // define a field with type 'bool' and name 'student'

END_MANAGED_STRUCT                 // define the end of the structure
#undef MANAGED_STRUCT_NAME         // undef the macro that specified the name of the structure so
                                   // that there are no warnings on overriding the macro in the future

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

#### Simple types

[example/simple](/example/simple/simple.cpp)

fields with simple types are set by a macro `MANAGED_FIELD(field type, field name)`

field type can be one of the following:
* bool
* integral types (char, int, ...)
* floating point types (float, double)
* std::string 

```cpp
MANAGED_FIELD(bool, ready)
MANAGED_FIELD(int, size)
MANAGED_FIELD(double, speed)
MANAGED_FIELD(std::string, name)
```

#### Structures

[example/struct](/example/struct/struct.cpp)

field with structure type is set by macro `MANAGED_FIELD_STRUCT(тип поля, имя поля)` The field type here should be a managed structure. For example, in the Earth structure, the `president` field is of the `President` type, which you define earlier.

```cpp
#define MANAGED_STRUCT_NAME President <-- define the structure President
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, mass)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

#define MANAGED_STRUCT_NAME Earth
BEGIN_MANAGED_STRUCT

MANAGED_FIELD_STRUCT(President, president) <-- define a field with type President

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME
```

#### Arrays

[example/array](/example/array/array.cpp)

field in the form of an array is set by a macro `MANAGED_FIELD_ARRAY(array element type, field name)`

```cpp
MANAGED_FIELD_ARRAY(std::string, friends)
```

item type can be:
- simple type
- array (ManagedArray)
- structure

real field type becomes `struct_mapping::managed::ManagedArray<item type>` Inside ManagedArray is std::vector, which will contain the values of the array. Reference to this vector can be obtained through the method `std::vector<T> & ManagedArray::get_data()`

```cpp
mib.friends.get_data()[13] // rray element at index thirteen
```

if you need an array whose elements are also arrays, you must use the same macro `MANAGED_FIELD_ARRAY` for the field, but the type of elements must be specified through the macro` MANAGED_ARRAY`

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), alien_groups)
```

this macro expands to

```cpp
struct_mapping::managed::ManagedArray<struct_mapping::managed::ManagedArray<std::string>> alien_groups
```

access to elements should take into account the nesting of vectors

```cpp
mib.alien_groups.get_data()[13].get_data()[42] // array element at index forty two in an array
                                               // at index thirteen
```

array dimension can be increased

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(MANAGED_ARRAY(std::string)), planet_groups)
```

#### Reverse mapping of c ++ structure on json data

[example/struct_to_json](/example/struct_to_json/struct_to_json.cpp)

pass an instance of the managed structure to the mapping method along with the output json data stream

```cpp
std::ostringstream json_data;
struct_mapping::mapper::map_struct_to_json(earth, json_data);
```

as a result, data of the form

```cpp
{"giant":false,"surface_area":510072000,"mass":5.97237e+24,"volume":1.08321e+12,"orbital_period":31536000,"name":"Terra","terrestrial":true,"shape":"nearly spherical","ocean":{"water_volume":1.332e+09,"surface_area":361132000,"liquid":true,"name":"World Ocean","color":{"name":"blue"},"parts":[{"name":"Pacific Ocean","average_depth":4.28011},{"name":"Atlantic Ocean","average_depth":3.646}]}}
```

the output format can be made more readable using the third parameter `map_struct_to_json`, which sets the indent. When indenting (parameter takes a string)

```cpp
std::ostringstream json_data;
struct_mapping::mapper::map_struct_to_json(earth, json_data, "  ");
```

as a result, data of the form

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

## How it works

Each managed structure has a variable (use_name) that stores the name of the field used. If use_name is not empty, then it stores the name of the field to which events from the parser will be broadcast. Initially, use_name is empty (no fields are used).

* if parsing encounters the beginning of a json object or json array, then:
	* if use_name is empty, then the name of the field whose parsing was started is placed in it
	* if use_name is not empty, then the event is broadcast to the field whose name is contained in use_name
* if during parsing the end of json object or json array is encountered, then:
	* if use_name is empty nothing happen
	* if use_name is not empty, then the event is broadcast to the field whose name is contained in use_name. If after broadcasting the event a sign of the end of the use chain is received, then use_name is cleared
* if parsing sets a value, then:
	* if use_name is empty, then the value is set for the field of the current instance of the structure by the name of this field (and in the case of an array, the value is added to the array)	
	* if use_name is not empty, then the event is broadcast to the field whose name is contained in use_name

The main task is to map data in json format to a c++ structure. A c++ structure is a collection of fields. Each field has a name and contains a value of a specific type. Therefore, json objects are mapped to a c++ structure. In a c++ structure, field types correspond to json value types and can be as follows:
* bool - stores json true or false
* integral or floating point - stores json number
* std::string - stores json string
* managed structure - stores json object
* managed array - stores the json array

To solve the task, SturctMapping uses:
* set of Fs_ classes
* managed structures
* parser json
* map_json_to_struct function

### set of Fs_ classes

SturctMapping contains a set of identical template classes that differ only in names:
* Fs_set_field
* Fs_set
* Fs_use
* Fs_release

Each Fs_ class is designed to set and get by the string name of a functor, the type of which is specified by the template parameter

```cpp
template<typename F>
class Fs_set_field {
public:
 static void add(std::string const & name, F f) {
  if (fs.find(name) == fs.end()) fs[name] = f;
 }

 static inline std::unordered_map<std::string, F> fs;
};
```

All instances of Fs_ classes can be conditionally divided into sets in each of which Fs_ instances of the same type of managed structure are assembled. The type of managed structure is defined by the first parameter of the function that the Fs_ instance stores. For example, the following code

```cpp
Fs_set_field<std::function<void(Person&, bool)>>
```

refers to an instance of Fs_, which stores functions of type `Person` (in this example, only functions designed to set fields of a logical type)

### Managed Structures

The definition of a managed structure consists of three parts: prologue, definition of fields, and epilogue


#### Prologue

The prolog consists of setting the structure name through the definition of the macro `MANAGED_STRUCT_NAME` and using the macro` BEGIN_MANAGED_STRUCT`. The macro `BEGIN_MANAGED_STRUCT` expands to

```cpp
struct имя_структуры {
 void set(std::string const &, bool) {...}
 void set(std::string const &, std::string const &) {...}
 void set(std::string const &, long long) {...}
 void set(std::string const &, double) {...}
 void use(std::string const &) {...}
 bool release() {...}
```

set functions are used to set values of a managed structure by the field name. The first parameter is the name of the field, and the second is the value. Overloaded by the type of set value for the boolean type, string, integer and floating-point number. The use and release functions are discussed later.

#### Field Definition

Structure fields are divided into three types:
* fields of simple types (boolean, integer, floating point and strings)
* fields with type of managed structure
* fields with type of managed array

##### Simple type fields

a simple type field is define by the `MANAGED_FIELD` macro, which is passed the field name and field type. The `MANAGED_FIELD` macro expands to

```cpp
 тип_поля имя_поля = [] {
  ...
 } ();
```

lambda is called when the field is initialized and returns the default value for the field. Before returning the value to Fs_set_field, std::function is added with a lambda that will set the value of this field for the structure that is currently defined. For example, when defining a `Person` field of a logical type named` name`

```cpp
 Fs_set_field<std::function<void(Person&, bool)>>::add(
 "name",
 [] (Person &, bool) {
  ...
 });
```

##### Fields of managed structure type

a managed structure type field is specified by the `MANAGED_FIELD_STRUCT` macro, which receives the field name and field type. The `MANAGED_FIELD_STRUCT` macro expands to

```cpp
 тип_поля имя_поля = [] {
  ...
 } ();
```

lambda is called when the field is initialized and returns the default value for the field. Before returning the values to Fs_set, Fs_use and Fs_release, std::function with a lambda is added, each of which simply calls the set, use, or release method for the structure passed to it, respectively.

##### Managed array type fields

To define arrays, two macros `MANAGED_ARRAY` and` MANAGED_FIELD_ARRAY` are defined in StructMapping.
The `MANAGED_ARRAY` macro, to which the type of the element of the array is transmitted, is introduced only to support a single style and is expanded simply

```cpp
struct_mapping::mapper::ManagedArray<array element type>
```

A managed array type field is specified by the `MANAGED_FIELD_ARRAY` macro, to which the field name and array element type are passed. The `MANAGED_FIELD_ARRAY` macro expands to

```cpp
MANAGED_FIELD_STRUCT(struct_mapping::mapper::ManagedArray<array element type>, field name)
```

those. Defines a field with the type of managed structure. Respectively, being a managed structure, ManagedArray has set, use, and release methods.

#### Epilogue

The epilogue consists of using the macro `END_MANAGED_STRUCT`, which expands simply to

```cpp
};
```

and deleting the current macro definition that set the structure name (without this action, when defining the next structure, there will be warnings about redefining the macro `MANAGED_STRUCT_NAME`)

### Parser json

When creating an instance of the parser, several callback functions are passed to it in the constructor, which are divided into three types:
1. setting the value (a separate function for each of the types: logical, integer, floating-point and string)
2. start and end structure (one function to start, the second function to end)
3. start and end array (one function to start, the second function to end)

the parser will call these functions during the work. A total of eight functions are transferred:

* set_bool with signature `void (std::string const & name, bool value)`
* set_integral with signature `void (std::string const & name, long long value)`
* set_floating_point with signature `void (std::string const & name, double value)`
* set_string with signature `void (std::string const & name, std::string const & value)`
* start_struct with signature `void (std::string const & name)`
* end_struct with signature `void ()`
* start_array with signature `void (std::string const & name)`
* end_array with signature `void ()`

#### set_bool

called upon completion of parsing:

* name/value pairs of json object set to true or false

```cpp
{
 ...
 "ready": true
 ...
}
```

in this case, the name and value are transferred in the call: `set_bool("ready", true)`

* json array values when the value is true or false

```cpp
[
 ...
 true
 ...
]
```

in this case, an empty name and values are transferred in the call: `set_bool("", true)`

#### set_integral

called upon completion of parsing:

* name/value pairs of json object with value integer

```cpp
{
 ...
 "age": 42
 ...
}
```

in this case, the name and value are transferred in the call: `set_integral("age", 42)`

* json array values when the value is an integer

```cpp
[
 ...
 2020
 ...
]
```

in this case, an empty name and values are transferred in the call: `set_integral("", 2020)`

#### set_floating_point

called upon completion of parsing:

* json object name / value pairs of floating point value

```cpp
{
 ...
 "mass": 3.14159
 ...
}
```

in this case, the name and value are transferred in the call: `set_floating_point("mass", 3.14159)`

* json array values when the value is a float

```cpp
[
 ...
 9.81
 ...
]
```

in this case, an empty name and values are transferred in the call: `set_floating_point("", 9.81)`

#### set_string

called upon completion of parsing:

* name/value pairs of json object with a value string

```cpp
{
 ...
 "name": "Agent K"
 ...
}
```

in this case, the name and value are transferred in the call: `set_string("name", "Agent K")`

* json array values when the value is a string

```cpp
[
 ...
 "Griffin"
 ...
]
```

in this case, an empty name and values are transferred in the call: `set_string("", "Griffin")`

#### start_struct

It is called when determining the beginning of the object (the symbol `'{'`). In this case, the call is transmitted:

* name: `start_struct("planet")`, if the object is the value of a name/value pair

```cpp
{
 ...
 "planet": {
 ...
}
```

* empty name: `start_struct("")`, if the object is an array value

```cpp
[
 ...
 {
 ...
]
```

#### end_struct

called when determining the end of the object (character `'}'`): `end_struct("")`

#### start_array

called when determining the beginning of the array (character `'['`). In this case, the call is transmitted:

* name: `start_array("friends")`, if the array is the value of a name/value pair

```cpp
{
 ...
 "friends": [
 ...
}
```

* empty name: `start_array("")`, if the array is an array value

```cpp
[
 ...
 [
 ...
]
```

#### end_array

called when determining the end of the array (character `']'`): `end_array("")`

### map_json_to_struct function

map_json_to_struct is the link between the parser and the managed structure onto which json data is mapped. Signature map_json_to_struct:

```cpp
template<typename T>
void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data)
```

The first parameter is a reference to the managed structure to which json data will be displayed. The second parameter is a reference to the json data stream.

map_json_to_struct performs two operations:
1. creates an instance of the parser, passing it to the constructor a set of functions that the parser will call during operation:

```cpp
struct_mapping::parser::Json jp(
 set_bool,
 set_integral,
 set_floating_point,
 set_string,
 start_struct,
 end_struct,
 start_array,
 end_array);
```

2. starts the process by calling the parser method `parse`

```cpp
 jp.parse(&json_data);
```

each of the functions passed to the parser simply passes the call to the managed structure. For example, `set_bool` is defined as

```cpp
auto set_bool = [&result_struct] (std::string const & name, bool value) {
 result_struct.set(name, value);
};
```

### parsing StructMapping on the example of how_it_works

[example/how_it_works](/example/how_it_works/how_it_works.cpp)

```cpp
#define MANAGED_STRUCT_NAME Author
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

#define MANAGED_STRUCT_NAME Book
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(int, price)
MANAGED_FIELD_STRUCT(Author, author)
MANAGED_FIELD_ARRAY(std::string, chapters)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

int main() {
 Book white_space;

 std::istringstream json_data(R"json(
 {
  "price": 273,
  "author": {
   "name": "bk192077"
  },
  "chapters": [
   "launch",
   "new horizons"
  ]
 }
 )json");

 struct_mapping::mapper::map_json_to_struct(white_space, json_data);
}
```

#### in compile time

code

```cpp
#define MANAGED_STRUCT_NAME Author
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME
```

defines the structure

```cpp
struct Author {
 void set(std::string const &, bool) {...}
 void set(std::string const &, std::string &) {...}
 void set(std::string const &, long long) {...}
 void set(std::string const &, double) {...}
 void use(std::string const &) {...}
 bool release() {...}

 std::string name;
};
```

the `name` field will be initialized with an empty string. Prior to this initialization, a function for setting the value for this field will be added to the instance of the Fs_set_field class.

```cpp
Fs_set_field<std::function<void(Author &, std::string const &)>>::add(
 "name",
 [] (Author & o, std::string cont & value) {
  o.name = value;
 });
```

code

```cpp
#define MANAGED_STRUCT_NAME Book
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(int, price)
MANAGED_FIELD_STRUCT(Author, author)
MANAGED_FIELD_ARRAY(std::string, chapters)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME
```

defines the structure

```cpp
struct Book {
 void set(std::string const &, bool) {...}
 void set(std::string const &, std::string &) {...}
 void set(std::string const &, long long) {...}
 void set(std::string const &, double) {...}
 void use(std::string const &) {...}
 bool release() {...}

 int price;
 Author author;
 ManagedArray<std::string> chapters;
};
```

the `price` field will be initialized to zero. Prior to this initialization, a function for setting the value for this field will be added to the instance of the Fs_set_field class.

```cpp
Fs_set_field<std::function<void(Book &, long long)>>::add(
 "price",
 [] (Book & o, long long value) {
  o.price = static_cast<int>(value);
 });
```

the `author` field will be initialized to Author by default. Prior to this initialization, functions will be added to instances of Fs_ classes:

```cpp
Fs_set<std::function<void(Book &, std::string const &, bool)>>::add(
 "author",
 [] (Book & o, std::string const & field_name, bool value) {
  o.author.set(field_name, value);
 });

Fs_set<std::function<void(Book &, std::string const &, double)>>::add(
 "author",
 [] (Book & o, std::string const & field_name, double value) {
  o.author.set(field_name, value);
 });

Fs_set<std::function<void(Book &, std::string const &, long long)>>::add(
 "author",
 [] (Book & o, std::string const & field_name, long long value) {
  o.author.set(field_name, value);
 });

Fs_set<std::function<void(Book &, std::string const &, std::string cont &)>>::add(
 "author",
 [] (Book & o, std::string const & field_name, std::string cont & value) {
  o.author.set(field_name, value);
 });

Fs_use<std::function<void(Book &, std::string const &)>>::add(
 "author",
 [] (Book & o, std::string const & name) {
  o.author.use(name);
 });

Fs_release<std::function<bool(Book &)>>::add(
 "author",
 [] (Book & o) {
  return o.author.release();
 });
```

actions with the `chapters` field will be similar to actions with the` author` field

#### in run time

*(when compiling with the `STRUCT_MAPPING_DEBUG` option enabled, the sequence of calls will be visible)*

the call to map_json_to_struct starts the parsing procedure, during which the following actions are performed (map_json_to_struct actually just translates the calls to the managed structure, so its actions are not considered):

| parser                          | managed |
|:--------------------------------|:--------|
| start_struct("")                | this is the beginning of the Book structure itself, so map_json_to_struct does not translate this call and it is simply ignored |
| set_integral("price", 273)      | broadcast to white_space : `white_space.set("price", 273)` |
|                                 | setting the value of the price field for white_space : `Fs_set_field<std::function<void(Book&, long long)>>::fs["price"](white_space, 273)` |
| start_struct("author")          | broadcast to white_space (after that, all calls to white_space will be translated to the author field) : `white_space.use("author")` |
| set_string("name", "bk192077")  | broadcast to white_space : `white_space.set("name", "bk192077")` |
|                                 | broadcast to author (calling set method on author) : `Fs_set<std::function<void(Book, std::string const &, bool)>>::fs["author"](white_space, "name", "bk192077")` |
|                                 | setting the value of the name field to author : `Fs_set_field<std::function<void(Author&, std::string const &)>>::fs["name"](author, "bk192077")` |
| end_struct()                    | broadcast to white_space : `white_space.release()` |
|                                 | broadcast to author (calling release method on author) : `Fs_release<std::function<bool(Book&)>>::fs["author"](white_space))` |
|                                 | after this, calls to white_space will no longer be broadcast to author |
| start_array("chapters")         | broadcast to white_space (after that all calls white_space will broadcast the chapters field) : `white_space.use("chapters")` |
| set_string("", "launch")        | broadcast to white_space : `white_space.set("", "launch")` |
|                                 | broadcast to chapters (chapters set method call) : `Fs_set<std::function<void(Book, std::string const &, bool)>>::fs["chapters"](white_space, "", "launch")` |
|                                 | adding "launch" element to the array |
| set_string("", "new horizons")  | broadcast to white_space : `white_space.set("", "new horizons")` |
|                                 | broadcast to chapters (chapters set method call) : `Fs_set<std::function<void(Book, std::string const &, bool)>>::fs["chapters"](white_space, "", "new horizons")` |
|                                 | adding "new horizons" element to the array |
| end_array()                     | broadcast to white_space : `white_space.release()` |
|                                 | broadcast to chapters (calling release method on chapters) : `Fs_release<std::function<bool(Book&)>>::fs["chapters"](white_space))` |
|                                 | after this, calls to white_space will no longer be broadcast to chapters |
| end_struct()                    | this is the end of the Book structure itself, so map_json_to_struct does not translate this call and it is simply ignored |


## Exceptions thrown

StructMapping throws a single type exception `StructMappingException`, that inherits from std::runtime_error

Exception thrown:

* set methods of the managed structure - when trying to set the value of a nonexistent field (there is no combination of the name and type of the field for which an attempt is made to set the value)
* managed method use method - when trying to execute this function for a nonexistent field (there is no field with a name for which the use function is called)
* managed array set method - when trying to set an invalid type value
* json parser when:
	*	reaching the end of the data stream when parsing is not completed (the process of parsing an object, value, etc.)
	* a character is received in the data stream that is not allowed at this position (for example, the termination character of the array, if the beginning character of the array was not received earlier)
	* when converting a string representing a number to a number error

After an exception, the state of the managed structure is incomplete and cannot be used.
