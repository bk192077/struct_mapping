# StructMapping

![Release version](https://img.shields.io/badge/release-v0.2.0-blue.svg)

[english documentation](/readme.md)

## Отображение данных в формате json на структуру c++

В идеале хотелось бы определить структуру с++

```cpp
struct Person {
 std::string name;
 int age;
 bool student;
} person;
```

передать экземпляр person в метод отображения вместе с данными json_data

```cpp
map_json_to_struct(person, json_data)
```

после чего просто пользоваться заполненной структурой

```cpp
std::cout << person.name << " : " << person.age;
```

StructMapping пытается решить эту задачу. Для обеспечения сценария, максимально приближенного к приведенному выше, StructMapping требует от разработчика определить особым образом поля структуры.

## Совместимость

Требуется компиляция с -std=c++17 В основном для:
* if constexpr
* static inline

Комбинации компилятор / платформа, на которых была протестирована StructMapping:

* GNU C++ 10.1.0 на Linux
* Clang 9 на Linux

## Установка

StructMapping - это библиотека включающая только заголовочные файлы. Все файлы библиотеки находятся в каталоге `include`.

Для сборки примеров и запуска тестов выполните следующие действия:

1. создайте каталог `build` внутри каталога StructMapping
2. перейдите в каталог `build`
3. выполните команду `cmake ..` чтобы настроить сборку
4. выполните команду `cmake --build .` При успешной сборке вы найдете скомпилированные тесты и бинарные файлы примеров в каталоге `bin`
5. для запуска тестов выполните команду `ctest` (вы можете получить детальный вывод используя команду `ctest -V`)
6. для установки библиотеки можно выполнить команду `cmake --install .` с административными привилегиями

## Использование

**управляемая структура** - структура, определенная с использование MANAGED макросов   
**управляемый массив** - массив, определенный с использование MANAGED макросов

#### Реализация сценария со структурой Person

[example/person](/example/person/person.cpp)

определяем структуру

```cpp
#define MANAGED_STRUCT_NAME Person // определяем макрос, который задает имя структуры
BEGIN_MANAGED_STRUCT               // определяем начало структуры

MANAGED_FIELD(std::string, name)   // определяем поле с типом 'std::string' и именем 'name'
MANAGED_FIELD(int, age)            // определяем поле с типом 'int' и именем 'age'
MANAGED_FIELD(bool, student)       // определяем поле с типом 'bool' и именем 'student'

END_MANAGED_STRUCT                 // определяем конец структуры
#undef MANAGED_STRUCT_NAME         // убираем макрос, который задавал имя структуры, чтобы не было
                                   // варнингов о переопределении макроса в дальнейшем
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
struct_mapping::mapper::map_json_to_struct(person, json_data);
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

#define MANAGED_STRUCT_NAME Person // определяем макрос, который задает имя структуры
BEGIN_MANAGED_STRUCT               // определяем начало структуры

MANAGED_FIELD(std::string, name)   // определяем поле с типом 'std::string' и именем 'name'
MANAGED_FIELD(int, age)            // определяем поле с типом 'int' и именем 'age'
MANAGED_FIELD(bool, student)       // определяем поле с типом 'bool' и именем 'student'

END_MANAGED_STRUCT                 // определяем конец структуры
#undef MANAGED_STRUCT_NAME         // убираем макрос, который задавал имя структуры, чтобы не было
                                   // варнингов о переопределении макроса в дальнейшем

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

#### Используем простые типы

[example/simple](/example/simple/simple.cpp)

поля с простыми типами задаются макросом `MANAGED_FIELD(тип поля, название поля)`

тип поля может быть одним из следующих:
* bool
* целочисленные типы (char, int, ...)
* типы с плавающей точкой (float, double)
* std::string 

```cpp
MANAGED_FIELD(bool, ready)
MANAGED_FIELD(int, size)
MANAGED_FIELD(double, speed)
MANAGED_FIELD(std::string, name)
```

#### Используем структуры

[example/struct](/example/struct/struct.cpp)

поле с типом структуры задается макросом `MANAGED_FIELD_STRUCT(тип поля, имя поля)` Тип поля здесь должен быть управляемой структурой. Например, в структуре Earth поле president имеет тип President, который задан ранее.

```cpp
#define MANAGED_STRUCT_NAME President <-- определяем структуру President
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, mass)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

#define MANAGED_STRUCT_NAME Earth
BEGIN_MANAGED_STRUCT

