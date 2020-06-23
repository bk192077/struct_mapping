#include <cstdint>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/struct_mapping.h"

using ::testing::ElementsAre;

namespace {

struct Struct_empty {
};

TEST(struct_mapping_map_json_to_struct, empty_struct) {
	Struct_empty result_struct;
	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);
}

struct Struct_field_number_long_long {
	long long name_1;
	long long name_2;
	long long name_3;
	long long name_4;
	long long name_5;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_long_long) {
	Struct_field_number_long_long result_struct;
	
	struct_mapping::reg(&Struct_field_number_long_long::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_long_long::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_long_long::name_3, "name_3");
	struct_mapping::reg(&Struct_field_number_long_long::name_4, "name_4");
	struct_mapping::reg(&Struct_field_number_long_long::name_5, "name_5");

	std::istringstream json_data(R"json(
	{
		"name_1": -9223372036854775807,
		"name_2": 9223372036854775807,
		"name_3": 0,
		"name_4": 0.25,
		"name_5": -452.98
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -9223372036854775807);
	ASSERT_EQ(result_struct.name_2, 9223372036854775807);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, 0);
	ASSERT_EQ(result_struct.name_5, -452);
}

struct Struct_field_number_int {
	int name_1;
	int name_2;
	int name_3;
	int name_4;
	int name_5;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_int) {
	Struct_field_number_int result_struct;
	
	struct_mapping::reg(&Struct_field_number_int::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_int::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_int::name_3, "name_3");
	struct_mapping::reg(&Struct_field_number_int::name_4, "name_4");
	struct_mapping::reg(&Struct_field_number_int::name_5, "name_5");

	std::istringstream json_data(R"json(
	{
		"name_1": -2147483647,
		"name_2": 2147483647,
		"name_3": 0,
		"name_4": -152.86,
		"name_5": 6.8953
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -2147483647);
	ASSERT_EQ(result_struct.name_2, 2147483647);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, -152);
	ASSERT_EQ(result_struct.name_5, 6);
}

struct Struct_field_number_short {
	short name_1;
	short name_2;
	short name_3;
	short name_4;
	short name_5;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_short) {
	Struct_field_number_short result_struct;

	struct_mapping::reg(&Struct_field_number_short::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_short::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_short::name_3, "name_3");
	struct_mapping::reg(&Struct_field_number_short::name_4, "name_4");
	struct_mapping::reg(&Struct_field_number_short::name_5, "name_5");

	std::istringstream json_data(R"json(
	{
		"name_1": -32767,
		"name_2": 32767,
		"name_3": 0,
		"name_4": -12.365,
		"name_5": 128.449
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -32767);
	ASSERT_EQ(result_struct.name_2, 32767);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, -12);
	ASSERT_EQ(result_struct.name_5, 128);
}

