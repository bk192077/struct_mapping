#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/managed/array.h"
#include "struct_mapping/managed/struct.h"
#include "struct_mapping/mapper/json.h"

using ::testing::ElementsAreArray;

namespace {

BEGIN_MANAGED_STRUCT(ManagedStruct_empty)
END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, empty_struct) {
	ManagedStruct_empty result_struct;
	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_long_long)

MANAGED_FIELD(long long, name_1)
MANAGED_FIELD(long long, name_2)
MANAGED_FIELD(long long, name_3)
MANAGED_FIELD(long long, name_4)
MANAGED_FIELD(long long, name_5)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_long_long) {
	ManagedStruct_field_number_long_long result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": -9223372036854775807,
		"name_2": 9223372036854775807,
		"name_3": 0,
		"name_4": 0.25,
		"name_5": -452.98
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -9223372036854775807);
	ASSERT_EQ(result_struct.name_2, 9223372036854775807);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, 0);
	ASSERT_EQ(result_struct.name_5, -452);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_int)

MANAGED_FIELD(int, name_1)
MANAGED_FIELD(int, name_2)
MANAGED_FIELD(int, name_3)
MANAGED_FIELD(int, name_4)
MANAGED_FIELD(int, name_5)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_int) {
	ManagedStruct_field_number_int result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": -2147483647,
		"name_2": 2147483647,
		"name_3": 0,
		"name_4": -152.86,
		"name_5": 6.8953
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -2147483647);
	ASSERT_EQ(result_struct.name_2, 2147483647);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, -152);
	ASSERT_EQ(result_struct.name_5, 6);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_short)

MANAGED_FIELD(short, name_1)
MANAGED_FIELD(short, name_2)
MANAGED_FIELD(short, name_3)
MANAGED_FIELD(short, name_4)
MANAGED_FIELD(short, name_5)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_short) {
	ManagedStruct_field_number_short result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": -32767,
		"name_2": 32767,
		"name_3": 0,
		"name_4": -12.365,
		"name_5": 128.449
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -32767);
	ASSERT_EQ(result_struct.name_2, 32767);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, -12);
	ASSERT_EQ(result_struct.name_5, 128);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_char)

MANAGED_FIELD(char, name_1)
MANAGED_FIELD(char, name_2)
MANAGED_FIELD(char, name_3)
MANAGED_FIELD(char, name_4)
MANAGED_FIELD(char, name_5)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_char) {
	ManagedStruct_field_number_char result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": -127,
		"name_2": 127,
		"name_3": 0,
		"name_4": -3.566,
		"name_5": 78.001
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -127);
	ASSERT_EQ(result_struct.name_2, 127);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, -3);
	ASSERT_EQ(result_struct.name_5, 78);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_unsigned_int)

MANAGED_FIELD(unsigned int, name_1)
MANAGED_FIELD(unsigned int, name_2)
MANAGED_FIELD(unsigned int, name_3)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_unsigned_int) {
	ManagedStruct_field_number_unsigned_int result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": 0,
		"name_2": 4294967295,
		"name_3": 2.356
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, 0);
	ASSERT_EQ(result_struct.name_2, 4294967295);
	ASSERT_EQ(result_struct.name_3, 2);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_unsigned_short)

MANAGED_FIELD(unsigned short, name_1)
MANAGED_FIELD(unsigned short, name_2)
MANAGED_FIELD(unsigned short, name_3)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_unsigned_short) {
	ManagedStruct_field_number_unsigned_short result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": 0,
		"name_2": 65535,
		"name_3": 45.032
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, 0);
	ASSERT_EQ(result_struct.name_2, 65535);
	ASSERT_EQ(result_struct.name_3, 45);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_unsigned_char)

MANAGED_FIELD(unsigned char, name_1)
MANAGED_FIELD(unsigned char, name_2)
MANAGED_FIELD(unsigned char, name_3)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_unsigned_char) {
	ManagedStruct_field_number_unsigned_char result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": 0,
		"name_2": 255,
		"name_3": 46.01
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, 0);
	ASSERT_EQ(result_struct.name_2, 255);
	ASSERT_EQ(result_struct.name_3, 46);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_number_float)