MANAGED_FIELD_STRUCT(President, president) <-- определяем поле с типом President

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME
```

#### Используем массивы

[example/array](/example/array/array.cpp)

поле в виде массива задается макросом `MANAGED_FIELD_ARRAY(тип элемента массива, имя поля)`

```cpp
MANAGED_FIELD_ARRAY(std::string, friends)
```

тип элемента может быть:
- простым типом
- массивом (ManagedArray)
- структурой

при этом реальным типом поля становится `struct_mapping::managed::ManagedArray<тип элемента>` Внутри ManagedArray находится std::vector, который будет содержать значения массива. Ссылка на этот вектор может быть получена через метод `std::vector<T> & ManagedArray::get_data()`

```cpp
mib.friends.get_data()[13] // элемент массива по индексу тринадцать
```

если требуется массив, элементы которого так же являются массивами, то необходимо использовать для поля тот же макрос `MANAGED_FIELD_ARRAY`, но тип элементов нужно задавать через макрос `MANAGED_ARRAY`

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), alien_groups)
```

этот макрос разворачивается в

```cpp
struct_mapping::managed::ManagedArray<struct_mapping::managed::ManagedArray<std::string>> alien_groups
```

доступ к элементам происходит с учетом вложенности векторов

```cpp
mib.alien_groups.get_data()[13].get_data()[42] // элемент массива по индексу сорок два в массиве
                                               // по индексу тринадцать
```

размерность массивов можно увеличивать

```cpp
MANAGED_FIELD_ARRAY(MANAGED_ARRAY(MANAGED_ARRAY(std::string)), planet_groups)
```

#### Обратное отображение структуры c++ на данные в формате json

[example/struct_to_json](/example/struct_to_json/struct_to_json.cpp)

передаем экземпляр управляемой структуры в метод отображения вместе с выходным потоком данных json

```cpp
std::ostringstream json_data;
struct_mapping::mapper::map_struct_to_json(earth, json_data);
```

в результате получаются данные вида

```cpp
{"giant":false,"surface_area":510072000,"mass":5.97237e+24,"volume":1.08321e+12,"orbital_period":31536000,"name":"Terra","terrestrial":true,"shape":"nearly spherical","ocean":{"water_volume":1.332e+09,"surface_area":361132000,"liquid":true,"name":"World Ocean","color":{"name":"blue"},"parts":[{"name":"Pacific Ocean","average_depth":4.28011},{"name":"Atlantic Ocean","average_depth":3.646}]}}
```

выходной формат можно сделать более читаемым, используя третий параметр `map_struct_to_json`, который задает отступ. При задании отступа (параметр принимает строку)

```cpp
std::ostringstream json_data;
struct_mapping::mapper::map_struct_to_json(earth, json_data, "  ");
```

в результате получаются данные вида

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

## Как это работает

Каждая управляемя структура имеет переменную (use_name), хранящую имя используемого поля. Если use_name не пустая, то она хранит имя поля, которому будут транслироваться события от парсера. Изначально use_name пустая (используемых полей нет).

* если при парсинге встречается начало json объекта или json массива, то:
	* если use_name пустая, то в нее помещается имя поля, парсинг которого был начат
	* если use_name не пустая, то событие транслируется полю, имя которого содержится в use_name
* если при парсинге встречается конец json объекта или json массива, то:
	* если use_name пустая, то ничего не происходит
	* если use_name не пустая, то событие транслируется полю, имя которого содержится в use_name. Если после трансляции события получен признак завершения цепочки использования, то use_name очищается
* если при парсинге встречается установка значения, то:
	* если use_name пустая, то значение устанавливается для поля текущего экземпляра структуры по имени этого поля (а в случае массива значение добавляется в массив)
	* если use_name не пустая, то событие транслируется полю, имя которого содержится в use_name

Основная задача - отобразить данные в формате json на структуру с++. Структура с++ - это набор полей. Каждое поле имеет имя и содержит значение определенного типа. Поэтому на структуру с++ отображаются json объекты. В структуре с++ типы полей соответствуют типам json значений и могут быть следующими:
* bool - хранит json значение true или false
* integral или floating point - хранит json число
* std::string - хранит json строку
* управляемая структура - хранит json объект
* управляемый массив - хранит json массив

Для решения задачи SturctMapping использует:
* набор Fs_ классов
* управляемые структуры
* парсер json
* функцию map_json_to_struct

### Набор Fs_ классов

SturctMapping содержит набор одинаковых шаблонных классов, которые отличаются только названиями:
* Fs_set_field
* Fs_set
* Fs_use
* Fs_release

Каждый Fs_ класс предназначен для задания и получения по строковому имени функтора, тип которого задается параметром шаблона

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

