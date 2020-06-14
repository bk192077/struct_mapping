#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/managed/array.h"
#include "struct_mapping/managed/struct.h"
#include "struct_mapping/mapper/json.h"

namespace {

#define MANAGED_STRUCT_NAME Simple
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(bool, a)
MANAGED_FIELD(int, b)
MANAGED_FIELD(double, c)
MANAGED_FIELD(std::string, d)
MANAGED_FIELD(bool, e)
MANAGED_FIELD(int, f)
MANAGED_FIELD(double, g)
MANAGED_FIELD(std::string, h)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_mapper_map_struct_to_json, test_simple) {
	Simple source;
	source.a = false;
	source.b = 1975;
	source.c = 14.768;
	source.d = std::string("Apollo");
	source.e = true;
	source.f = 1975;
	source.g = 6.790;
	source.h = std::string("Soyuz");

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json);

	std::string expected_json(R"json({"a":false,"b":1975,"c":14.768,"d":"Apollo","e":true,"f":1975,"g":6.79,"h":"Soyuz"})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

#define MANAGED_STRUCT_NAME Struct_A
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(int, value)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

#define MANAGED_STRUCT_NAME Struct
BEGIN_MANAGED_STRUCT

MANAGED_FIELD_STRUCT(Struct_A, a)
MANAGED_FIELD_STRUCT(Struct_A, b)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_mapper_map_struct_to_json, test_struct) {
	Struct source;
	source.a.value = 42;
	source.b.value = 2020;

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json);

	std::string expected_json(R"json({"a":{"value":42},"b":{"value":2020}})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

TEST(struct_mapping_mapper_map_struct_to_json_pretty, test_struct) {
	Struct source;
	source.a.value = 42;
	source.b.value = 2020;

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json, "++");

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

#define MANAGED_STRUCT_NAME Array
BEGIN_MANAGED_STRUCT

MANAGED_FIELD_ARRAY(int, a)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_mapper_map_struct_to_json, test_array) {
	Array source;
	source.a.get_data().push_back(1);
	source.a.get_data().push_back(3);
	source.a.get_data().push_back(5);

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json);

	std::string expected_json(R"json({"a":[1,3,5]})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

TEST(struct_mapping_mapper_map_struct_to_json_pretty, test_array) {
	Array source;
	source.a.get_data().push_back(1);
	source.a.get_data().push_back(3);
	source.a.get_data().push_back(5);

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json, "++");

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

#define MANAGED_STRUCT_NAME ComplexAuthor
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(int, birth_year)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

#define MANAGED_STRUCT_NAME ComplexBook
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(double, price)
MANAGED_FIELD(bool, free)
MANAGED_FIELD_STRUCT(ComplexAuthor, author)
MANAGED_FIELD_ARRAY(std::string, chapters)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_mapper_map_struct_to_json, test_complex) {
	ComplexBook source;

	source.price = 12.35;
	source.free = false;
	source.author.name = "Gogol";
	source.author.birth_year = 1809;
	source.chapters.get_data().push_back(std::string("B 1999"));
	source.chapters.get_data().push_back(std::string("M 1998"));
	source.chapters.get_data().push_back(std::string("E 1997"));

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json);

	std::string expected_json(R"json({"price":12.35,"free":false,"author":{"name":"Gogol","birth_year":1809},"chapters":["B 1999","M 1998","E 1997"]})json");

	ASSERT_EQ(result_json.str(), expected_json);
}

TEST(struct_mapping_mapper_map_struct_to_json_pretty, test_complex) {
	ComplexBook source;

	source.price = 12.35;
	source.free = false;
	source.author.name = "Gogol";
	source.author.birth_year = 1809;
	source.chapters.get_data().push_back(std::string("B 1999"));
	source.chapters.get_data().push_back(std::string("M 1998"));
	source.chapters.get_data().push_back(std::string("E 1997"));

	std::ostringstream result_json;
	struct_mapping::mapper::map_struct_to_json(source, result_json, "++");

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
}
