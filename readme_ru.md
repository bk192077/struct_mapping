# StructMapping

![Release version](https://img.shields.io/badge/release-v0.2.1-blue.svg)

[english documentation](/readme.md)

## Отображение json на структуру c++ и обратно

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

## Совместимость

Требуется компиляция с -std=c++17 В основном для:
* if constexpr
* static inline

Комбинации компилятор | платформа, на которых была протестирована StructMapping:

* GNU C++ 10.1.0 | Linux
* Clang 9 | Linux
* Visual C++ 2019 и Microsoft (R) C/C++ Optimizing Compiler Version 19.26.28806 for x64 | Windows 64-bit (кроме тестов)

## Установка

StructMapping - это библиотека включающая только заголовочные файлы. Все файлы библиотеки находятся в каталоге `include`

Для сборки примеров и запуска тестов выполните следующие действия (требуется [cmake](https://cmake.org/download/)):

1. создайте каталог `build` внутри каталога StructMapping
2. перейдите в каталог `build`
3. выполните команду `cmake ..` чтобы настроить сборку
4. выполните команду `cmake --build .` При успешной сборке вы найдете бинарные файлы примеров и тестов (под windows тесты не собираются) в каталоге `bin`
5. (не для windows) для запуска тестов выполните команду `ctest` (вы можете получить детальный вывод используя команду `ctest -V`)
6. для установки библиотеки можно выполнить команду `cmake --install .` с административными привилегиями

## Использование

### Реализация сценария со структурой Person

[example/person](/example/person/person.cpp)

определяем структуру

```cpp
BEGIN_MANAGED_STRUCT(Person)     // начало структуры

MANAGED_FIELD(std::string, name) // поле с типом 'std::string' и именем 'name'
MANAGED_FIELD(int, age)          // поле с типом 'int' и именем 'age'
MANAGED_FIELD(bool, student)     // поле с типом 'bool' и именем 'student'

END_MANAGED_STRUCT               // конец структуры
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
mapper::map_json_to_struct(person, json_data);
```

пользуемся

```cpp
std::cout << person.name << " : " << person.age;
```

Полностью код выглядит так

```cpp
#include <iostream>
#include <sstream>

#include "struct_mapping/struct_mapping.h" // inclusion of library files

BEGIN_MANAGED_STRUCT(Person)     // начало структуры

MANAGED_FIELD(std::string, name) // поле с типом 'std::string' и именем 'name'
MANAGED_FIELD(int, age)          // поле с типом 'int' и именем 'age'
MANAGED_FIELD(bool, student)     // поле с типом 'bool' и именем 'student'

END_MANAGED_STRUCT               // конец структуры

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

результат

```cpp
Jeebs : 42 : true
```

### Управляемая структура

Для использования в отображении структура должна быть определена с использованием MANAGED макросов:
- BEGIN_MANAGED_STRUCT
- MANAGED_FIELD
- MANAGED_FIELD_STRUCT
- MANAGED_FIELD_ARRAY
- END_MANAGED_STRUCT

#### BEGIN_MANAGED_STRUCT
Задает начало структуры и ее имя    

BEGIN_MANAGED_STRUCT(имя структуры)

```cpp
BEGIN_MANAGED_STRUCT(Person)
```

#### MANAGED_FIELD
Добавляет поле структуры, когда поле имеет один из следующих типов:
- bool
- целочисленные типы (char, int, ...)
- типы с плавающей точкой (float, double)
- std::string

MANAGED_FIELD(тип поля, название поля)

```cpp
MANAGED_FIELD(bool, ready)
MANAGED_FIELD(int, size)
MANAGED_FIELD(double, speed)
MANAGED_FIELD(std::string, color)
```

#### MANAGED_FIELD_STRUCT
Добавляет поле структуры, когда поле имеет тип структуры:

MANAGED_FIELD_STRUCT(тип поля, название поля)

```cpp
MANAGED_FIELD_STRUCT(President, president)
```

Тип поля здесь должен быть управляемой структурой. Например, в структуре Earth поле president имеет тип President, который задан ранее.

```cpp
BEGIN_MANAGED_STRUCT(President) <-- определяем структуру President

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, mass)

END_MANAGED_STRUCT


BEGIN_MANAGED_STRUCT(Earth)

MANAGED_FIELD_STRUCT(President, president) <-- определяем поле с типом President

END_MANAGED_STRUCT
```

#### MANAGED_FIELD_ARRAY
Добавляет поле структуры, когда поле имеет тип массива:

MANAGED_FIELD_ARRAY(тип элемента массива, имя поля)

```cpp
MANAGED_FIELD_ARRAY(std::string, friends)
```

тип элемента массива может быть одним из следующих:
- bool
- целочисленные типы (char, int, ...)
- типы с плавающей точкой (float, double)
- std::string
- управляемая структура
- массив

при этом реальным типом поля становится `managed::ManagedArray<тип элемента массива>` Внутри ManagedArray находится std::vector, который будет содержать значения массива. Ссылка на этот вектор может быть получена через метод

```cpp
std::vector<T> & ManagedArray::get_data();
````

например

```cpp
mib.friends.get_data()[13] // элемент массива по индексу тринадцать
```

Если требуется массив, элементы которого так же являются массивами, то необходимо использовать для поля тот же макрос `MANAGED_FIELD_ARRAY`, а тип элементов задавать через макрос `MANAGED_ARRAY`

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), alien_groups)
```

Доступ к элементам происходит с учетом вложенности векторов

```cpp
mib.alien_groups.get_data()[13].get_data()[42] // элемент массива по индексу сорок два в массиве
                                               // по индексу тринадцать
```

Размерность массивов можно увеличивать

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(MANAGED_ARRAY(std::string)), planet_groups)
```

#### END_MANAGED_STRUCT
Задает конец структуры

END_MANAGED_STRUCT


```cpp
END_MANAGED_STRUCT
```

### Отображение json на структуру c++

Для отображения json на структуру необходимо задать управляемую структуру с помощью MANAGED макросов и вызвать функцию

```cpp
template<typename T>
void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data);
```

- `result_struct` - ссылка на результирующую структуру
- `json_data` - ссылка на входной поток json данных

#### пример использования простых типов

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

результат

```cpp
earth
 giant        : false
 surface_area : 510072000000000
 mass         : 5.97237e+24
 satellite    : Moon
```

#### пример использования структур

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

результат

```cpp
earth.president:
 name : Agent K
 mass : 75.6
```

#### пример использования массивов

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

результат

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

### Обратное отображение структуры c++ на json

Для обратного отображения структуры в json необходимо задать управляемую структуру с помощью MANAGED макросов и вызвать функцию

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

## Генерируемые исключения

StructMapping генерирует в процессе отображения исключение `StructMappingException`

* при использовании для структуры поля с несуществующим именем (в json имя значения в объекте не сответствуют ни одному из полей с++ структуры)
* при попытке установить для массива значение неверного типа (в json тип значения в массиве не соответствует типу значения массива с++)
*	при достижении конца потока json, когда парсинг не завершен (выполняется процесс парсинга объекта, значения и т.д.)
* когда в потоке json получен символ, который недопустим в данной позиции (например, символ завершения массива, если символ начала массива не был получен ранее)
* при ошибке преобразования json строки, представляющей собой число в число

После исключения состояние управляемой структуры неполное и не может быть использовано.
