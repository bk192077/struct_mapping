#include <cstdint>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/struct_mapping.h"

namespace
{

struct Simple
{
	bool a;
	int b;
	double c;
	std::string d;
	bool e;
	int f;
	double g;
	std::string h;
};

TEST(struct_mapping_mapper_map_struct_to_json, simple)
{
	Simple source;

	struct_mapping::reg(&Simple::a, "a");
	struct_mapping::reg(&Simple::b, "b");
	struct_mapping::reg(&Simple::c, "c");
	struct_mapping::reg(&Simple::d, "d");
	struct_mapping::reg(&Simple::e, "e");
	struct_mapping::reg(&Simple::f, "f");
	struct_mapping::reg(&Simple::g, "g");
	struct_mapping::reg(&Simple::h, "h");

	source.a = false;
	source.b = 1975;
	source.c = 14.768;
	source.d = std::string("Apollo");
	source.e = true;
	source.f = 1975;
	source.g = 6.790;
	source.h = std::string("Soyuz");

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json);

	std::string expected_json(
		R"json({"a":false,"b":1975,"c":14.768,"d":"Apollo","e":true,"f":1975,"g":6.79,"h":"Soyuz"})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

struct Struct_A
{
	int value;
};

struct Struct
{
	Struct_A a;
	Struct_A b;
};

TEST(struct_mapping_mapper_map_struct_to_json, struct)
{
	Struct source;
	
	struct_mapping::reg(&Struct_A::value, "value");
	struct_mapping::reg(&Struct::a, "a");
	struct_mapping::reg(&Struct::b, "b");
	
	source.a.value = 42;
	source.b.value = 2020;

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json);

	std::string expected_json(R"json({"a":{"value":42},"b":{"value":2020}})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

TEST(struct_mapping_mapper_map_struct_to_json_pretty, test_struct)
{
	Struct source;

	source.a.value = 42;
	source.b.value = 2020;

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "++");

	std::string expected_json(
R"json({
++"a": {
++++"value": 42
++},
++"b": {
++++"value": 2020
++}
})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

struct Array
{
	std::vector<int> a;
};

TEST(struct_mapping_mapper_map_struct_to_json, array)
{
	Array source;

	struct_mapping::reg(&Array::a, "a");

	source.a.push_back(1);
	source.a.push_back(3);
	source.a.push_back(5);

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json);

	std::string expected_json(R"json({"a":[1,3,5]})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

TEST(struct_mapping_mapper_map_struct_to_json_pretty, test_array)
{
	Array source;

	source.a.push_back(1);
	source.a.push_back(3);
	source.a.push_back(5);

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "++");

	std::string expected_json(
R"json({
++"a": [
++++1,
++++3,
++++5
++]
})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

struct ComplexAuthor
{
	std::string name;
	int birth_year;
};

struct ComplexBook
{
	double price;
	bool free;
	ComplexAuthor author;
	std::vector<std::string> chapters;
};

TEST(struct_mapping_mapper_map_struct_to_json, complex)
{
	ComplexBook source;

	struct_mapping::reg(&ComplexAuthor::name, "name");
	struct_mapping::reg(&ComplexAuthor::birth_year, "birth_year");
	struct_mapping::reg(&ComplexBook::price, "price");
	struct_mapping::reg(&ComplexBook::free, "free");
	struct_mapping::reg(&ComplexBook::author, "author");
	struct_mapping::reg(&ComplexBook::chapters, "chapters");

	source.price = 12.35;
	source.free = false;
	source.author.name = "Gogol";
	source.author.birth_year = 1809;
	source.chapters.push_back(std::string("B 1999"));
	source.chapters.push_back(std::string("M 1998"));
	source.chapters.push_back(std::string("E 1997"));

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json);

	std::string expected_json(
		R"json({"price":12.35,"free":false,"author":{"name":"Gogol","birth_year":1809},"chapters":["B 1999","M 1998","E 1997"]})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

TEST(struct_mapping_mapper_map_struct_to_json_pretty, test_complex)
{
	ComplexBook source;

	source.price = 12.35;
	source.free = false;
	source.author.name = "Gogol";
	source.author.birth_year = 1809;
	source.chapters.push_back(std::string("B 1999"));
	source.chapters.push_back(std::string("M 1998"));
	source.chapters.push_back(std::string("E 1997"));

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "++");

	std::string expected_json(
R"json({
++"price": 12.35,
++"free": false,
++"author": {
++++"name": "Gogol",
++++"birth_year": 1809
++},
++"chapters": [
++++"B 1999",
++++"M 1998",
++++"E 1997"
++]
})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

enum class Enum_reverse
{
	v1,
	v2,
	v3
};

struct Struct_enum_reverse
{
	Enum_reverse value;
	std::list<Enum_reverse> value_list;
	std::map<std::string, Enum_reverse> value_map;
};

TEST(struct_mapping_map_json_to_struct, test_enum)
{
	struct_mapping::MemberString<Enum_reverse>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return Enum_reverse::v1;
			}
			else if (value == "v2")
			{
				return Enum_reverse::v2;
			}
			else if (value == "v3")
			{
				return Enum_reverse::v3;
			} 

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum_reverse");
		},
		[] (Enum_reverse value)
		{
			switch (value)
			{
			case Enum_reverse::v1: return "v1";
			case Enum_reverse::v2: return "v2";
			default: return "v3";
			}
		});

	struct_mapping::reg(&Struct_enum_reverse::value, "value");
	struct_mapping::reg(&Struct_enum_reverse::value_list, "value_list");
	struct_mapping::reg(&Struct_enum_reverse::value_map, "value_map");

	Struct_enum_reverse source;

	source.value = Enum_reverse::v2;
	source.value_list.push_back(Enum_reverse::v1);
	source.value_list.push_back(Enum_reverse::v3);
	source.value_map["first"] = Enum_reverse::v2;
	source.value_map["second"] = Enum_reverse::v3;

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "++");

	std::string expected_json(
R"json({
++"value": "v2",
++"value_list": [
++++"v1",
++++"v3"
++],
++"value_map": {
++++"first": "v2",
++++"second": "v3"
++}
})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

struct class_from_to_string_struct_a
{
	int value;
};

struct class_from_to_string_struct_b
{
	class_from_to_string_struct_a value;
	std::vector<class_from_to_string_struct_a> value_array;
	std::map<std::string, class_from_to_string_struct_a> value_map;
};

TEST(struct_mapping_map_json_to_struct, test_class_from_to_string)
{
	struct_mapping::MemberString<class_from_to_string_struct_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return class_from_to_string_struct_a{1};
			}
			else if (o == "value_2")
			{
				return class_from_to_string_struct_a{2};
			}
			
			return class_from_to_string_struct_a{0};
		},
		[] (class_from_to_string_struct_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(&class_from_to_string_struct_b::value, "value");
	struct_mapping::reg(&class_from_to_string_struct_b::value_array, "value_array");
	struct_mapping::reg(&class_from_to_string_struct_b::value_map, "value_map");

	class_from_to_string_struct_b source;

	source.value = class_from_to_string_struct_a{2};
	source.value_array.push_back(class_from_to_string_struct_a{1});
	source.value_array.push_back(class_from_to_string_struct_a{0});
	source.value_map["first"] = class_from_to_string_struct_a{2};
	source.value_map["second"] = class_from_to_string_struct_a{1};

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "++");

	std::string expected_json(
R"json({
++"value": "value_2",
++"value_array": [
++++"value_1",
++++"value_0"
++],
++"value_map": {
++++"first": "value_2",
++++"second": "value_1"
++}
})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

} // namespace
