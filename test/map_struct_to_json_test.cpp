#include "struct_mapping/struct_mapping.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cstdint>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace
{

TEST(mapper_map_struct_to_json, simple)
{
	struct mapper_map_struct_to_json_simple
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

	mapper_map_struct_to_json_simple source;

	struct_mapping::reg(&mapper_map_struct_to_json_simple::a, "a");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::b, "b");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::c, "c");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::d, "d");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::e, "e");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::f, "f");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::g, "g");
	struct_mapping::reg(&mapper_map_struct_to_json_simple::h, "h");

	source.a = false;
	source.b = 1975;
	source.c = 14.768;
	source.d = std::string("Apollo");
	source.e = true;
	source.f = 1975;
	source.g = 6.790;
	source.h = std::string("Soyuz");

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "");

	std::string expected_json(
		R"json({"a":false,"b":1975,"c":14.768,"d":"Apollo","e":true,"f":1975,"g":6.79,"h":"Soyuz"})json");

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(mapper_map_struct_to_json, struct)
{
	struct mapper_map_struct_to_json_struct_A
	{
		int value;
	};

	struct mapper_map_struct_to_json_struct
	{
		mapper_map_struct_to_json_struct_A a;
		mapper_map_struct_to_json_struct_A b;
	};

	mapper_map_struct_to_json_struct source;
	
	struct_mapping::reg(&mapper_map_struct_to_json_struct_A::value, "value");
	struct_mapping::reg(&mapper_map_struct_to_json_struct::a, "a");
	struct_mapping::reg(&mapper_map_struct_to_json_struct::b, "b");
	
	source.a.value = 42;
	source.b.value = 2020;

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "");

	std::string expected_json(R"json({"a":{"value":42},"b":{"value":2020}})json");

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(mapper_map_struct_to_json_pretty, test_struct)
{
	struct mapper_map_struct_to_json_pretty_test_struct_A
	{
		int value;
	};

	struct mapper_map_struct_to_json_pretty_test_struct
	{
		mapper_map_struct_to_json_pretty_test_struct_A a;
		mapper_map_struct_to_json_pretty_test_struct_A b;
	};

	mapper_map_struct_to_json_pretty_test_struct source;

	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_struct_A::value, "value");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_struct::a, "a");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_struct::b, "b");

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

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(mapper_map_struct_to_json, array)
{
	struct mapper_map_struct_to_json_array
	{
		std::vector<int> a;
	};

	mapper_map_struct_to_json_array source;

	struct_mapping::reg(&mapper_map_struct_to_json_array::a, "a");

	source.a.push_back(1);
	source.a.push_back(3);
	source.a.push_back(5);

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "");

	std::string expected_json(R"json({"a":[1,3,5]})json");

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(mapper_map_struct_to_json_pretty, test_array)
{
	struct mapper_map_struct_to_json_pretty_test_array
	{
		std::vector<int> a;
	};

	mapper_map_struct_to_json_pretty_test_array source;

	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_array::a, "a");

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

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(mapper_map_struct_to_json, complex)
{
	struct mapper_map_struct_to_json_complex_author
	{
		std::string name;
		int birth_year;
	};

	struct mapper_map_struct_to_json_complex_book
	{
		double price;
		bool free;
		mapper_map_struct_to_json_complex_author author;
		std::vector<std::string> chapters;
	};

	mapper_map_struct_to_json_complex_book source;

	struct_mapping::reg(&mapper_map_struct_to_json_complex_author::name, "name");
	struct_mapping::reg(&mapper_map_struct_to_json_complex_author::birth_year, "birth_year");
	struct_mapping::reg(&mapper_map_struct_to_json_complex_book::price, "price");
	struct_mapping::reg(&mapper_map_struct_to_json_complex_book::free, "free");
	struct_mapping::reg(&mapper_map_struct_to_json_complex_book::author, "author");
	struct_mapping::reg(&mapper_map_struct_to_json_complex_book::chapters, "chapters");

	source.price = 12.35;
	source.free = false;
	source.author.name = "Gogol";
	source.author.birth_year = 1809;
	source.chapters.push_back(std::string("B 1999"));
	source.chapters.push_back(std::string("M 1998"));
	source.chapters.push_back(std::string("E 1997"));

	std::ostringstream result_json;
	struct_mapping::map_struct_to_json(source, result_json, "");

	std::string expected_json(
		R"json({"price":12.35,"free":false,"author":{"name":"Gogol","birth_year":1809},"chapters":["B 1999","M 1998","E 1997"]})json");

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(mapper_map_struct_to_json_pretty, test_complex)
{
	struct mapper_map_struct_to_json_pretty_test_complex_author
	{
		std::string name;
		int birth_year;
	};

	struct mapper_map_struct_to_json_pretty_test_complex_book
	{
		double price;
		bool free;
		mapper_map_struct_to_json_pretty_test_complex_author author;
		std::vector<std::string> chapters;
	};

	mapper_map_struct_to_json_pretty_test_complex_book source;

	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_complex_author::name, "name");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_complex_author::birth_year, "birth_year");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_complex_book::price, "price");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_complex_book::free, "free");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_complex_book::author, "author");
	struct_mapping::reg(&mapper_map_struct_to_json_pretty_test_complex_book::chapters, "chapters");

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

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(map_json_to_struct, test_enum)
{
	enum class map_json_to_struct_test_enum
	{
		v1,
		v2,
		v3
	};

	struct map_json_to_struct_test_enum_struct
	{
		map_json_to_struct_test_enum value;
		std::list<map_json_to_struct_test_enum> value_list;
		std::map<std::string, map_json_to_struct_test_enum> value_map;
	};

	struct_mapping::MemberString<map_json_to_struct_test_enum>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return map_json_to_struct_test_enum::v1;
			}
			else if (value == "v2")
			{
				return map_json_to_struct_test_enum::v2;
			}
			else if (value == "v3")
			{
				return map_json_to_struct_test_enum::v3;
			} 

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to map_json_to_struct_test_enum");
		},
		[] (map_json_to_struct_test_enum value)
		{
			switch (value)
			{
			case map_json_to_struct_test_enum::v1: return "v1";
			case map_json_to_struct_test_enum::v2: return "v2";
			default: return "v3";
			}
		});

	struct_mapping::reg(&map_json_to_struct_test_enum_struct::value, "value");
	struct_mapping::reg(&map_json_to_struct_test_enum_struct::value_list, "value_list");
	struct_mapping::reg(&map_json_to_struct_test_enum_struct::value_map, "value_map");

	map_json_to_struct_test_enum_struct source;

	source.value = map_json_to_struct_test_enum::v2;
	source.value_list.push_back(map_json_to_struct_test_enum::v1);
	source.value_list.push_back(map_json_to_struct_test_enum::v3);
	source.value_map["first"] = map_json_to_struct_test_enum::v2;
	source.value_map["second"] = map_json_to_struct_test_enum::v3;

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

	EXPECT_EQ(result_json.str(), expected_json);
}