Все экземпляры Fs_ классов можно условно разделить на наборы в каждом из которых собраны экземпляры Fs_, относящиеся к одному типу управляемой структуры. Тип управляемой структуры определяется первым параметром функции, которую хранит экземпляр Fs_. Например, следующий код

```cpp
Fs_set_field<std::function<void(Person&, bool)>>
```

относится к экземпляру Fs_, который хранит функции, относящиеся к типу `Person` (в данном примере только функции, предназначенные для установки полей логического типа)

### Управляемые структуры

Определение управляемой структуры состоит из трех частей: пролога, определения полей и эпилога

#### Пролог

Пролог состоит из задания имени структуры через определение макроса `MANAGED_STRUCT_NAME` и использование макроса `BEGIN_MANAGED_STRUCT`. Макрос `BEGIN_MANAGED_STRUCT` разворачивается в

```cpp
struct имя_структуры {
 void set(std::string const &, bool) {...}
 void set(std::string const &, std::string const &) {...}
 void set(std::string const &, long long) {...}
 void set(std::string const &, double) {...}
 void use(std::string const &) {...}
 bool release() {...}
```

функции set предназначены для установки значений управляемой структуры по имени поля. Первым параметром принимают имя поля, а вторым - значение. Перегружены по типу устанавливаемого значения для логического типа, строки, целого числа и числа с плавающей точкой. Функции use и release рассматриваются позже.

#### Определение полей

Поля структуры подразделяются на три типа:
* поля простых типов (логического типа, целочисленные, с плавающей точкой и строки)
* поля типа управляемой структуры
* поля типа управляемого массива

##### Поля простых типов

поле простого типа задается макросом `MANAGED_FIELD`, которому передается имя поля и тип поля. Макрос `MANAGED_FIELD` разворачивается в

```cpp
 тип_поля имя_поля = [] {
  ...
 } ();
```

лямбда вызывается при инициализации поля и возвращает значение по умолчанию для поля. Перед возвратом значения в Fs_set_field добавляется std::function с лямбдой, которая будет устанавливать значение этого поля у структуры, которая определяется в данный момент. Например, при определении у `Person` поля логического типа с именем `name`

```cpp
 Fs_set_field<std::function<void(Person&, bool)>>::add(
 "name",
 [] (Person &, bool) {
  ...
 });
```

##### Поля типа управляемой структуры

поле типа управляемой структуры задается макросом `MANAGED_FIELD_STRUCT`, которому передается имя поля и тип поля. Макрос `MANAGED_FIELD_STRUCT` разворачивается в

```cpp
 тип_поля имя_поля = [] {
  ...
 } ();
```

лямбда вызывается при инициализации поля и возвращает значение по умолчанию для поля. Перед возвратом значения в Fs_set, Fs_use и Fs_release добавляются std::function с лямбдой, каждая из которых просто вызывает у переданной ей ссылки на управляемую структуру метод set, use или release, соответственно.

##### Поля типа управляемого массива

Для задания массивов в StructMapping определены два макроса `MANAGED_ARRAY` и `MANAGED_FIELD_ARRAY`.
Макрос `MANAGED_ARRAY`, которому передается тип элемента массива, введен только для поддержки единого стиля и разворачивается просто в

```cpp
struct_mapping::mapper::ManagedArray<тип элемента массива>
```

Поле типа управляемого массива задается макросом `MANAGED_FIELD_ARRAY`, которому передается имя поля и тип элемента массива. Макрос `MANAGED_FIELD_ARRAY` разворачивается в

```cpp
MANAGED_FIELD_STRUCT(struct_mapping::mapper::ManagedArray<тип элемента массива>, имя поля)
```

т.е. определяется поле с типом управляемой структуры. Соответвтенно, являясь управляемой структурой, ManagedArray имеет методы set, use и release.

#### Эпилог

Эпилог состоит из использования макроса `END_MANAGED_STRUCT`, который разворачивается просто в

```cpp
};
```

и удаления текущего определения макроса, который задавал имя структуры (без этого действия при определении следующей структуры будут варнинги о переопределении макроса `MANAGED_STRUCT_NAME`)

### Парсер json

При создании экземпляра парсера ему в конструкторе передается несколько функций обратного вызова, которые делятся на три типа:
1. установки значения (отдельная функция для каждого из типов: логического, целого числа, числа с плавающей точкой и строки)
2. начала и завершения структуры (отдельные функции для начала и завершения)
3. начала и завершения массива (отдельные функции для начала и завершения)

эти функции парсер будет вызывать процессе работы. Всего передается восемь функций:

* set_bool с сигнатурой `void (std::string const & name, bool value)`
* set_integral с сигнатурой `void (std::string const & name, long long value)`
* set_floating_point с сигнатурой `void (std::string const & name, double value)`
* set_string с сигнатурой `void (std::string const & name, std::string const & value)`
* start_struct с сигнатурой `void (std::string const & name)`
* end_struct с сигнатурой `void ()`
* start_array с сигнатурой `void (std::string const & name)`
* end_array с сигнатурой `void ()`

#### set_bool

вызывается при завершении парсинга:

* пары имя/значение объекта json имеющей значением true или false

```cpp
{
 ...
 "ready": true
 ...
}
```

при этом в вызове передается имя и значение: `set_bool("ready", true)`

* значения массива json, когда значением является true или false

```cpp
[
 ...
 true
 ...
]
```

при этом в вызове передается пустое имя и значения: `set_bool("", true)`

#### set_integral

вызывается при завершении парсинга:

* пары имя/значение объекта json имеющей значением целое число

```cpp
{
 ...
 "age": 42
 ...
}
```

при этом в вызове передается имя и значение: `set_integral("age", 42)`

* значения массива json, когда значением является целое число

```cpp
[
 ...
 2020
 ...
]
```

при этом в вызове передается пустое имя и значения: `set_integral("", 2020)`

#### set_floating_point

вызывается при завершении парсинга:

* пары имя/значение объекта json имеющей значением число с плавающей точкой

```cpp
{
 ...
 "mass": 3.14159
 ...
}
```

при этом в вызове передается имя и значение: `set_floating_point("mass", 3.14159)`

* значения массива json, когда значением является число с плавающей точкой

```cpp
[
 ...
 9.81
 ...
]
```

при этом в вызове передается пустое имя и значения: `set_floating_point("", 9.81)`

#### set_string

вызывается при завершении парсинга:

* пары имя/значение объекта json имеющей значением строку

```cpp
{
 ...
 "name": "Agent K"
 ...
}
```

при этом в вызове передается имя и значение: `set_string("name", "Agent K")`

* значения массива json, когда значением является строка

```cpp
[
 ...
 "Griffin"
 ...
]
```

при этом в вызове передается пустое имя и значения: `set_string("", "Griffin")`

#### start_struct

вызывается при определении начала объекта (символа `'{'`). При этом в вызове передается:

* имя: `start_struct("planet")`, если объект является значением пары имя/значение

```cpp
{
 ...
 "planet": {
 ...
}
```

* пустое имя: `start_struct("")`, если объект является значением массива

```cpp
[
 ...
 {
 ...
]
```

#### end_struct

вызывается при определении конца объекта (символа `'}'`): `end_struct("")`

#### start_array

вызывается при определении начала массива (символа `'['`). При этом в вызове передается:

* имя: `start_array("friends")`, если массив является значением пары имя/значение

```cpp
{
 ...
 "friends": [
 ...
}
```

* пустое имя: `start_array("")`, если массив является значением массива

```cpp
[
 ...
 [
 ...
]
```

#### end_array

вызывается при определении конца массива (символа `']'`): `end_array("")`

### функция map_json_to_struct

map_json_to_struct является связующим звеном между парсером и управляемой структурой на которую отображаются json данные. Сигнатура map_json_to_struct:

```cpp
template<typename T>
void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data)
```

первый параметр - это ссылка на управляемую структуру на которую будут отображаться json данные. Второй параметр - это ссылка на поток json данных.

map_json_to_struct выполняет две опреации:
1. создает экземпляр парсера, передавая его конструктору набор функций, которые будет вызывать парсер в процессе работы:

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

2. запускает процесс, вызывая у парсера метод `parse`

```cpp
 jp.parse(&json_data);
```

каждая из функций, переданных парсеру, просто передает вызов управляемой структуре. Например, `set_bool` определена как

```cpp
auto set_bool = [&result_struct] (std::string const & name, bool value) {
 result_struct.set(name, value);
};
```

### разбор работы StructMapping на примере how_it_works

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

#### при компиляции

код

```cpp
#define MANAGED_STRUCT_NAME Author
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME
```

определяет структуру

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

поле `name` будет инициализировано пустой строкой. До этой инициализации в экземпляр класса Fs_set_field будет добавлена функция установки значения для данного поля

```cpp
Fs_set_field<std::function<void(Author &, std::string const &)>>::add(
 "name",
 [] (Author & o, std::string cont & value) {
  o.name = value;
 });
```

код