MANAGED_FIELD(double, name_1)
MANAGED_FIELD(double, name_2)
MANAGED_FIELD(double, name_3)
MANAGED_FIELD(double, name_4)
MANAGED_FIELD(double, name_5)
MANAGED_FIELD(double, name_6)
MANAGED_FIELD(double, name_7)
MANAGED_FIELD(double, name_8)
MANAGED_FIELD(double, name_9)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_number_float) {
	ManagedStruct_field_number_float result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": -9223372036854775807,
		"name_2": 9223372036854775807,
		"name_3": -2.9017,
		"name_4": 6325.23,
		"name_5": -0.018,
		"name_6": 0.9002,
		"name_7": 0,
		"name_8": 1,
		"name_9": -1
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_DOUBLE_EQ(result_struct.name_1, static_cast<double>(-9223372036854775807));
	ASSERT_DOUBLE_EQ(result_struct.name_2, static_cast<double>(9223372036854775807));
	ASSERT_DOUBLE_EQ(result_struct.name_3, -2.9017);
	ASSERT_DOUBLE_EQ(result_struct.name_4, 6325.23);
	ASSERT_DOUBLE_EQ(result_struct.name_5, -0.018);
	ASSERT_DOUBLE_EQ(result_struct.name_6, 0.9002);
	ASSERT_DOUBLE_EQ(result_struct.name_7, 0.0);
	ASSERT_DOUBLE_EQ(result_struct.name_8, 1.0);
	ASSERT_DOUBLE_EQ(result_struct.name_9, -1.0);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_string)

MANAGED_FIELD(std::string, name_1)
MANAGED_FIELD(std::string, name_2)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_string) {
	ManagedStruct_field_string result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": "value_1",
		"name_2": ""
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, "value_1");
	ASSERT_EQ(result_struct.name_2, "");
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_bool)

MANAGED_FIELD_ARRAY(bool, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_bool) {
	ManagedStruct_field_array_of_bool result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			true,
			false,
			false,
			true,
			true
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		true,
		false,
		false,
		true,
		true
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_number_long_long)

MANAGED_FIELD_ARRAY(long long, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_number_long_long) {
	ManagedStruct_field_array_of_number_long_long result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			42,
			-421,
			3.1425,
			-89.458,
			0.03901,
			-0.3006,
			0,
			1,
			-1
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		42,
		-421,
		3,
		-89,
		0,
		0,
		0,
		1,
		-1
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_number_int)

MANAGED_FIELD_ARRAY(int, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_number_int) {
	ManagedStruct_field_array_of_number_int result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			42,
			-421,
			3.1425,
			-89.458,
			0.03901,
			-0.3006,
			0,
			1,
			-1
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		42,
		-421,
		3,
		-89,
		0,
		0,
		0,
		1,
		-1
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_number_short)

MANAGED_FIELD_ARRAY(short, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_number_short) {
	ManagedStruct_field_array_of_number_short result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			42,
			-421,
			3.1425,
			-89.458,
			0.03901,
			-0.3006,
			0,
			1,
			-1
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		42,
		-421,
		3,
		-89,
		0,
		0,
		0,
		1,
		-1
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_number_char)

MANAGED_FIELD_ARRAY(char, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_number_char) {
	ManagedStruct_field_array_of_number_char result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			42,
			-41,
			3.1425,
			-89.458,
			0.03901,
			-0.3006,
			0,
			1,
			-1
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		42,
		-41,
		3,
		-89,
		0,
		0,
		0,
		1,
		-1
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_number_float)

MANAGED_FIELD_ARRAY(float, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_number_float) {
	ManagedStruct_field_array_of_number_float result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			42,
			-4105,
			3.1425,
			-89.458,
			0.03901,
			-0.3006,
			0,
			1,
			-1
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		42.0,
		-4105.0,
		3.1425,
		-89.458,
		0.03901,
		-0.3006,
		0.0,
		1.0,
		-1.0
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_number_double)

MANAGED_FIELD_ARRAY(double, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_number_double) {
	ManagedStruct_field_array_of_number_double result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			42,
			-4105,
			3.1425,
			-89.458,
			0.03901,
			-0.3006,
			0,
			1,
			-1
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		42.0,
		-4105.0,
		3.1425,
		-89.458,
		0.03901,
		-0.3006,
		0.0,
		1.0,
		-1.0
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_string)