TEST(map_json_to_struct, test_class_from_to_string)
{
	struct map_json_to_struct_test_class_from_to_string_a
	{
		int value;
	};

	struct map_json_to_struct_test_class_from_to_string_b
	{
		map_json_to_struct_test_class_from_to_string_a value;
		std::vector<map_json_to_struct_test_class_from_to_string_a> value_array;
		std::map<std::string, map_json_to_struct_test_class_from_to_string_a> value_map;
	};

	struct_mapping::MemberString<map_json_to_struct_test_class_from_to_string_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return map_json_to_struct_test_class_from_to_string_a{1};
			}
			else if (o == "value_2")
			{
				return map_json_to_struct_test_class_from_to_string_a{2};
			}
			
			return map_json_to_struct_test_class_from_to_string_a{0};
		},
		[] (map_json_to_struct_test_class_from_to_string_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(&map_json_to_struct_test_class_from_to_string_b::value, "value");
	struct_mapping::reg(&map_json_to_struct_test_class_from_to_string_b::value_array, "value_array");
	struct_mapping::reg(&map_json_to_struct_test_class_from_to_string_b::value_map, "value_map");

	map_json_to_struct_test_class_from_to_string_b source;

	source.value = map_json_to_struct_test_class_from_to_string_a{2};
	source.value_array.push_back(map_json_to_struct_test_class_from_to_string_a{1});
	source.value_array.push_back(map_json_to_struct_test_class_from_to_string_a{0});
	source.value_map["first"] = map_json_to_struct_test_class_from_to_string_a{2};
	source.value_map["second"] = map_json_to_struct_test_class_from_to_string_a{1};

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

	EXPECT_EQ(result_json.str(), expected_json);
}

} // namespace