```cpp
#define MANAGED_STRUCT_NAME Book
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(int, price)
MANAGED_FIELD_STRUCT(Author, author)
MANAGED_FIELD_ARRAY(std::string, chapters)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME
```

определяет структуру

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

поле `price` будет инициализировано нулем. До этой инициализации в экземпляр класса Fs_set_field будет добавлена функция установки значения для данного поля

```cpp
Fs_set_field<std::function<void(Book &, long long)>>::add(
 "price",
 [] (Book & o, long long value) {
  o.price = static_cast<int>(value);
 });
```

поле `author` будет инициализировано значением по умолчанию Author. До этой инициализации в экземпляры классов Fs_ будут добавлены функции:

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

действия с полем `chapters` будут аналогичны действиям с полем `author`

#### при выполнении

*(при компиляции с включенной опцией `STRUCT_MAPPING_DEBUG` будет видна последовательность вызовов)*

вызов map_json_to_struct запускает процедуру парсинга, в процессе чего выполняются следующие действия (map_json_to_struct фактически просто транслирует вызовы управляемой структуре, поэтому ее действия не рассматриваются):

| parser                          | managed |
|:--------------------------------|:--------|
| start_struct("")                | это начало самой структуры Book, поэтому map_json_to_struct не транслирует этот вызов и он просто игнорируется |
| set_integral("price", 273)      | трансляция к white_space : `white_space.set("price", 273)` |
|                                 | установка значения поля price у white_space : `Fs_set_field<std::function<void(Book&, long long)>>::fs["price"](white_space, 273)` |
| start_struct("author")          | трансляция к white_space (после этого все вызовы white_space будет транслировать полю author) : `white_space.use("author")` |
| set_string("name", "bk192077")  | трансляция к white_space : `white_space.set("name", "bk192077")` |
|                                 | трансляция к author (вызов метода set у author) : `Fs_set<std::function<void(Book, std::string const &, bool)>>::fs["author"](white_space, "name", "bk192077")` |
|                                 | установка значения поля name у author : `Fs_set_field<std::function<void(Author&, std::string const &)>>::fs["name"](author, "bk192077")` |
| end_struct()                    | трансляция к white_space : `white_space.release()` |
|                                 | трансляция к author (вызов метода release у author) : `Fs_release<std::function<bool(Book&)>>::fs["author"](white_space))` |
|                                 | после этого вызовы к white_space не будут больше транслироваться к author |
| start_array("chapters")         | трансляция к white_space (после этого все вызовы white_space будет транслировать полю chapters) : `white_space.use("chapters")` |
| set_string("", "launch")        | трансляция к white_space : `white_space.set("", "launch")` |
|                                 | трансляция к chapters (вызов метода set у chapters) : `Fs_set<std::function<void(Book, std::string const &, bool)>>::fs["chapters"](white_space, "", "launch")` |
|                                 | добавление в массив элемента "launch" |
| set_string("", "new horizons")  | трансляция к white_space : `white_space.set("", "new horizons")` |
|                                 | трансляция к chapters (вызов метода set у chapters) : `Fs_set<std::function<void(Book, std::string const &, bool)>>::fs["chapters"](white_space, "", "new horizons")` |
|                                 | добавление в массив элемента "new horizons" |
| end_array()                     | трансляция к white_space : `white_space.release()` |
|                                 | трансляция к chapters (вызов метода release у chapters) : `Fs_release<std::function<bool(Book&)>>::fs["chapters"](white_space))` |
|                                 | после этого вызовы к white_space не будут больше транслироваться к chapters |
| end_struct()                    | это конец самой структуры Book, поэтому map_json_to_struct не транслирует этот вызов и он просто игнорируется |


## Генерируемые исключения

StructMapping генерирует исключение единственного типа `StructMappingException`, которое наследовано от std::runtime_error

Исключение генерируют:

* методы set управляемой структуры - при попытке установить значение несуществующего поля (нет сочетания названия и типа поля, для которого выполняется попытка установки значения)
* метод use управляемой структуры - при попытке выполнить эту функцию для несуществующего поля (нет поля с названием, для которого вызывается функция use)
* метод set управляемого массива - при попытке установить значение неверного типа
* json парсер при:
	*	достижении конца потока данных, когда парсинг не завершен (выполняется процесс парсинга объекта, значения и т.д.)
	* в потоке данных получен символ, который недопустим в данной позиции (например, символ завершения массива, если символ начала массива не был получен ранее)
	* при ошибке преобразования строки, представляющей собой число в число

После исключения состояние управляемой структуры неполное и не может быть использовано.