MANAGED_FIELD_ARRAY(std::string, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_string) {
	ManagedStruct_field_array_of_string result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			"first_string",
			"",
			"third_string"
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1.get_data(), ElementsAreArray({
		"first_string",
		"",
		"third_string",
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_bool_single)

MANAGED_FIELD(bool, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_bool)

MANAGED_FIELD_ARRAY(ManagedStruct_field_bool_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_bool) {
	ManagedStruct_field_array_of_ManagedStruct_field_bool result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": true
			},
			{
			},
			{
				"name_2": false
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);

	ASSERT_TRUE(result_struct.name_1.get_data()[0].name_2);
	ASSERT_FALSE(result_struct.name_1.get_data()[1].name_2);
	ASSERT_FALSE(result_struct.name_1.get_data()[2].name_2);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_char_single)

MANAGED_FIELD(char, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_char)

MANAGED_FIELD_ARRAY(ManagedStruct_field_char_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_char) {
	ManagedStruct_field_array_of_ManagedStruct_field_char result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": 0
			},
			{
			},
			{
				"name_2": -1
			},
			{
				"name_2": 1
			},
			{
				"name_2": -10.123
			},
			{
				"name_2": 26.140
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 6);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, -1);
	ASSERT_EQ(result_struct.name_1.get_data()[3].name_2, 1);
	ASSERT_EQ(result_struct.name_1.get_data()[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1.get_data()[5].name_2, 26);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_short_single)

MANAGED_FIELD(short, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_short)

MANAGED_FIELD_ARRAY(ManagedStruct_field_short_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_short) {
	ManagedStruct_field_array_of_ManagedStruct_field_short result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": 0
			},
			{
			},
			{
				"name_2": -1
			},
			{
				"name_2": 1
			},
			{
				"name_2": -10.123
			},
			{
				"name_2": 26.140
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 6);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, -1);
	ASSERT_EQ(result_struct.name_1.get_data()[3].name_2, 1);
	ASSERT_EQ(result_struct.name_1.get_data()[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1.get_data()[5].name_2, 26);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_int_single)

MANAGED_FIELD(int, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_int)

MANAGED_FIELD_ARRAY(ManagedStruct_field_int_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_int) {
	ManagedStruct_field_array_of_ManagedStruct_field_int result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": 0
			},
			{
			},
			{
				"name_2": -102
			},
			{
				"name_2": 2365
			},
			{
				"name_2": -10.123
			},
			{
				"name_2": 26.140
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 6);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, -102);
	ASSERT_EQ(result_struct.name_1.get_data()[3].name_2, 2365);
	ASSERT_EQ(result_struct.name_1.get_data()[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1.get_data()[5].name_2, 26);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_long_long_single)

MANAGED_FIELD(long long, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_long_long)

MANAGED_FIELD_ARRAY(ManagedStruct_field_long_long_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_long_long) {
	ManagedStruct_field_array_of_ManagedStruct_field_long_long result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": 0
			},
			{
			},
			{
				"name_2": -102
			},
			{
				"name_2": 2365
			},
			{
				"name_2": -10.123
			},
			{
				"name_2": 26.140
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 6);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, -102);
	ASSERT_EQ(result_struct.name_1.get_data()[3].name_2, 2365);
	ASSERT_EQ(result_struct.name_1.get_data()[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1.get_data()[5].name_2, 26);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_float_single)

MANAGED_FIELD(float, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_float)

MANAGED_FIELD_ARRAY(ManagedStruct_field_float_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_float) {
	ManagedStruct_field_array_of_ManagedStruct_field_float result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": 0
			},
			{
			},
			{
				"name_2": -102
			},
			{
				"name_2": 2365
			},
			{
				"name_2": -10.123
			},
			{
				"name_2": 26.140
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 6);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, 0.0f);
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, 0.0f);
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, -102.0f);
	ASSERT_EQ(result_struct.name_1.get_data()[3].name_2, 2365.0f);
	ASSERT_EQ(result_struct.name_1.get_data()[4].name_2, -10.123f);
	ASSERT_EQ(result_struct.name_1.get_data()[5].name_2, 26.14f);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_double_single)

MANAGED_FIELD(double, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_double)

MANAGED_FIELD_ARRAY(ManagedStruct_field_double_single, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_double) {
	ManagedStruct_field_array_of_ManagedStruct_field_double result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": 0
			},
			{
			},
			{
				"name_2": -102
			},
			{
				"name_2": 2365
			},
			{
				"name_2": -10.123
			},
			{
				"name_2": 26.140
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 6);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, 0.0);
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, 0.0);
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, -102);
	ASSERT_EQ(result_struct.name_1.get_data()[3].name_2, 2365);
	ASSERT_EQ(result_struct.name_1.get_data()[4].name_2, -10.123);
	ASSERT_EQ(result_struct.name_1.get_data()[5].name_2, 26.140);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_string_one)