struct Struct_field_number_char {
	char name_1;
	char name_2;
	char name_3;
	char name_4;
	char name_5;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_char) {
	Struct_field_number_char result_struct;

	struct_mapping::reg(&Struct_field_number_char::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_char::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_char::name_3, "name_3");
	struct_mapping::reg(&Struct_field_number_char::name_4, "name_4");
	struct_mapping::reg(&Struct_field_number_char::name_5, "name_5");

	std::istringstream json_data(R"json(
	{
		"name_1": -127,
		"name_2": 127,
		"name_3": 0,
		"name_4": -3.566,
		"name_5": 78.001
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, -127);
	ASSERT_EQ(result_struct.name_2, 127);
	ASSERT_EQ(result_struct.name_3, 0);
	ASSERT_EQ(result_struct.name_4, -3);
	ASSERT_EQ(result_struct.name_5, 78);
}

struct Struct_field_number_unsigned_int {
	unsigned int name_1;
	unsigned int name_2;
	unsigned int name_3;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_unsigned_int) {
	Struct_field_number_unsigned_int result_struct;

	struct_mapping::reg(&Struct_field_number_unsigned_int::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_unsigned_int::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_unsigned_int::name_3, "name_3");

	std::istringstream json_data(R"json(
	{
		"name_1": 0,
		"name_2": 4294967295,
		"name_3": 2.356
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, 0);
	ASSERT_EQ(result_struct.name_2, 4294967295);
	ASSERT_EQ(result_struct.name_3, 2);
}

struct Struct_field_number_unsigned_short {
	unsigned short name_1;
	unsigned short name_2;
	unsigned short name_3;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_unsigned_short) {
	Struct_field_number_unsigned_short result_struct;

	struct_mapping::reg(&Struct_field_number_unsigned_short::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_unsigned_short::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_unsigned_short::name_3, "name_3");

	std::istringstream json_data(R"json(
	{
		"name_1": 0,
		"name_2": 65535,
		"name_3": 45.032
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, 0);
	ASSERT_EQ(result_struct.name_2, 65535);
	ASSERT_EQ(result_struct.name_3, 45);
}

struct Struct_field_number_unsigned_char {
	unsigned char name_1;
	unsigned char name_2;
	unsigned char name_3;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_unsigned_char) {
	Struct_field_number_unsigned_char result_struct;

	struct_mapping::reg(&Struct_field_number_unsigned_char::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_unsigned_char::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_unsigned_char::name_3, "name_3");

	std::istringstream json_data(R"json(
	{
		"name_1": 0,
		"name_2": 255,
		"name_3": 46.01
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, 0);
	ASSERT_EQ(result_struct.name_2, 255);
	ASSERT_EQ(result_struct.name_3, 46);
}

struct Struct_field_number_float {
	double name_1;
	double name_2;
	double name_3;
	double name_4;
	double name_5;
	double name_6;
	double name_7;
	double name_8;
	double name_9;
};

TEST(struct_mapping_map_json_to_struct, struct_field_number_float) {
	Struct_field_number_float result_struct;

	struct_mapping::reg(&Struct_field_number_float::name_1, "name_1");
	struct_mapping::reg(&Struct_field_number_float::name_2, "name_2");
	struct_mapping::reg(&Struct_field_number_float::name_3, "name_3");
	struct_mapping::reg(&Struct_field_number_float::name_4, "name_4");
	struct_mapping::reg(&Struct_field_number_float::name_5, "name_5");
	struct_mapping::reg(&Struct_field_number_float::name_6, "name_6");
	struct_mapping::reg(&Struct_field_number_float::name_7, "name_7");
	struct_mapping::reg(&Struct_field_number_float::name_8, "name_8");
	struct_mapping::reg(&Struct_field_number_float::name_9, "name_9");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

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

struct Struct_field_string {
	std::string name_1;
	std::string name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_string) {
	Struct_field_string result_struct;

	struct_mapping::reg(&Struct_field_string::name_1, "name_1");
	struct_mapping::reg(&Struct_field_string::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": "value_1",
		"name_2": ""
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, "value_1");
	ASSERT_EQ(result_struct.name_2, "");
}

struct Struct_field_array_of_bool {
	std::list<bool> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_bool) {
	Struct_field_array_of_bool result_struct;

	struct_mapping::reg(&Struct_field_array_of_bool::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": [true, false, false, true, true]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(true, false, false, true, true));
}

struct Struct_field_array_of_number_long_long {
	std::vector<long long> name_1;
	std::list<long long> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_long_long) {
	Struct_field_array_of_number_long_long result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_long_long::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_long_long::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": [42, -421, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1],
		"name_2": [43, -421, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(42, -421, 3, -89, 0, 0, 0, 1, -1));
	ASSERT_THAT(result_struct.name_2, ElementsAre(43, -421, 3, -89, 0, 0, 0, 1, -1));
}

struct Struct_field_array_of_number_int {
	std::vector<int> name_1;
	std::list<int> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_int) {
	Struct_field_array_of_number_int result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_int::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_int::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": [42, -421, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1],
		"name_2": [43, -421, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(42, -421, 3, -89, 0, 0, 0, 1, -1));
	ASSERT_THAT(result_struct.name_2, ElementsAre(43, -421, 3, -89, 0, 0, 0, 1, -1));
}

struct Struct_field_array_of_number_short {
	std::vector<short> name_1;
	std::list<short> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_short) {
	Struct_field_array_of_number_short result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_short::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_short::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": [42, -421, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1],
		"name_2": [43, -421, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(42, -421, 3, -89, 0, 0, 0, 1, -1));
	ASSERT_THAT(result_struct.name_2, ElementsAre(43, -421, 3, -89, 0, 0, 0, 1, -1));
}

struct Struct_field_array_of_number_char {
	std::vector<char> name_1;
	std::list<char> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_char) {
	Struct_field_array_of_number_char result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_char::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_char::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": [42, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1],
		"name_2": [43, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(42, -21, 3, -89, 0, 0, 0, 1, -1));
	ASSERT_THAT(result_struct.name_2, ElementsAre(43, -21, 3, -89, 0, 0, 0, 1, -1));
}

struct Struct_field_array_of_number_float {
	std::vector<float> name_1;
	std::list<float> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_float) {
	Struct_field_array_of_number_float result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_float::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_float::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": [42, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1],
		"name_2": [43, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(42, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1));
	ASSERT_THAT(result_struct.name_2, ElementsAre(43, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1));
}

struct Struct_field_array_of_number_double {
	std::vector<double> name_1;
	std::list<double> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_double) {
	Struct_field_array_of_number_double result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_double::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_double::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": [42, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1],
		"name_2": [43, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre(42, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1));
	ASSERT_THAT(result_struct.name_2, ElementsAre(43, -21, 3.1425, -89.458, 0.03901, -0.3006, 0, 1, -1));
}

struct Struct_field_array_of_number_string {
	std::vector<std::string> name_1;
	std::list<std::string> name_2;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_number_string) {
	Struct_field_array_of_number_string result_struct;

	struct_mapping::reg(&Struct_field_array_of_number_string::name_1, "name_1");
	struct_mapping::reg(&Struct_field_array_of_number_string::name_2, "name_2");

	std::istringstream json_data(R"json(
	{
		"name_1": ["14", "12", "12"],
		"name_2": ["24", "22", "22"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.name_1, ElementsAre("14", "12", "12"));
	ASSERT_THAT(result_struct.name_2, ElementsAre("24", "22", "22"));
}

struct Struct_field_bool_single {
	bool name_2;
};

struct Struct_field_array_of_Struct_field_bool {
	std::vector<Struct_field_bool_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_bool) {
	Struct_field_array_of_Struct_field_bool result_struct;

	struct_mapping::reg(&Struct_field_bool_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_bool::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);

	ASSERT_TRUE(result_struct.name_1[0].name_2);
	ASSERT_FALSE(result_struct.name_1[1].name_2);
	ASSERT_FALSE(result_struct.name_1[2].name_2);
}

struct Struct_field_char_single {
	char name_2;
};

struct Struct_field_array_of_Struct_field_char {
	std::vector<Struct_field_char_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_char) {
	Struct_field_array_of_Struct_field_char result_struct;

	struct_mapping::reg(&Struct_field_char_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_char::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 6);

	ASSERT_EQ(result_struct.name_1[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1[2].name_2, -1);
	ASSERT_EQ(result_struct.name_1[3].name_2, 1);
	ASSERT_EQ(result_struct.name_1[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1[5].name_2, 26);
}

struct Struct_field_short_single {
	short name_2;
};

struct Struct_field_array_of_Struct_field_short {
	std::vector<Struct_field_short_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_short) {
	Struct_field_array_of_Struct_field_short result_struct;

	struct_mapping::reg(&Struct_field_short_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_short::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 6);

	ASSERT_EQ(result_struct.name_1[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1[2].name_2, -1);
	ASSERT_EQ(result_struct.name_1[3].name_2, 1);
	ASSERT_EQ(result_struct.name_1[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1[5].name_2, 26);
}

struct Struct_field_int_single {
	int name_2;
};

struct Struct_field_array_of_Struct_field_int {
	std::vector<Struct_field_int_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_int) {
	Struct_field_array_of_Struct_field_int result_struct;

	struct_mapping::reg(&Struct_field_int_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_int::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 6);

	ASSERT_EQ(result_struct.name_1[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1[2].name_2, -102);
	ASSERT_EQ(result_struct.name_1[3].name_2, 2365);
	ASSERT_EQ(result_struct.name_1[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1[5].name_2, 26);
}

struct Struct_field_long_long_single {
	long long name_2;
};

struct Struct_field_array_of_Struct_field_long_long {
	std::vector<Struct_field_long_long_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_long_long) {
	Struct_field_array_of_Struct_field_long_long result_struct;

	struct_mapping::reg(&Struct_field_long_long_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_long_long::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 6);

	ASSERT_EQ(result_struct.name_1[0].name_2, 0);
	ASSERT_EQ(result_struct.name_1[1].name_2, 0);
	ASSERT_EQ(result_struct.name_1[2].name_2, -102);
	ASSERT_EQ(result_struct.name_1[3].name_2, 2365);
	ASSERT_EQ(result_struct.name_1[4].name_2, -10);
	ASSERT_EQ(result_struct.name_1[5].name_2, 26);
}

struct Struct_field_float_single {
	float name_2;
};

struct Struct_field_array_of_Struct_field_float {
	std::vector<Struct_field_float_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_float) {
	Struct_field_array_of_Struct_field_float result_struct;

	struct_mapping::reg(&Struct_field_float_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_float::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 6);

	ASSERT_EQ(result_struct.name_1[0].name_2, 0.0f);
	ASSERT_EQ(result_struct.name_1[1].name_2, 0.0f);
	ASSERT_EQ(result_struct.name_1[2].name_2, -102.0f);
	ASSERT_EQ(result_struct.name_1[3].name_2, 2365.0f);
	ASSERT_EQ(result_struct.name_1[4].name_2, -10.123f);
	ASSERT_EQ(result_struct.name_1[5].name_2, 26.14f);
}

struct Struct_field_double_single {
	double name_2;
};

struct Struct_field_array_of_Struct_field_double {
	std::vector<Struct_field_double_single> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_double) {
	Struct_field_array_of_Struct_field_double result_struct;

	struct_mapping::reg(&Struct_field_double_single::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_double::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 6);

	ASSERT_EQ(result_struct.name_1[0].name_2, 0.0);
	ASSERT_EQ(result_struct.name_1[1].name_2, 0.0);
	ASSERT_EQ(result_struct.name_1[2].name_2, -102);
	ASSERT_EQ(result_struct.name_1[3].name_2, 2365);
	ASSERT_EQ(result_struct.name_1[4].name_2, -10.123);
	ASSERT_EQ(result_struct.name_1[5].name_2, 26.140);
}

struct Struct_field_string_one {
	std::string name_2;
};

struct Struct_field_array_of_Struct_field_string {
	std::vector<Struct_field_string_one> name_1;
};

TEST(struct_mapping_map_json_to_struct, struct_field_array_of_Struct_field_string) {
	Struct_field_array_of_Struct_field_string result_struct;

	struct_mapping::reg(&Struct_field_string_one::name_2, "name_2");
	struct_mapping::reg(&Struct_field_array_of_Struct_field_string::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);

	ASSERT_EQ(result_struct.name_1[0].name_2, "first_string");
	ASSERT_EQ(result_struct.name_1[1].name_2, "");
	ASSERT_EQ(result_struct.name_1[2].name_2, "");
}

struct Struct_field_array_of_array_of_bool {
	std::vector<std::list<bool>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_bool) {
	Struct_field_array_of_array_of_bool result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_bool::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(true, false, true));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(false, true));
}

struct Struct_field_array_of_array_of_char {
	std::vector<std::list<char>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_char) {
	Struct_field_array_of_array_of_char result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_char::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(123, 0, -123, 0, -45));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(39, 0, -223, 0, -145, 28));
}

struct Struct_field_array_of_array_of_short {
	std::vector<std::list<short>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_short) {
	Struct_field_array_of_array_of_short result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_short::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				223,
				0,
				-223,
				0.2,
				-245.689
			],
			[
			],
			[
				239,
				0,
				-2223,
				0.2,
				-245.689,
				28
			]
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(223, 0, -223, 0, -245));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(239, 0, -2223, 0, -245, 28));
}

struct Struct_field_array_of_array_of_int {
	std::vector<std::list<int>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_int) {
	Struct_field_array_of_array_of_int result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_int::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				223,
				0,
				-223,
				0.2,
				-245.689
			],
			[
			],
			[
				239,
				0,
				-2223,
				0.2,
				-245.689,
				28
			]
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(223, 0, -223, 0, -245));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(239, 0, -2223, 0, -245, 28));
}

struct Struct_field_array_of_array_of_long_long {
	std::vector<std::list<long long>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_long_long) {
	Struct_field_array_of_array_of_long_long result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_long_long::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				223,
				0,
				-223,
				0.2,
				-245.689
			],
			[
			],
			[
				239,
				0,
				-2223,
				0.2,
				-245.689,
				28
			]
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(223, 0, -223, 0, -245));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(239, 0, -2223, 0, -245, 28));
}

struct Struct_field_array_of_array_of_float {
	std::vector<std::list<float>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_float) {
	Struct_field_array_of_array_of_float result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_float::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				223,
				0,
				-223,
				0.2,
				-245.689
			],
			[
			],
			[
				239,
				0,
				-2223,
				0.2,
				-245.689,
				28
			]
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(223, 0, -223, 0.2, -245.689));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(239, 0, -2223, 0.2, -245.689, 28));
}

