# StructMapping

![Release version](https://img.shields.io/badge/release-v0.5.0-blue.svg)

[english documentation](/readme.md)

### Содержание
- [Введение](#introduction)
- [Совместимость](#compatibility)
- [Установка](#installation)
- [Использование](#usage)
	- [Реализация сценария со структурой Person](#implementing_a_scenario_with_a_Person_structure)
	- [Отображение json на структуру c++](#mapping_json_to_c_plus_plus_structure)
		- [Перечисления](#mapping_json_to_c_plus_plus_structure_enumeration)
		- [Структуры, представленные в json в виде строк](#mapping_json_to_c_plus_plus_structure_class_to_from_string)
		- [Пример использования простых типов](#simple_types_example)
		- [Пример использования структур](#structure_example)
		- [Пример использования структур, представленных в json в виде строк](#structure_example_class_to_from_string)
		- [Пример использования перечислений](#enumeration_example)
		- [Пример использования последовательных контейнеров](#sequence_container_example)
		- [Пример использования ассоциативных контейнеров](#associative_container_example)
		- [Опции отображения](#options)
			- [Bounds](#options_bounds)
			- [Default](#options_default)
			- [NotEmpty](#options_not_empty)
			- [Required](#options_required)
			- [Пример использования опций](#options_example)
	- [Обратное отображение структуры c++ на json](#reverse_mapping_of_c_plus_plus_structure_to_json)
	- [Регистрация полей, совмещенная с инициализацией](#registration_of_data_members_combined_with_initialization)
- [Генерируемые исключения](#exceptions)

## Отображение json на структуру c++ и обратно <div id="introduction"></div>

Хотелось бы определить структуру с++

```cpp
struct Person {
 std::string name;
 int age;
 bool student;
} person;
```

передать экземпляр person в метод отображения вместе с json данными

```cpp
map_json_to_struct(person, json_data)
```

после чего пользоваться заполненной структурой

```cpp
std::cout << person.name << " : " << person.age;
```

Или наоборот

```cpp
map_struct_to_json(person, json_data, "  ");
std::cout << json_data.str() << std::endl;
```

получить Person в виде json

```cpp
{
 "name": "Agent K",
 "age": 42,
 "student": false
}
```

StructMapping пытается решить эти задачи

## Совместимость <div id="compatibility"></div>

Требуется компиляция с -std=c++17 В основном для:

* if constexpr
* static inline

Комбинации компилятор | платформа, на которых была протестирована StructMapping:

* GNU C++ 10.1.0 | Linux
* Visual C++ 2019 and Microsoft (R) C/C++ Optimizing Compiler Version 19.26.28806 for x64 | Windows 64-bit (кроме тестов)

В качестве типов полей могут быть использованы:

* bool
* char, unsigned char, short, unsigned short, int unsigned int, long, long long
* float, double
* std::string
* std::list
* std::vector
* std::set (ожидается, что в json будет представлен массивом)
* std::unordered_set (ожидается, что в json будет представлен массивом)
* std::multiset (ожидается, что в json будет представлен массивом)
* std::unordered_multiset (ожидается, что в json будет представлен массивом)
* std::map (ключем может быть только std::string)
* std::unordered_map (ключем может быть только std::string)
* std::multimap (ключем может быть только std::string)
* std::unordered_multimap (ключем может быть только std::string)
* структуры с++
* перечисления

## Установка <div id="installation"></div>

StructMapping - это библиотека включающая только заголовочные файлы. Все файлы библиотеки находятся в каталоге `include`

Для сборки примеров и запуска тестов выполните следующие действия (требуется [cmake](https://cmake.org/download/)):

1. (при необходимости) установите переменные окружения CC и CXX:
* `export CC=/usr/bin/gcc`
* `export CXX=/usr/bin/g++`
2. создайте каталог `build` внутри каталога StructMapping
3. перейдите в каталог `build`
4. выполните команду `cmake ..` чтобы настроить сборку
5. выполните команду `cmake --build .` При успешной сборке вы найдете бинарные файлы примеров и тестов (под windows тесты не собираются) в каталоге `bin`
6. (не для windows) для запуска тестов выполните команду `ctest` (вы можете получить детальный вывод используя команду `ctest -V`)
7. для установки библиотеки можно выполнить команду `cmake --install .` с административными привилегиями

## Использование <div id="usage"></div>

### Реализация сценария со структурой Person <div id="implementing_a_scenario_with_a_Person_structure"></div>

[example/person](/example/person/person.cpp)

определяем структуру

```cpp
struct Person {
 std::string name;
 int age;
 bool student;
};
```

регистрируем поля

```cpp
struct_mapping::reg(&Person::name, "name");
struct_mapping::reg(&Person::age, "age");
struct_mapping::reg(&Person::student, "student");
```

создаем экземпляр

```cpp
Person person;
```

задаем json данные

```cpp
std::istringstream json_data(R"json(
{
 "name": "Jeebs",
 "age": 42,
 "student": true
}
)json");
```

передаем экземпляр person в метод отображения вместе с данными json

```cpp
struct_mapping::map_json_to_struct(person, json_data);
```

пользуемся

```cpp
std::cout <<
 person.name << " : " <<
 person.age << " : " <<
 std::boolalpha << person.student << std::endl;
```

Полностью код выглядит так

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

результат

```cpp
Jeebs : 42 : true
```

### Отображение json на структуру c++ <div id="mapping_json_to_c_plus_plus_structure"></div>

Для отображения json на структуру необходимо зарегистрировать все поля всех структур, которые требуется отображать, используя для каждого поля функцию

```cpp
template<typename T, typename V, typename ... U, template<typename> typename ... Options>
inline void reg(V T::* ptr, std::string const & name, Options<U>&& ... options);
```

- `ptr` - указатель на поле
- `name` - имя поля
- `options` - [опции отображения](#options)

и вызвать функцию

```cpp
template<typename T>
inline void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data);
```

- `result_struct` - ссылка на результирующую структуру
- `json_data` - ссылка на входной поток json данных

В процессе отображения проверяется соответствие типов полей типам устанавливаемого значения и (для чисел) устанавливаемое значение проверяется на выход из диапазона значений типа поля. При несоответствии типов или выхода значения за границы диапазона генерируются [исключения](#exceptions).

#### Перечисления <div id="mapping_json_to_c_plus_plus_structure_enumeration"></div>

Перечисления в json будут представляться в виде строк. Поэтому для использования перечислений требуется установить методы преобразования из строки в значение перечисления и наоборот, используя:

```cpp
template<typename From, typename To>
static void MemberString::set(From function_from_string_, To function_to_string_);
```

- `function_from_string_` - функция преобразования из строки в значение перечисления
- `function_to_string_` - функция преобразования из значения перечисления в строку

например

```cpp
enum class Color {
 red,
 blue,
 green,
};

struct_mapping::MemberString<Color>::set(
 [] (const std::string & value) {
  if (value == "red") return Color::red;
  if (value == "green") return Color::green;
  if (value == "blue") return Color::blue;

  throw struct_mapping::StructMappingException("bad convert '" + value + "' to Color");
 },
 [] (Color value) {
  switch (value) {
  case Color::red: return "red";
  case Color::green: return "green";
  default: return "blue";
  }
 });
```

или в разделе [пример использования перечислений](#enumeration_example)

#### Структуры, представленные в json в виде строк <div id="mapping_json_to_c_plus_plus_structure_class_to_from_string"></div>

Структуры в json могут быть представлены в виде строк. Для использования этого способа требуется установить методы преобразования из строки в структуру и наоборот, используя:

```cpp
template<typename From, typename To>
static void MemberString::set(From function_from_string_, To function_to_string_);
```

- `function_from_string_` - функция преобразования из строки в структуру
- `function_to_string_` - функция преобразования из структуры в строку

например

```cpp
struct Color {
 int value;
};

struct_mapping::MemberString<Color>::set(
 [] (const std::string & value) {
  if (value == "red") return Color{1};
  if (value == "blue") return Color{2};

  throw struct_mapping::StructMappingException("bad convert '" + value + "' to Color");
 },
 [] (Color color) {
  switch (color.value) {
  case 1: return "red";
  case 2: return "blue";
  default: return "green";
  }
 }
 });
```

или в разделе [пример использования структур, представленных в json в виде строк](#structure_example_class_to_from_string)

#### пример использования простых типов <div id="simple_types_example"></div>

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

результат

```cpp
earth
 giant        : false
 surface_area : 510072000000000
 mass         : 5.97237e+24
 satellite    : Moon
```

#### пример использования структур <div id="structure_example"></div>

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

результат

```cpp
earth.president:
 name : Agent K
 mass : 75.6
```

#### пример использования структур, представленных в json в виде строк <div id="structure_example_class_to_from_string"></div>

[example/struct_from_string](/example/struct_from_string/struct_from_string.cpp)

```cpp
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Color {
 int value;

 bool operator<(const Color & o) const {
  return value < o.value;
 }
};

Color color_from_string(const std::string & value) {
 if (value == "red") return Color{1};
 if (value == "blue") return Color{2};

 return Color{0};
}

std::string color_to_string(const Color & color) {
 switch (color.value) {
 case 1: return "red";
 case 2: return "blue";
 default: return "green";
 }
}

struct Background {
 Color color;
};

struct Palette {
 Color main_color;
 Background background;
 std::list<Color> special_colors;
 std::set<Color> old_colors;
 std::map<std::string, Color> new_colors;

 friend std::ostream & operator<<(std::ostream & os, const Palette & o) {
  os << "main_color         : " << color_to_string(o.main_color) << std::endl;
  os << "background.color   : " << color_to_string(o.background.color) << std::endl;
  os << "special_colors     : ";
  for (auto color : o.special_colors) os << color_to_string(color) << ", ";
  os << std::endl << "old_colors         : ";
  for (auto color : o.old_colors) os << color_to_string(color) << ", ";
  os << std::endl << "new_colors         : ";
  for (auto [name, color] : o.new_colors) os << "[" << name << ", " << color_to_string(color) << "], ";
  os << std::endl;

  return os;
 }
};

int main() {
 sm::MemberString<Color>::set(color_from_string, color_to_string);

 sm::reg(&Palette::main_color, "main_color", sm::Default{"red"});
 sm::reg(&Palette::background, "background", sm::Required{});
 sm::reg(&Palette::special_colors, "special_colors");
 sm::reg(&Palette::old_colors, "old_colors");
 sm::reg(&Palette::new_colors, "new_colors");

 sm::reg(&Background::color, "color");

 Palette palette;

 std::istringstream json_data(R"json(
 {
  "background": {
   "color": "blue"
  },
  "special_colors": ["red", "green", "red", "blue"],
  "old_colors": ["red", "green", "blue"],
  "new_colors": {
   "dark": "green",
   "light": "red",
   "neutral": "blue"
  }
 }
 )json");

 sm::map_json_to_struct(palette, json_data);

 std::cout << palette << std::endl;
}
```

результат

```cpp
main_color         : red
background.color   : blue
special_colors     : red, green, red, blue, 
old_colors         : green, red, blue, 
new_colors         : [dark, green], [light, red], [neutral, blue],
```

#### пример использования перечислений <div id="enumeration_example"></div>

[example/enumeration](/example/enumeration/enumeration.cpp)

```cpp
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

enum class Color {
 red,
 blue,
 green,
};

Color color_from_string(const std::string & value) {
 if (value == "red") return Color::red;
 if (value == "blue") return Color::blue;

 return Color::green;
}

std::string color_to_string(Color color) {
 switch (color) {
 case Color::red: return "red";
 case Color::green: return "green";
 default: return "blue";
 }
}

struct Palette {
 Color main_color;
 Color background_color;
 std::list<Color> special_colors;
 std::map<std::string, Color> colors;

 friend std::ostream & operator<<(std::ostream & os, const Palette & o) {
  os << "main_color       : " << color_to_string(o.main_color) << std::endl;
  os << "background_color : " << color_to_string(o.background_color) << std::endl;
  os << "special_colors   : ";
  for (auto color : o.special_colors) os << color_to_string(color) << ", ";
  os << std::endl << "colors           : ";
  for (auto [name, color] : o.colors) os << "[" << name << ", " << color_to_string(color) << "], ";
  os << std::endl;

  return os;
 }
};

int main() {
 sm::MemberString<Color>::set(color_from_string, color_to_string);

 sm::reg(&Palette::main_color, "main_color", sm::Required{});
 sm::reg(&Palette::background_color, "background_color", sm::Default{Color::blue});
 sm::reg(&Palette::special_colors, "special_colors");
 sm::reg(&Palette::colors, "colors");

 Palette palette;

 std::istringstream json_data(R"json(
 {
  "main_color": "green",
  "special_colors": ["green", "green", "red"],
  "colors": {
   "dark": "green",
   "light": "red",
   "neutral": "blue"
  }
 }
 )json");

 sm::map_json_to_struct(palette, json_data);

 std::cout << palette << std::endl;
}
```

результат

```cpp
main_color       : green
background_color : blue
special_colors   : green, green, red, 
colors           : [dark, green], [light, red], [neutral, blue],
```

#### пример использования последовательных контейнеров <div id="sequence_container_example"></div>

[example/array_like](/example/array_like/array_like.cpp)

```cpp
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "struct_mapping/struct_mapping.h"

struct Friend {
 std::string name;
 std::set<int> counters;

 bool operator==(const Friend & o) const {
  return name == o.name;
 }
};

struct Friend_hash {
 size_t operator()(const Friend & o) const {
  return static_cast<size_t>(o.name.size());
 }
};

struct MiB {
 std::unordered_set<Friend, Friend_hash> friends;
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

результат

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

#### пример использования ассоциативных контейнеров <div id="associative_container_example"></div>

[example/map_like](/example/map_like/map_like.cpp)

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

результат

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

#### Опции отображения <div id="options"></div>

При регистрации поля можно указывать одну или несколько опций, которые будут настраивать отображение.

##### Bounds <div id="options_bounds"></div>

Устанавливает диапазон значений, в котором (включая границы диапазона) должно находится устанавливаемое значение. Применима для целочисленных типов и типов с плавающей точкой. Опция принимает два параметра - границы диапазона. Генерирует [исключение](#exceptions) при выходе устанавливаемого в процессе отображения значения за границы.

```cpp
Bounds{нижняя граница, верхняя граница}
```

Пример задания опции:

```cpp
reg(&Stage::engine_count, "engine_count", Bounds{1, 31});
```

##### Default <div id="options_default"></div>

Устанавливает значение по умолчанию для поля. Применима для bool, целочисленных типов, типов с плавающей точкой, строк, контейнеров, структур с++ и перечислений. Опция принимает один параметр - значение по умолчанию.

```cpp
Default{значение по умолчанию}
```

Пример задания опции:

```cpp
reg(&Stage::engine_count, "engine_count", Default{3});
```

При использовании опции для структуры, для которой используется преобразование в/из строки ([структуры, представленные в json в виде строк](#mapping_json_to_c_plus_plus_structure_class_to_from_string)), значение по умолчанию так же должно быть строкой

```cpp
sm::reg(&Palette::main_color, "main_color", sm::Default{"red"});
```

##### NotEmpty <div id="options_not_empty"></div>

Отмечает, что для поля не может быть установлено пустое значение. Применима для строк и контейнеров. Опция не принимает параметров. Генерирует [исключение](#exceptions), если после завершения отображения значением поля является пустая строка или пустой контейнер.

Пример задания опции:

```cpp
reg(&Spacecraft::name, "name", NotEmpty{}));
```

##### Required <div id="options_required"></div>

Отмечает, что для поля обязательно должно быть установлено значение. Применима для bool, целочисленных типов, типов с плавающей точкой, строк, контейнеров, структур с++ и перечислений. Опция не принимает параметров. Генерирует [исключение](#exceptions), если после завершения отображения значение для поля не было установлено.

Пример задания опции:

```cpp
reg(&Spacecraft::name, "name", Required{}));
```

##### Пример использования опций <div id="options_example"></div>

[example/options](/example/options/options.cpp)

```cpp
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>

#include "struct_mapping/struct_mapping.h"

namespace sm = struct_mapping;

struct Stage {
 unsigned short engine_count;
 std::string fuel;
 long length;

 friend std::ostream & operator<<(std::ostream & os, const Stage & o) {
  os << "  engine_count : " << o.engine_count << std::endl;
  os << "  fuel         : " << o.fuel << std::endl;
  os << "  length       : " << o.length << std::endl;

  return os;
 }
};

struct Spacecraft {
 bool in_development;
 std::string name;
 int mass;
 std::map<std::string, Stage> stages;
 std::list<std::string> crew;
 std::set<int> ids;
 std::unordered_set<std::string> tools;

 friend std::ostream & operator<<(std::ostream & os, const Spacecraft & o) {
  os << "in_development : " << std::boolalpha << o.in_development << std::endl;
  os << "name           : " << o.name << std::endl;
  os << "mass           : " << o.mass << std::endl;
  os << "stages: " << std::endl;
  for (auto& s : o.stages) os << " " << s.first << std::endl << s.second;
  os << "crew: " << std::endl;
  for (auto& p : o.crew) os << " " << p << std::endl;
  os << "ids: " << std::endl;
  for (auto& i : o.ids) os << " " << i << std::endl;
  os << "tools: " << std::endl;
  for (auto& t : o.tools) os << " " << t << std::endl;

  return os;
 }
};

int main() {
 sm::reg(&Stage::engine_count, "engine_count", sm::Default{6}, sm::Bounds{1, 31});
 sm::reg(&Stage::fuel, "fuel", sm::Default{"subcooled"});
 sm::reg(&Stage::length, "length", sm::Default{50});

 sm::reg(&Spacecraft::in_development, "in_development", sm::Required{});
 sm::reg(&Spacecraft::name, "name", sm::NotEmpty{});
 sm::reg(&Spacecraft::mass, "mass", sm::Default{5000000}, sm::Bounds{100000, 10000000});
 sm::reg(&Spacecraft::stages, "stages", sm::NotEmpty{});
 sm::reg(&Spacecraft::crew, "crew", sm::Default{std::list<std::string>{"Arthur", "Ford", "Marvin"}});
 sm::reg(&Spacecraft::ids, "ids", sm::Default{std::set<int>{14, 159}});
 sm::reg(&Spacecraft::tools, "tools", sm::NotEmpty{});

 Spacecraft starship;

 std::istringstream json_data(R"json(
 {
  "in_development": false,
  "name": "Vostok",
  "stages": {
   "first": {
    "engine_count": 31,
    "fuel": "compressed gas",
    "length": 70
   },
   "second": {}
  },
  "tools": [
   "Reverberating Carbonizer With Mutate Capacity",
   "Noisy Cricket",
   "The Series 4 De-Atomizer"
  ]
 }
 )json");

 sm::map_json_to_struct(starship, json_data);

 std::cout << starship << std::endl;
}
```

результат

```cpp
in_development : false
name           : Vostok
mass           : 5000000
stages: 
 first
  engine_count : 31
  fuel         : compressed gas
  length       : 70
 second
  engine_count : 6
  fuel         : subcooled
  length       : 50
crew: 
 Arthur
 Ford
 Marvin
ids: 
 14
 159
tools: 
 The Series 4 De-Atomizer
 Noisy Cricket
 Reverberating Carbonizer With Mutate Capacit
```

### Обратное отображение структуры c++ на json <div id="reverse_mapping_of_c_plus_plus_structure_to_json"></div>

Для обратного отображения структуры на json необходимо зарегистрировать все поля всех структур, которые требуется отображать, используя для каждого поля функцию

```cpp
template<typename T, typename V, typename ... U, template<typename> typename ... Options>
inline void reg(V T::* ptr, std::string const & name, Options<U>&& ... options);
```

- `ptr` - указатель на поле
- `name` - имя поля
- `options` - [опции отображения](#options)

и вызвать функцию

```cpp
template<typename T>
void map_struct_to_json(T & source_struct, std::basic_ostream<char> & json_data, std::string indent);
```

- `source_struct` - ссылка на исходную структуру
- `json_data` - ссылка на выходной поток json данных
- `indent` - отступ (если задан, делает выходной формат лучше читаемым)

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

результат

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

### Регистрация полей, совмещенная с инициализацией <div id="registration_of_data_members_combined_with_initialization"></div>

Чтобы не выносить регистрацию полей из структуры можно совместить регистрацию с инициализацией

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

Для упрощения использования такого способа определены четыре макроса

- BEGIN_STRUCT
- MEMBER
- MEMBER_OPTIONS
- END_STRUCT

#### BEGIN_STRUCT
Задает начало структуры и ее имя    

BEGIN_STRUCT(имя структуры)

```cpp
BEGIN_STRUCT(Planet)
```

#### MEMBER
Добавляет поле, регистрирует его и инициализирует его значением по умолчанию:

MEMBER(тип, название)

```cpp
MEMBER(bool, giant)
MEMBER(long long, surface_area)
MEMBER(double, mass)
MEMBER(std::vector<std::string>, satellites)
```

#### MEMBER_OPTIONS
Добавляет поле и регистрирует его. Вы можете установить опции для поля. Должно быть установлено не менее одной опции:

MEMBER_OPTIONS(тип, название, опция_1, ...)

```cpp
MEMBER_OPTIONS(
	int,
	count,
	struct_mapping::Bounds{23, 47},
	struct_mapping::Default{35})
```

#### END_STRUCT
Задает конец структуры

END_STRUCT

```cpp
END_STRUCT
```

[example/macro_reg](/example/macro_reg/macro_reg.cpp)

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "struct_mapping/struct_mapping.h"

BEGIN_STRUCT(Planet)

MEMBER(bool, giant)
MEMBER(long long, surface_area)
MEMBER_OPTIONS(
 double,
 mass,
 struct_mapping::Bounds{1.0e23, 1.0e27},
 struct_mapping::Default{1.0e25})
MEMBER(std::vector<std::string>, satellites)

END_STRUCT

int main() {
 std::istringstream json_data(R"json(
 {
  "giant": false,
  "surface_area": 510072000000000,
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
## Генерируемые исключения <div id="exceptions"></div>

StructMapping генерирует в процессе отображения исключение `StructMappingException`

* при установке значения для незарегистрированного поля (в json имя значения в объекте не сответствуют ни одному из зарегистрированных полей с++ структуры)
* при установке значения, тип которого не соответствует типу поля (для перечислений при установке значений отличных от строки)
* (для числовых полей) при установке значения , величина которого выходит за границы типа поля
* при использовании перечисления, если для него не бьли заданы функции преобразования в строку/из строки
* при установке значения, величина которого выходит за границы, установленные опцией Bounds
* при пустой строке или контейнере, если для была установлена опция NotEmpty
* если была задана опция Required, но значение не было установлено 
* при задании для опции Bounds значения, которое выходит за границы диапазона значений для типа поля
* при задании для опции Bounds значений, когда значение нижней границы больше значения верхней границы
* при задании для опции Default значения, которое выходит за границы диапазона значений для типа поля
*	при достижении конца потока json, когда парсинг не завершен (выполняется процесс парсинга объекта, значения и т.д.)
* когда в потоке json получен символ, который недопустим в данной позиции (например, символ завершения массива, если символ начала массива не был получен ранее)
* при ошибке преобразования json строки, представляющей собой число в число