MANAGED_FIELD(std::string, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_ManagedStruct_field_string)

MANAGED_FIELD_ARRAY(ManagedStruct_field_string_one, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, struct_field_array_of_ManagedStruct_field_string) {
	ManagedStruct_field_array_of_ManagedStruct_field_string result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			{
				"name_2": "first_string"
			},
			{
			},
			{
				"name_2": ""
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);

	ASSERT_EQ(result_struct.name_1.get_data()[0].name_2, "first_string");
	ASSERT_EQ(result_struct.name_1.get_data()[1].name_2, "");
	ASSERT_EQ(result_struct.name_1.get_data()[2].name_2, "");
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_bool)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(bool), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_bool) {
	ManagedStruct_field_array_of_array_of_bool result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				true,
				false,
				true
			],
			[
			],
			[
				false,
				true
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_EQ(result_struct.name_1.get_data()[0].get_data().size(), 3);
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_EQ(result_struct.name_1.get_data()[2].get_data().size(), 2);
	ASSERT_TRUE(result_struct.name_1.get_data()[0].get_data()[0]);
	ASSERT_FALSE(result_struct.name_1.get_data()[0].get_data()[1]);
	ASSERT_TRUE(result_struct.name_1.get_data()[0].get_data()[2]);
	ASSERT_FALSE(result_struct.name_1.get_data()[2].get_data()[0]);
	ASSERT_TRUE(result_struct.name_1.get_data()[2].get_data()[1]);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_char)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(char), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_char) {
	ManagedStruct_field_array_of_array_of_char result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				123,
				0,
				-123,
				0.2,
				-45.689
			],
			[
			],
			[
				39,
				0,
				-223,
				0.2,
				-145.689,
				28
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		123,
		0,
		-123,
		0,
		-45
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		39,
		0,
		-223,
		0,
		-145,
		28
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_short)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(short), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_short) {
	ManagedStruct_field_array_of_array_of_short result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				123,
				0,
				-123,
				0.2,
				-45.689
			],
			[
			],
			[
				39,
				0,
				-223,
				0.2,
				-145.689,
				28
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		123,
		0,
		-123,
		0,
		-45
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		39,
		0,
		-223,
		0,
		-145,
		28
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_int)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(int), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_int) {
	ManagedStruct_field_array_of_array_of_int result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				123,
				0,
				-123,
				0.2,
				-45.689
			],
			[
			],
			[
				39,
				0,
				-223,
				0.2,
				-145.689,
				28
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		123,
		0,
		-123,
		0,
		-45
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		39,
		0,
		-223,
		0,
		-145,
		28
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_long_long)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(long long), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_long_long) {
	ManagedStruct_field_array_of_array_of_long_long result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				123,
				0,
				-123,
				0.2,
				-45.689
			],
			[
			],
			[
				39,
				0,
				-223,
				0.2,
				-145.689,
				28
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		123,
		0,
		-123,
		0,
		-45
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		39,
		0,
		-223,
		0,
		-145,
		28
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_float)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(float), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_float) {
	ManagedStruct_field_array_of_array_of_float result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				123,
				0,
				-123,
				0.2,
				-45.689
			],
			[
			],
			[
				39,
				0,
				-223,
				0.2,
				-145.689,
				28
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		123.0f,
		0.0f,
		-123.0f,
		0.2f,
		-45.689f
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		39.0f,
		0.0f,
		-223.0f,
		0.2f,
		-145.689f,
		28.0f
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_double)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(double), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_double) {
	ManagedStruct_field_array_of_array_of_double result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				123,
				0,
				-123,
				0.2,
				-45.689
			],
			[
			],
			[
				39,
				0,
				-223,
				0.2,
				-145.689,
				28
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		123.0,
		0.0,
		-123.0,
		0.2,
		-45.689
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		39.0,
		0.0,
		-223.0,
		0.2,
		-145.689,
		28.0
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_field_array_of_array_of_string)

MANAGED_FIELD_ARRAY(MANAGED_ARRAY(std::string), name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_field_array_of_array_of_string) {
	ManagedStruct_field_array_of_array_of_string result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				"first string",
				"",
				"second_string"
			],
			[
			],
			[
				"",
				"third_string"
			]
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.get_data().size(), 3);
	ASSERT_THAT(result_struct.name_1.get_data()[0].get_data(), ElementsAreArray({
		"first string",
		"",
		"second_string"
	}));
	ASSERT_EQ(result_struct.name_1.get_data()[1].get_data().size(), 0);
	ASSERT_THAT(result_struct.name_1.get_data()[2].get_data(), ElementsAreArray({
		"",
		"third_string"
	}));
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_bool_3)