struct Struct_field_array_of_array_of_double {
	std::vector<std::list<double>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_double) {
	Struct_field_array_of_array_of_double result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_double::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": [
			[
				223,
				0,
				-223,
				0.2,
				-245.689
			],
			[
			],
			[
				239,
				0,
				-2223,
				0.2,
				-245.689,
				28
			]
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre(223, 0, -223, 0.2, -245.689));
	ASSERT_THAT(result_struct.name_1[1], ElementsAre());
	ASSERT_THAT(result_struct.name_1[2], ElementsAre(239, 0, -2223, 0.2, -245.689, 28));
}

struct Struct_field_array_of_array_of_string {
	std::vector<std::list<std::string>> name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_field_array_of_array_of_string) {
	Struct_field_array_of_array_of_string result_struct;

	struct_mapping::reg(&Struct_field_array_of_array_of_string::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.size(), 3);
	ASSERT_THAT(result_struct.name_1[0], ElementsAre("first string", "", "second_string"));
	ASSERT_EQ(result_struct.name_1[1].size(), 0);
	ASSERT_THAT(result_struct.name_1[2], ElementsAre("", "third_string"));
}

struct Struct_Struct_field_bool_3 {
	bool name_3;
	bool name_4;
};

struct Struct_Struct_field_bool_2 {
	Struct_Struct_field_bool_3 name_2;
};

struct Struct_Struct_field_bool_1 {
	Struct_Struct_field_bool_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_bool) {
	Struct_Struct_field_bool_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_bool_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_bool_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_bool_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_bool_1::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_FALSE(result_struct.name_1.name_2.name_3);
	ASSERT_TRUE(result_struct.name_1.name_2.name_4);
}

struct Struct_Struct_field_char_3 {
	char name_3;
	char name_4;
};

struct Struct_Struct_field_char_2 {
	Struct_Struct_field_char_3 name_2;
};

struct Struct_Struct_field_char_1 {
	Struct_Struct_field_char_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_char) {
	Struct_Struct_field_char_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_char_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_char_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_char_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_char_1::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, 9);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, -25);
}

struct Struct_Struct_field_short_3 {
	short name_3;
	short name_4;
};

struct Struct_Struct_field_short_2 {
	Struct_Struct_field_short_3 name_2;
};

struct Struct_Struct_field_short_1 {
	Struct_Struct_field_short_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_short) {
	Struct_Struct_field_short_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_short_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_short_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_short_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_short_1::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -19);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 2598);
}

struct Struct_Struct_field_int_3 {
	int name_3;
	int name_4;
};

struct Struct_Struct_field_int_2 {
	Struct_Struct_field_int_3 name_2;
};