MANAGED_FIELD(bool, name_3)
MANAGED_FIELD(bool, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_bool_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_bool_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_bool_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_bool_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_bool) {
	ManagedStruct_ManagedStruct_field_bool_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": false,
				"name_4": true
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_FALSE(result_struct.name_1.name_2.name_3);
	ASSERT_TRUE(result_struct.name_1.name_2.name_4);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_char_3)

MANAGED_FIELD(char, name_3)
MANAGED_FIELD(char, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_char_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_char_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_char_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_char_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_char) {
	ManagedStruct_ManagedStruct_field_char_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": 9.01856,
				"name_4": -25
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, 9);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, -25);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_short_3)

MANAGED_FIELD(short, name_3)
MANAGED_FIELD(short, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_short_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_short_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_short_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_short_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_short) {
	ManagedStruct_ManagedStruct_field_short_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": -19.01856,
				"name_4": 2598
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -19);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 2598);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_int_3)

MANAGED_FIELD(int, name_3)
MANAGED_FIELD(int, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_int_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_int_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_int_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_int_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_int) {
	ManagedStruct_ManagedStruct_field_int_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": -191.2856,
				"name_4": 29809
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -191);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 29809);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_long_long_3)

MANAGED_FIELD(long long, name_3)
MANAGED_FIELD(long long, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_long_long_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_long_long_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_long_long_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_long_long_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_long_long) {
	ManagedStruct_ManagedStruct_field_long_long_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": 89412.2856,
				"name_4": -109963
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, 89412);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, -109963);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_float_3)

MANAGED_FIELD(float, name_3)
MANAGED_FIELD(float, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_float_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_float_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_float_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_float_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_float) {
	ManagedStruct_ManagedStruct_field_float_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": -1412.2856,
				"name_4": 63
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -1412.2856f);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 63.0f);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_double_3)

MANAGED_FIELD(double, name_3)
MANAGED_FIELD(double, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_double_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_double_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_double_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_double_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_double) {
	ManagedStruct_ManagedStruct_field_double_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": 555.3294,
				"name_4": -3695478
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, 555.3294);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, -3695478.0);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_string_3)

MANAGED_FIELD(std::string, name_3)
MANAGED_FIELD(std::string, name_4)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_string_2)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_string_3, name_2)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_string_1)

MANAGED_FIELD_STRUCT(ManagedStruct_ManagedStruct_field_string_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedStruct_ManagedStruct_field_string) {
	ManagedStruct_ManagedStruct_field_string_1 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": "first_string",
				"name_4": ""
			}
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, "first_string");
	ASSERT_EQ(result_struct.name_1.name_2.name_4, "");
}

BEGIN_MANAGED_STRUCT(ManagedStruct_ManagedStruct_field_string_0)

MANAGED_FIELD_ARRAY(ManagedStruct_ManagedStruct_field_string_1, name_0)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, ManagedArray_ManagedStruct_ManagedStruct_field_string) {
	ManagedStruct_ManagedStruct_field_string_0 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_0": [
			{
				"name_1": {
					"name_2": {
						"name_3": "first_string",
						"name_4": ""
					}
				}
			},
			{
			},
			{
				"name_1": {
					"name_2": {
						"name_3": "",
						"name_4": "second_string"
					}
				}
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_0.get_data().size(), 3);

	ASSERT_EQ(result_struct.name_0.get_data()[0].name_1.name_2.name_3, "first_string");
	ASSERT_EQ(result_struct.name_0.get_data()[0].name_1.name_2.name_4, "");

	ASSERT_EQ(result_struct.name_0.get_data()[1].name_1.name_2.name_3, "");
	ASSERT_EQ(result_struct.name_0.get_data()[1].name_1.name_2.name_4, "");

	ASSERT_EQ(result_struct.name_0.get_data()[2].name_1.name_2.name_3, "");
	ASSERT_EQ(result_struct.name_0.get_data()[2].name_1.name_2.name_4, "second_string");
}

BEGIN_MANAGED_STRUCT(ManagedStruct_identical_field_names_and_types_in_structures_1)

MANAGED_FIELD(std::string, name_1)
MANAGED_FIELD(int, name_2)
MANAGED_FIELD(bool, name_3)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_identical_field_names_and_types_in_structures_2)