struct Struct_Struct_field_int_1 {
	Struct_Struct_field_int_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_int) {
	Struct_Struct_field_int_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_int_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_int_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_int_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_int_1::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": -119.01856,
				"name_4": 12598
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -119);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 12598);
}

struct Struct_Struct_field_long_long_3 {
	long long name_3;
	long long name_4;
};

struct Struct_Struct_field_long_long_2 {
	Struct_Struct_field_long_long_3 name_2;
};

struct Struct_Struct_field_long_long_1 {
	Struct_Struct_field_long_long_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_long_long) {
	Struct_Struct_field_long_long_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_long_long_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_long_long_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_long_long_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_long_long_1::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": -1119.01856,
				"name_4": 112598
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -1119);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 112598);
}

struct Struct_Struct_field_float_3 {
	float name_3;
	float name_4;
};

struct Struct_Struct_field_float_2 {
	Struct_Struct_field_float_3 name_2;
};

struct Struct_Struct_field_float_1 {
	Struct_Struct_field_float_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_float) {
	Struct_Struct_field_float_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_float_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_float_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_float_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_float_1::name_1, "name_1");

	std::istringstream json_data(R"json(
	{
		"name_1": {
			"name_2": {
				"name_3": -19.0186,
				"name_4": 2598
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -19.0186f);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 2598.0f);
}

struct Struct_Struct_field_double_3 {
	double name_3;
	double name_4;
};

struct Struct_Struct_field_double_2 {
	Struct_Struct_field_double_3 name_2;
};

struct Struct_Struct_field_double_1 {
	Struct_Struct_field_double_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_double) {
	Struct_Struct_field_double_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_double_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_double_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_double_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_double_1::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, -19.01856);
	ASSERT_EQ(result_struct.name_1.name_2.name_4, 2598);
}

struct Struct_Struct_field_string_3 {
	std::string name_3;
	std::string name_4;
};

struct Struct_Struct_field_string_2 {
	Struct_Struct_field_string_3 name_2;
};

struct Struct_Struct_field_string_1 {
	Struct_Struct_field_string_2 name_1;
};

TEST(struct_mapping_map_json_to_struct, Struct_Struct_field_string) {
	Struct_Struct_field_string_1 result_struct;

	struct_mapping::reg(&Struct_Struct_field_string_3::name_3, "name_3");
	struct_mapping::reg(&Struct_Struct_field_string_3::name_4, "name_4");
	struct_mapping::reg(&Struct_Struct_field_string_2::name_2, "name_2");
	struct_mapping::reg(&Struct_Struct_field_string_1::name_1, "name_1");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1.name_2.name_3, "first_string");
	ASSERT_EQ(result_struct.name_1.name_2.name_4, "");
}

struct Struct_Struct_field_string_0 {
	std::vector<Struct_Struct_field_string_1> name_0;
};

TEST(struct_mapping_map_json_to_struct, ManagedArray_Struct_Struct_field_string) {
	Struct_Struct_field_string_0 result_struct;

	struct_mapping::reg(&Struct_Struct_field_string_0::name_0, "name_0");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_0.size(), 3);

	ASSERT_EQ(result_struct.name_0[0].name_1.name_2.name_3, "first_string");
	ASSERT_EQ(result_struct.name_0[0].name_1.name_2.name_4, "");

	ASSERT_EQ(result_struct.name_0[1].name_1.name_2.name_3, "");
	ASSERT_EQ(result_struct.name_0[1].name_1.name_2.name_4, "");

	ASSERT_EQ(result_struct.name_0[2].name_1.name_2.name_3, "");
	ASSERT_EQ(result_struct.name_0[2].name_1.name_2.name_4, "second_string");
}