MANAGED_FIELD(std::string, name_1)
MANAGED_FIELD(int, name_2)
MANAGED_FIELD(double, name_3)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_identical_field_names_and_types_in_structures_3)

MANAGED_FIELD(std::string, name_1)
MANAGED_FIELD_STRUCT(ManagedStruct_identical_field_names_and_types_in_structures_1, name_2)
MANAGED_FIELD_STRUCT(ManagedStruct_identical_field_names_and_types_in_structures_2, name_3)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, identical_field_names_and_types_in_structures) {
	ManagedStruct_identical_field_names_and_types_in_structures_3 result_struct;
	std::istringstream json_data(R"json(
	{
		"name_1": "first_string",
		"name_2": {
			"name_1": "second_string",
			"name_2": 42,
			"name_3": true
		},
		"name_3": {
			"name_1": "third_string",
			"name_2": 93,
			"name_3": -0.23
		}
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, "first_string");
	ASSERT_EQ(result_struct.name_2.name_1, "second_string");
	ASSERT_EQ(result_struct.name_2.name_2, 42);
	ASSERT_TRUE(result_struct.name_2.name_3);
	ASSERT_EQ(result_struct.name_3.name_1, "third_string");
	ASSERT_EQ(result_struct.name_3.name_2, 93);
	ASSERT_EQ(result_struct.name_3.name_3, -0.23);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_multiple_times_2)

MANAGED_FIELD(std::string, name_2)
MANAGED_FIELD(bool, name_3)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_multiple_times_1)

MANAGED_FIELD_ARRAY(ManagedStruct_multiple_times_2, name_1)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, multiple_times_same_struct) {
	ManagedStruct_multiple_times_1 result_struct_1;
	ManagedStruct_multiple_times_1 result_struct_2;

	std::istringstream json_data_1(R"json(
	{
		"name_1": [
			{
				"name_2": "first_string",
				"name_3": true
			},
			{
				"name_2": "second_string",
				"name_3": false
			}
		]
	}
	)json");

	std::istringstream json_data_2(R"json(
	{
		"name_1": [
			{
				"name_2": "third_string",
				"name_3": true
			},
			{
				"name_2": "fourth_string",
				"name_3": true
			},
			{
				"name_2": "fifth_string",
				"name_3": false
			}
		]
	}
	)json");
	
	struct_mapping::mapper::map_json_to_struct(result_struct_1, json_data_1);
	struct_mapping::mapper::map_json_to_struct(result_struct_2, json_data_2);

	ASSERT_EQ(result_struct_1.name_1.get_data().size(), 2);
	ASSERT_EQ(result_struct_1.name_1.get_data()[0].name_2, "first_string");
	ASSERT_TRUE(result_struct_1.name_1.get_data()[0].name_3);
	ASSERT_EQ(result_struct_1.name_1.get_data()[1].name_2, "second_string");
	ASSERT_FALSE(result_struct_1.name_1.get_data()[1].name_3);

	ASSERT_EQ(result_struct_2.name_1.get_data().size(), 3);
	ASSERT_EQ(result_struct_2.name_1.get_data()[0].name_2, "third_string");
	ASSERT_TRUE(result_struct_2.name_1.get_data()[0].name_3);
	ASSERT_EQ(result_struct_2.name_1.get_data()[1].name_2, "fourth_string");
	ASSERT_TRUE(result_struct_2.name_1.get_data()[1].name_3);
	ASSERT_EQ(result_struct_2.name_1.get_data()[2].name_2, "fifth_string");
	ASSERT_FALSE(result_struct_2.name_1.get_data()[2].name_3);
}

BEGIN_MANAGED_STRUCT(ManagedStruct_satellite)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(double, radius)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_planet)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(bool, populated)
MANAGED_FIELD(double, radius)
MANAGED_FIELD_ARRAY(ManagedStruct_satellite, satellites)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_photospheric_composition)

MANAGED_FIELD(double, Hydrogen)
MANAGED_FIELD(double, Helium)
MANAGED_FIELD(double, Oxygen)
MANAGED_FIELD(double, Carbon)
MANAGED_FIELD(double, Iron)
MANAGED_FIELD(double, Neon)
MANAGED_FIELD(double, Nitrogen)
MANAGED_FIELD(double, Silicon)
MANAGED_FIELD(double, Magnesium)
MANAGED_FIELD(double, Sulphur)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_star)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(long long, age)
MANAGED_FIELD(double, radius)
MANAGED_FIELD_STRUCT(ManagedStruct_photospheric_composition, photospheric_composition)

END_MANAGED_STRUCT

BEGIN_MANAGED_STRUCT(ManagedStruct_complex)

MANAGED_FIELD(std::string, name)
MANAGED_FIELD(long long, age)
MANAGED_FIELD(double, major_axis)
MANAGED_FIELD(bool, populated)
MANAGED_FIELD_STRUCT(ManagedStruct_star, star)
MANAGED_FIELD_ARRAY(ManagedStruct_planet, planets)

END_MANAGED_STRUCT

TEST(struct_mapping_mapper_map_json_to_struct, complex) {
	ManagedStruct_complex result_struct;

	std::istringstream json_data(R"json(
	{
		"name": "solar system",
		"age": 4568000000,
		"major_axis": 4500000000,
		"populated": true,
		"star": {
			"name": "Sun",
			"age": 4600000000,
			"radius": 695700,
			"photospheric_composition": {
				"Hydrogen": 73.46,
				"Helium": 24.85,
				"Oxygen": 0.77,
				"Carbon": 0.29,
				"Iron": 0.16,
				"Neon": 0.12,
				"Nitrogen": 0.09,
				"Silicon": 0.07,
				"Magnesium": 0.05,
				"Sulphur": 0.04
			}
		},
		"planets": [
			{
				"name": "Mercury",
				"populated": false,
				"radius": 2440,
				"satellites": []
			},
			{
				"name": "Venus",
				"populated": false,
				"radius": 6052,
				"satellites": []
			},
			{
				"name": "Earth",
				"populated": true,
				"radius": 6371,
				"satellites": [
					{
						"name": "Moon",
						"radius": 1738
					}
				]
			},
			{
				"name": "Mars",
				"populated": false,
				"radius": 3390,
				"satellites": [
					{
						"name": "Phobos",
						"radius": 11.27
					},
					{
						"name": "Deimos",
						"radius": 6.2
					}
				]
			},
			{
				"name": "Jupiter",
				"populated": false,
				"radius": 71492,
				"satellites": [
					{
						"name": "Io",
						"radius": 1822
					},
					{
						"name": "Europa",
						"radius": 1561
					},
					{
						"name": "Ganymede",
						"radius": 2634
					},
					{
						"name": "Callisto",
						"radius": 2410
					}
				]
			},
			{
				"name": "Saturn",
				"populated": false,
				"radius": 58232,
				"satellites": [
					{
						"name": "Mimas",
						"radius": 198
					},
					{
						"name": "Enceladus",
						"radius": 252
					},
					{
						"name": "Tethys",
						"radius": 531
					}
				]
			},
			{
				"name": "Uranus",
				"populated": false,
				"radius": 25363,
				"satellites": [
					{
						"name": "Miranda",
						"radius": 236
					},
					{
						"name": "Ariel",
						"radius": 579
					},
					{
						"name": "Umbriel",
						"radius": 585
					}
				]
			},
			{
				"name": "Neptune",
				"populated": false,
				"radius": 24622,
				"satellites": [
					{
						"name": "Triton",
						"radius": 1354
					},
					{
						"name": "Nereid",
						"radius": 175
					}
				]
			}
		]
	}
	)json");

	struct_mapping::mapper::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name, "solar system");
	ASSERT_EQ(result_struct.age, 4568000000);
	ASSERT_EQ(result_struct.major_axis, 4500000000);
	ASSERT_EQ(result_struct.populated, true);

	ASSERT_EQ(result_struct.star.name, "Sun");
	ASSERT_EQ(result_struct.star.age, 4600000000);
	ASSERT_EQ(result_struct.star.radius, 695700);
	ASSERT_EQ(result_struct.star.photospheric_composition.Hydrogen, 73.46);
	ASSERT_EQ(result_struct.star.photospheric_composition.Helium, 24.85);
	ASSERT_EQ(result_struct.star.photospheric_composition.Oxygen, 0.77);
	ASSERT_EQ(result_struct.star.photospheric_composition.Carbon, 0.29);
	ASSERT_EQ(result_struct.star.photospheric_composition.Iron, 0.16);
	ASSERT_EQ(result_struct.star.photospheric_composition.Neon, 0.12);
	ASSERT_EQ(result_struct.star.photospheric_composition.Nitrogen, 0.09);
	ASSERT_EQ(result_struct.star.photospheric_composition.Silicon, 0.07);
	ASSERT_EQ(result_struct.star.photospheric_composition.Magnesium, 0.05);
	ASSERT_EQ(result_struct.star.photospheric_composition.Sulphur, 0.04);

	ASSERT_EQ(result_struct.planets.get_data().size(), 8);

	ASSERT_EQ(result_struct.planets.get_data()[0].name, "Mercury");
	ASSERT_EQ(result_struct.planets.get_data()[0].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[0].radius, 2440);
	ASSERT_EQ(result_struct.planets.get_data()[0].satellites.get_data().size(), 0);

	ASSERT_EQ(result_struct.planets.get_data()[1].name, "Venus");
	ASSERT_EQ(result_struct.planets.get_data()[1].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[1].radius, 6052);
	ASSERT_EQ(result_struct.planets.get_data()[1].satellites.get_data().size(), 0);

	ASSERT_EQ(result_struct.planets.get_data()[2].name, "Earth");
	ASSERT_EQ(result_struct.planets.get_data()[2].populated, true);
	ASSERT_EQ(result_struct.planets.get_data()[2].radius, 6371);
	ASSERT_EQ(result_struct.planets.get_data()[2].satellites.get_data().size(), 1);
	ASSERT_EQ(result_struct.planets.get_data()[2].satellites.get_data()[0].name, "Moon");
	ASSERT_EQ(result_struct.planets.get_data()[2].satellites.get_data()[0].radius, 1738);

	ASSERT_EQ(result_struct.planets.get_data()[3].name, "Mars");
	ASSERT_EQ(result_struct.planets.get_data()[3].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[3].radius, 3390);
	ASSERT_EQ(result_struct.planets.get_data()[3].satellites.get_data().size(), 2);
	ASSERT_EQ(result_struct.planets.get_data()[3].satellites.get_data()[0].name, "Phobos");
	ASSERT_EQ(result_struct.planets.get_data()[3].satellites.get_data()[0].radius, 11.27);
	ASSERT_EQ(result_struct.planets.get_data()[3].satellites.get_data()[1].name, "Deimos");
	ASSERT_EQ(result_struct.planets.get_data()[3].satellites.get_data()[1].radius, 6.2);

	ASSERT_EQ(result_struct.planets.get_data()[4].name, "Jupiter");
	ASSERT_EQ(result_struct.planets.get_data()[4].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[4].radius, 71492);
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data().size(), 4);
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[0].name, "Io");
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[0].radius, 1822);
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[1].name, "Europa");
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[1].radius, 1561);
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[2].name, "Ganymede");
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[2].radius, 2634);
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[3].name, "Callisto");
	ASSERT_EQ(result_struct.planets.get_data()[4].satellites.get_data()[3].radius, 2410);

	ASSERT_EQ(result_struct.planets.get_data()[5].name, "Saturn");
	ASSERT_EQ(result_struct.planets.get_data()[5].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[5].radius, 58232);
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data().size(), 3);
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data()[0].name, "Mimas");
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data()[0].radius, 198);
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data()[1].name, "Enceladus");
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data()[1].radius, 252);
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data()[2].name, "Tethys");
	ASSERT_EQ(result_struct.planets.get_data()[5].satellites.get_data()[2].radius, 531);

	ASSERT_EQ(result_struct.planets.get_data()[6].name, "Uranus");
	ASSERT_EQ(result_struct.planets.get_data()[6].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[6].radius, 25363);
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data().size(), 3);
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data()[0].name, "Miranda");
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data()[0].radius, 236);
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data()[1].name, "Ariel");
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data()[1].radius, 579);
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data()[2].name, "Umbriel");
	ASSERT_EQ(result_struct.planets.get_data()[6].satellites.get_data()[2].radius, 585);

	ASSERT_EQ(result_struct.planets.get_data()[7].name, "Neptune");
	ASSERT_EQ(result_struct.planets.get_data()[7].populated, false);
	ASSERT_EQ(result_struct.planets.get_data()[7].radius, 24622);
	ASSERT_EQ(result_struct.planets.get_data()[7].satellites.get_data().size(), 2);
	ASSERT_EQ(result_struct.planets.get_data()[7].satellites.get_data()[0].name, "Triton");
	ASSERT_EQ(result_struct.planets.get_data()[7].satellites.get_data()[0].radius, 1354);
	ASSERT_EQ(result_struct.planets.get_data()[7].satellites.get_data()[1].name, "Nereid");
	ASSERT_EQ(result_struct.planets.get_data()[7].satellites.get_data()[1].radius, 175);
}

}