struct Struct_identical_field_names_and_types_in_structures_1 {
	std::string name_1;
	int name_2;
	bool name_3;
};

struct Struct_identical_field_names_and_types_in_structures_2 {
	std::string name_1;
	int name_2;
	double name_3;
};

struct Struct_identical_field_names_and_types_in_structures_3 {
	std::string name_1;
	Struct_identical_field_names_and_types_in_structures_1 name_2;
	Struct_identical_field_names_and_types_in_structures_2 name_3;
};

TEST(struct_mapping_map_json_to_struct, identical_field_names_and_types_in_structures) {
	Struct_identical_field_names_and_types_in_structures_3 result_struct;

	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_1::name_1, "name_1");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_1::name_2, "name_2");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_1::name_3, "name_3");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_2::name_1, "name_1");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_2::name_2, "name_2");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_2::name_3, "name_3");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_3::name_1, "name_1");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_3::name_2, "name_2");
	struct_mapping::reg(&Struct_identical_field_names_and_types_in_structures_3::name_3, "name_3");

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

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name_1, "first_string");
	ASSERT_EQ(result_struct.name_2.name_1, "second_string");
	ASSERT_EQ(result_struct.name_2.name_2, 42);
	ASSERT_TRUE(result_struct.name_2.name_3);
	ASSERT_EQ(result_struct.name_3.name_1, "third_string");
	ASSERT_EQ(result_struct.name_3.name_2, 93);
	ASSERT_EQ(result_struct.name_3.name_3, -0.23);
}

struct Struct_multiple_times_2 {
	std::string name_2;
	bool name_3;
};

struct Struct_multiple_times_1 {
	std::vector<Struct_multiple_times_2> name_1;
};

TEST(struct_mapping_map_json_to_struct, multiple_times_same_struct) {
	Struct_multiple_times_1 result_struct_1;
	Struct_multiple_times_1 result_struct_2;

	struct_mapping::reg(&Struct_multiple_times_2::name_2, "name_2");
	struct_mapping::reg(&Struct_multiple_times_2::name_3, "name_3");
	struct_mapping::reg(&Struct_multiple_times_1::name_1, "name_1");

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
	
	struct_mapping::map_json_to_struct(result_struct_1, json_data_1);
	struct_mapping::map_json_to_struct(result_struct_2, json_data_2);

	ASSERT_EQ(result_struct_1.name_1.size(), 2);
	ASSERT_EQ(result_struct_1.name_1[0].name_2, "first_string");
	ASSERT_TRUE(result_struct_1.name_1[0].name_3);
	ASSERT_EQ(result_struct_1.name_1[1].name_2, "second_string");
	ASSERT_FALSE(result_struct_1.name_1[1].name_3);

	ASSERT_EQ(result_struct_2.name_1.size(), 3);
	ASSERT_EQ(result_struct_2.name_1[0].name_2, "third_string");
	ASSERT_TRUE(result_struct_2.name_1[0].name_3);
	ASSERT_EQ(result_struct_2.name_1[1].name_2, "fourth_string");
	ASSERT_TRUE(result_struct_2.name_1[1].name_3);
	ASSERT_EQ(result_struct_2.name_1[2].name_2, "fifth_string");
	ASSERT_FALSE(result_struct_2.name_1[2].name_3);
}

}
