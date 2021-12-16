#include "struct_mapping/struct_mapping.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cstdint>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::Pair;
using ::testing::UnorderedElementsAre;

namespace
{

TEST(map_json_to_struct, empty)
{
	struct map_json_to_struct_empty {};

	map_json_to_struct_empty result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);
}

TEST(map_json_to_struct, bool_integer_floating_point_string)
{
	struct map_json_to_struct_bool_integer_floating_point_string
	{
		bool member_bool;
		char member_char;
		unsigned char member_unsigned_char;
		short member_short;
		unsigned short member_unsigned_short;
		int member_int;
		unsigned int member_unsigned_int;
		long member_long;
		long long member_long_long;
		float member_float;
		double member_double;
		std::string member_string;
	};

	map_json_to_struct_bool_integer_floating_point_string result_struct;
	
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_bool, "member_bool");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_char, "member_char");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_unsigned_char,
		"member_unsigned_char");

	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_short, "member_short");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_unsigned_short,
		"member_unsigned_short");

	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_int, "member_int");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_unsigned_int,
		"member_unsigned_int");

	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_long, "member_long");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_long_long,	"member_long_long");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_float, "member_float");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_double, "member_double");
	struct_mapping::reg(&map_json_to_struct_bool_integer_floating_point_string::member_string, "member_string");

	std::istringstream json_data(R"json(
	{
		"member_bool": true,
		"member_char": -1,
		"member_unsigned_char": 2,
		"member_short": -3,
		"member_unsigned_short": 4,
		"member_int": -5,
		"member_unsigned_int": 6,
		"member_long": -7,
		"member_long_long": 8,
		"member_float": -9.1,
		"member_double": 10.0,
		"member_string": "String"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_bool, true);
	EXPECT_EQ(result_struct.member_char, -1);
	EXPECT_EQ(result_struct.member_unsigned_char, 2);
	EXPECT_EQ(result_struct.member_short, -3);
	EXPECT_EQ(result_struct.member_unsigned_short, 4);
	EXPECT_EQ(result_struct.member_int, -5);
	EXPECT_EQ(result_struct.member_unsigned_int, 6);
	EXPECT_EQ(result_struct.member_long, -7);
	EXPECT_EQ(result_struct.member_long_long, 8);
	EXPECT_EQ(result_struct.member_float, -9.1f);
	EXPECT_EQ(result_struct.member_double, 10.0);
	EXPECT_EQ(result_struct.member_string, "String");
}

TEST(map_json_to_struct, member_list)
{
	struct map_json_to_struct_member_list
	{
		std::list<int> member_list_int;
		std::list<float> member_list_float;
		std::list<std::string> member_list_string;
	};

	map_json_to_struct_member_list result_struct;

	struct_mapping::reg(&map_json_to_struct_member_list::member_list_int, "member_list_int");
	struct_mapping::reg(&map_json_to_struct_member_list::member_list_float, "member_list_float");
	struct_mapping::reg(&map_json_to_struct_member_list::member_list_string, "member_list_string");

	std::istringstream json_data(R"json(
	{
		"member_list_int": [-10, -1, 0, 1, 10],
		"member_list_float": [-10.5, -1, 0, 1, 10.5],
		"member_list_string": ["first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_list_int, ElementsAre(-10, -1, 0, 1, 10));
	ASSERT_THAT(result_struct.member_list_float, ElementsAre(-10.5f, -1.0f, 0.0f, 1.0f, 10.5f));
	ASSERT_THAT(result_struct.member_list_string, ElementsAre("first", "second"));
}

TEST(map_json_to_struct, member_vector)
{
	struct map_json_to_struct_member_vector
	{
		std::vector<int> member_vector_int;
		std::vector<float> member_vector_float;
		std::vector<std::string> member_vector_string;
	};

	map_json_to_struct_member_vector result_struct;

	struct_mapping::reg(&map_json_to_struct_member_vector::member_vector_int, "member_vector_int");
	struct_mapping::reg(&map_json_to_struct_member_vector::member_vector_float, "member_vector_float");
	struct_mapping::reg(&map_json_to_struct_member_vector::member_vector_string, "member_vector_string");

	std::istringstream json_data(R"json(
	{
		"member_vector_int": [-10, -1, 0, 1, 10],
		"member_vector_float": [-10.5, -1, 0, 1, 10.5],
		"member_vector_string": ["first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_vector_int, ElementsAre(-10, -1, 0, 1, 10));
	ASSERT_THAT(result_struct.member_vector_float, ElementsAre(-10.5f, -1.0f, 0.0f, 1.0f, 10.5f));
	ASSERT_THAT(result_struct.member_vector_string, ElementsAre("first", "second"));
}

TEST(map_json_to_struct, member_map)
{
	struct map_json_to_struct_member_map
	{
		std::map<std::string, int> member_map_int;
		std::map<std::string, float> member_map_float;
		std::map<std::string, std::string> member_map_string;
	};

	map_json_to_struct_member_map result_struct;

	struct_mapping::reg(&map_json_to_struct_member_map::member_map_int, "member_map_int");
	struct_mapping::reg(&map_json_to_struct_member_map::member_map_float, "member_map_float");
	struct_mapping::reg(&map_json_to_struct_member_map::member_map_string, "member_map_string");

	std::istringstream json_data(R"json(
	{
		"member_map_int": {
			"first": -10,
			"second": 0,
			"third": 10
		},
		"member_map_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_map_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_map_int, ElementsAre(Pair("first", -10), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(
		result_struct.member_map_float,
		ElementsAre(Pair("first", -10.5f), Pair("second", 1.0f), Pair("third", 10.5f)));
	ASSERT_THAT(
		result_struct.member_map_string,
		ElementsAre(Pair("first", "first_string"), Pair("second", "second_string"), Pair("third", "third_string")));
}

TEST(map_json_to_struct, member_unordered_map)
{
	struct map_json_to_struct_member_unordered_map
	{
		std::unordered_map<std::string, int> member_unordered_map_int;
		std::unordered_map<std::string, float> member_unordered_map_float;
		std::unordered_map<std::string, std::string> member_unordered_map_string;
	};

	map_json_to_struct_member_unordered_map result_struct;

	struct_mapping::reg(&map_json_to_struct_member_unordered_map::member_unordered_map_int, "member_unordered_map_int");
	struct_mapping::reg(&map_json_to_struct_member_unordered_map::member_unordered_map_float,
		"member_unordered_map_float");

	struct_mapping::reg(&map_json_to_struct_member_unordered_map::member_unordered_map_string,
		"member_unordered_map_string");

	std::istringstream json_data(R"json(
	{
		"member_unordered_map_int": {
			"first": -10,
			"second": 0,
			"third": 10
		},
		"member_unordered_map_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_unordered_map_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(
		result_struct.member_unordered_map_int,
		UnorderedElementsAre(Pair("first", -10), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(
		result_struct.member_unordered_map_float,
		UnorderedElementsAre(Pair("first", -10.5f), Pair("second", 1.0f), Pair("third", 10.5f)));
	ASSERT_THAT(
		result_struct.member_unordered_map_string,
		UnorderedElementsAre(
			Pair("first", "first_string"),
			Pair("second", "second_string"),
			Pair("third", "third_string")));
}

TEST(map_json_to_struct, member_multimap)
{
	struct map_json_to_struct_member_multimap
	{
		std::multimap<std::string, int> member_multimap_int;
		std::multimap<std::string, float> member_multimap_float;
		std::multimap<std::string, std::string> member_multimap_string;
	};

	map_json_to_struct_member_multimap result_struct;

	struct_mapping::reg(&map_json_to_struct_member_multimap::member_multimap_int, "member_multimap_int");
	struct_mapping::reg(&map_json_to_struct_member_multimap::member_multimap_float, "member_multimap_float");
	struct_mapping::reg(&map_json_to_struct_member_multimap::member_multimap_string, "member_multimap_string");

	std::istringstream json_data(R"json(
	{
		"member_multimap_int": {
			"first": -10,
			"first": 20,
			"second": 0,
			"third": 10
		},
		"member_multimap_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_multimap_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(
		result_struct.member_multimap_int,
		ElementsAre(Pair("first", -10), Pair("first", 20), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(
		result_struct.member_multimap_float,
		ElementsAre(Pair("first", -10.5f), Pair("second", 1.0f), Pair("third", 10.5f)));
	ASSERT_THAT(
		result_struct.member_multimap_string,
		ElementsAre(Pair("first", "first_string"), Pair("second", "second_string"), Pair("third", "third_string")));
}

TEST(map_json_to_struct, member_unordered_multimap)
{
	struct map_json_to_struct_member_unordered_multimap
	{
		std::unordered_multimap<std::string, int> member_unordered_multimap_int;
		std::unordered_multimap<std::string, float> member_unordered_multimap_float;
		std::unordered_multimap<std::string, std::string> member_unordered_multimap_string;
	};

	map_json_to_struct_member_unordered_multimap result_struct;

	struct_mapping::reg(&map_json_to_struct_member_unordered_multimap::member_unordered_multimap_int,
		"member_unordered_multimap_int");

	struct_mapping::reg(&map_json_to_struct_member_unordered_multimap::member_unordered_multimap_float,
		"member_unordered_multimap_float");

	struct_mapping::reg(&map_json_to_struct_member_unordered_multimap::member_unordered_multimap_string,
		"member_unordered_multimap_string");

	std::istringstream json_data(R"json(
	{
		"member_unordered_multimap_int": {
			"first": -10,
			"first": 20,
			"second": 0,
			"third": 10
		},
		"member_unordered_multimap_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_unordered_multimap_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(
		result_struct.member_unordered_multimap_int,
		UnorderedElementsAre(Pair("first", -10), Pair("first", 20), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(
		result_struct.member_unordered_multimap_float,
		UnorderedElementsAre(Pair("first", -10.5f), Pair("second", 1.0f), Pair("third", 10.5f)));
	ASSERT_THAT(
		result_struct.member_unordered_multimap_string,
		UnorderedElementsAre(
			Pair("first", "first_string"),
			Pair("second", "second_string"),
			Pair("third", "third_string")));
}

TEST(map_json_to_struct, member_struct)
{
	struct map_json_to_struct_member_struct_A
	{
		std::string member_string;
	};

	struct map_json_to_struct_member_struct_B
	{
		map_json_to_struct_member_struct_A member_a;
	};

	map_json_to_struct_member_struct_B result_struct;
	
	struct_mapping::reg(&map_json_to_struct_member_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_struct_B::member_a, "member_a");

	std::istringstream json_data(R"json(
	{
		"member_a": {
			"member_string": "String"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_a.member_string, "String");
}

TEST(map_json_to_struct, member_struct_struct)
{
	struct map_json_to_struct_member_struct_struct_A
	{
		std::string member_string;
	};

	struct map_json_to_struct_member_struct_struct_B
	{
		map_json_to_struct_member_struct_struct_A member_a;
	};

	struct map_json_to_struct_member_struct_struct_C
	{
		map_json_to_struct_member_struct_struct_B member_b;
	};

	map_json_to_struct_member_struct_struct_C result_struct;
	
	struct_mapping::reg(&map_json_to_struct_member_struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_struct_struct_B::member_a, "member_a");
	struct_mapping::reg(&map_json_to_struct_member_struct_struct_C::member_b, "member_b");

	std::istringstream json_data(R"json(
	{
		"member_b": {
			"member_a": {
				"member_string": "String"
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_b.member_a.member_string, "String");
}

TEST(map_json_to_struct, member_vector_struct)
{
	struct map_json_to_struct_member_vector_struct_A
	{
		std::string member_string;
	};

	struct map_json_to_struct_member_vector_struct_B
	{
		std::vector<map_json_to_struct_member_vector_struct_A> member_vector_a;
	};

	map_json_to_struct_member_vector_struct_B result_struct;
	
	struct_mapping::reg(&map_json_to_struct_member_vector_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_vector_struct_B::member_vector_a, "member_vector_a");

	std::istringstream json_data(R"json(
	{
		"member_vector_a": [
			{
				"member_string": "first"
			},
			{
				"member_string": "second"
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_vector_a.size(), 2);
	EXPECT_EQ(result_struct.member_vector_a[0].member_string, "first");
	EXPECT_EQ(result_struct.member_vector_a[1].member_string, "second");
}

TEST(map_json_to_struct, member_vector_struct_struct)
{
	struct map_json_to_struct_member_vector_struct_struct_A
	{
		std::string member_string;
	};

	struct map_json_to_struct_member_vector_struct_struct_B
	{
		map_json_to_struct_member_vector_struct_struct_A member_struct_a;
	};

	struct map_json_to_struct_member_vector_struct_struct_C
	{
		std::vector<map_json_to_struct_member_vector_struct_struct_B> member_vector_struct_b;
	};

	map_json_to_struct_member_vector_struct_struct_C result_struct;
	
	struct_mapping::reg(&map_json_to_struct_member_vector_struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_vector_struct_struct_B::member_struct_a, "member_struct_a");
	struct_mapping::reg(&map_json_to_struct_member_vector_struct_struct_C::member_vector_struct_b,
		"member_vector_struct_b");

	std::istringstream json_data(R"json(
	{
		"member_vector_struct_b": [
			{
				"member_struct_a": {
					"member_string": "first"
				}
			},
			{
				"member_struct_a": {
					"member_string": "second"
				}
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_vector_struct_b.size(), 2);
	EXPECT_EQ(result_struct.member_vector_struct_b[0].member_struct_a.member_string, "first");
	EXPECT_EQ(result_struct.member_vector_struct_b[1].member_struct_a.member_string, "second");
}

TEST(map_json_to_struct, member_map_struct)
{
	struct map_json_to_struct_member_map_struct_A
	{
		std::string member_string;
	};

	struct map_json_to_struct_member_map_struct_B
	{
		std::map<std::string, map_json_to_struct_member_map_struct_A> member_map_a;
	};

	map_json_to_struct_member_map_struct_B result_struct;
	
	struct_mapping::reg(&map_json_to_struct_member_map_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_map_struct_B::member_map_a, "member_map_a");

	std::istringstream json_data(R"json(
	{
		"member_map_a": {
			"1": {
				"member_string": "first"
			},
			"2": {
				"member_string": "second"
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_map_a.size(), 2);
	EXPECT_EQ(result_struct.member_map_a["1"].member_string, "first");
	EXPECT_EQ(result_struct.member_map_a["2"].member_string, "second");
}

TEST(map_json_to_struct, member_map_struct_struct)
{
	struct map_json_to_struct_member_map_struct_struct_A
	{
		std::string member_string;
	};

	struct map_json_to_struct_member_map_struct_struct_B
	{
		map_json_to_struct_member_map_struct_struct_A member_struct_a;
	};

	struct map_json_to_struct_member_map_struct_struct_C
	{
		std::map<std::string, map_json_to_struct_member_map_struct_struct_B> member_map_struct_b;
	};

	map_json_to_struct_member_map_struct_struct_C result_struct;
	
	struct_mapping::reg(&map_json_to_struct_member_map_struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_map_struct_struct_B::member_struct_a, "member_struct_a");
	struct_mapping::reg(&map_json_to_struct_member_map_struct_struct_C::member_map_struct_b, "member_map_struct_b");

	std::istringstream json_data(R"json(
	{
		"member_map_struct_b": {
			"1": {
				"member_struct_a": {
					"member_string": "first"
				}
			},
			"2": {
				"member_struct_a": {
					"member_string": "second"
				}
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_map_struct_b.size(), 2);
	EXPECT_EQ(result_struct.member_map_struct_b["1"].member_struct_a.member_string, "first");
	EXPECT_EQ(result_struct.member_map_struct_b["2"].member_struct_a.member_string, "second");
}

TEST(map_json_to_struct, enum)
{
	enum map_json_to_struct_enum
	{
		Enum_v1,
		Enum_v2,
		Enum_v3
	};

	struct map_json_to_struct_enum_struct
	{
		map_json_to_struct_enum value;
	};

	struct_mapping::MemberString<map_json_to_struct_enum>::set(
		[] (const std::string& value)
		{
			if (value == "Enum_v1")
			{
				return Enum_v1;
			}
			else if (value == "Enum_v2")
			{
				return Enum_v2;
			}
			else if (value == "Enum_v3")
			{
				return Enum_v3;
			} 

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum");
		},
		[] (map_json_to_struct_enum value)
		{
			switch (value)
			{
			case Enum_v1: return "Enum_v1";
			case Enum_v2: return "Enum_v2";
			case Enum_v3: return "Enum_v3";
			}

			throw struct_mapping::StructMappingException("bad convert Enum '" + std::to_string(value) + "' to string");
		});

	map_json_to_struct_enum_struct result_struct;

	struct_mapping::reg(&map_json_to_struct_enum_struct::value, "value");

	std::istringstream json_data(R"json(
	{
		"value": "Enum_v2"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value, Enum_v2);
}

TEST(map_json_to_struct, enum_list)
{
	enum class map_json_to_struct_enum_list
	{
		v1,
		v2,
		v3
	};

	struct map_json_to_struct_enum_list_struct
	{
		std::list<map_json_to_struct_enum_list> values;
	};

	struct_mapping::MemberString<map_json_to_struct_enum_list>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return map_json_to_struct_enum_list::v1;
			}
			else if (value == "v2")
			{
				return map_json_to_struct_enum_list::v2;
			}
			else if (value == "v3")
			{
				return map_json_to_struct_enum_list::v3;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to map_json_to_struct_enum_list");
		},
		[] (map_json_to_struct_enum_list value)
		{
			switch (value)
			{
			case map_json_to_struct_enum_list::v1: return "v1";
			case map_json_to_struct_enum_list::v2: return "v2";
			default: return "v3";
			}
		});

	map_json_to_struct_enum_list_struct result_struct;

	struct_mapping::reg(&map_json_to_struct_enum_list_struct::values, "values");

	std::istringstream json_data(R"json(
	{
		"values": ["v2", "v1", "v2"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(
		map_json_to_struct_enum_list::v2,
		map_json_to_struct_enum_list::v1,
		map_json_to_struct_enum_list::v2));
}

TEST(map_json_to_struct, enum_map)
{
	enum class map_json_to_struct_enum_map
	{
		v1,
		v2,
		v3
	};

	struct map_json_to_struct_enum_map_struct
	{
		std::map<std::string, map_json_to_struct_enum_map> values;
	};

	struct_mapping::MemberString<map_json_to_struct_enum_map>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				 return map_json_to_struct_enum_map::v1;
			}
			else if (value == "v2")
			{
				return map_json_to_struct_enum_map::v2;
			}
			else if (value == "v3")
			{
				return map_json_to_struct_enum_map::v3;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to map_json_to_struct_enum_map");
		},
		[] (map_json_to_struct_enum_map value)
		{
			switch (value)
			{
			case map_json_to_struct_enum_map::v1: return "v1";
			case map_json_to_struct_enum_map::v2: return "v2";
			default: return "v3";
			}
		});

	map_json_to_struct_enum_map_struct result_struct;

	struct_mapping::reg(&map_json_to_struct_enum_map_struct::values, "values");

	std::istringstream json_data(R"json(
	{
		"values": {
			"first": "v2",
			"second": "v3",
			"third": "v2"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values,
		ElementsAre(
			Pair("first", map_json_to_struct_enum_map::v2),
			Pair("second", map_json_to_struct_enum_map::v3),
			Pair("third", map_json_to_struct_enum_map::v2)));
}

TEST(map_json_to_struct, member_set)
{
	struct map_json_to_struct_member_set
	{
		std::set<bool> member_set_bool;
		std::set<int> member_set_int;
		std::set<float> member_set_float;
		std::set<std::string> member_set_string;
	};

	map_json_to_struct_member_set result_struct;

	struct_mapping::reg(&map_json_to_struct_member_set::member_set_bool, "member_set_bool");
	struct_mapping::reg(&map_json_to_struct_member_set::member_set_int, "member_set_int");
	struct_mapping::reg(&map_json_to_struct_member_set::member_set_float, "member_set_float");
	struct_mapping::reg(&map_json_to_struct_member_set::member_set_string, "member_set_string");

	std::istringstream json_data(R"json(
	{
		"member_set_bool": [true, false],
		"member_set_int": [-10, -1, 0, 1, 10],
		"member_set_float": [-10.5, -1, 0, 1, 10.5],
		"member_set_string": ["first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_set_bool, ElementsAre(false, true));
	ASSERT_THAT(result_struct.member_set_int, ElementsAre(-10, -1, 0, 1, 10));
	ASSERT_THAT(result_struct.member_set_float, ElementsAre(-10.5f, -1.0f, 0.0f, 1.0f, 10.5f));
	ASSERT_THAT(result_struct.member_set_string, ElementsAre("first", "second"));
}

TEST(map_json_to_struct, member_multiset)
{
	struct map_json_to_struct_member_multiset
	{
		std::multiset<bool> member_set_bool;
		std::multiset<int> member_set_int;
		std::multiset<float> member_set_float;
		std::multiset<std::string> member_set_string;
	};

	map_json_to_struct_member_multiset result_struct;

	struct_mapping::reg(&map_json_to_struct_member_multiset::member_set_bool, "member_set_bool");
	struct_mapping::reg(&map_json_to_struct_member_multiset::member_set_int, "member_set_int");
	struct_mapping::reg(&map_json_to_struct_member_multiset::member_set_float, "member_set_float");
	struct_mapping::reg(&map_json_to_struct_member_multiset::member_set_string, "member_set_string");

	std::istringstream json_data(R"json(
	{
		"member_set_bool": [true, false, false, true],
		"member_set_int": [-10, -1, 0, 1, 10, -10, 0, 10],
		"member_set_float": [-10.5, -1, 0, 1, 10.5, -10.5, -1, 0],
		"member_set_string": ["first", "second", "first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_set_bool, ElementsAre(false, false, true, true));
	ASSERT_THAT(result_struct.member_set_int, ElementsAre(-10, -10, -1, 0, 0, 1, 10, 10));
	ASSERT_THAT(result_struct.member_set_float, ElementsAre(-10.5f, -10.5f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 10.5f));
	ASSERT_THAT(result_struct.member_set_string, ElementsAre("first", "first", "second", "second"));
}

TEST(map_json_to_struct, member_unordered_set)
{
	struct map_json_to_struct_member_unordered_set
	{
		std::unordered_set<bool> member_set_bool;
		std::unordered_set<int> member_set_int;
		std::unordered_set<float> member_set_float;
		std::unordered_set<std::string> member_set_string;
	};

	map_json_to_struct_member_unordered_set result_struct;

	struct_mapping::reg(&map_json_to_struct_member_unordered_set::member_set_bool, "member_set_bool");
	struct_mapping::reg(&map_json_to_struct_member_unordered_set::member_set_int, "member_set_int");
	struct_mapping::reg(&map_json_to_struct_member_unordered_set::member_set_float, "member_set_float");
	struct_mapping::reg(&map_json_to_struct_member_unordered_set::member_set_string, "member_set_string");

	std::istringstream json_data(R"json(
	{
		"member_set_bool": [true, false],
		"member_set_int": [-10, -1, 0, 1, 10],
		"member_set_float": [-10.5, -1, 0, 1, 10.5],
		"member_set_string": ["first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_set_bool, UnorderedElementsAre(false, true));
	ASSERT_THAT(result_struct.member_set_int, UnorderedElementsAre(-10, -1, 0, 1, 10));
	ASSERT_THAT(result_struct.member_set_float, UnorderedElementsAre(-10.5f, -1.0f, 0.0f, 1.0f, 10.5f));
	ASSERT_THAT(result_struct.member_set_string, UnorderedElementsAre("first", "second"));
}

TEST(map_json_to_struct, member_unordered_multiset)
{
	struct map_json_to_struct_member_unordered_multiset
	{
		std::unordered_multiset<bool> member_set_bool;
		std::unordered_multiset<int> member_set_int;
		std::unordered_multiset<float> member_set_float;
		std::unordered_multiset<std::string> member_set_string;
	};

	map_json_to_struct_member_unordered_multiset result_struct;

	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset::member_set_bool, "member_set_bool");
	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset::member_set_int, "member_set_int");
	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset::member_set_float, "member_set_float");
	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset::member_set_string, "member_set_string");

	std::istringstream json_data(R"json(
	{
		"member_set_bool": [true, false, false, true],
		"member_set_int": [-10, -1, 0, 1, 10, -10, 0, 10],
		"member_set_float": [-10.5, -1, 0, 1, 10.5, -10.5, -1, 0],
		"member_set_string": ["first", "second", "first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_set_bool, UnorderedElementsAre(false, false, true, true));
	ASSERT_THAT(result_struct.member_set_int, UnorderedElementsAre(-10, -1, 0, 1, 10, -10, 0, 10));
	ASSERT_THAT(result_struct.member_set_float,
		UnorderedElementsAre(-10.5f, -1.0f, 0.0f, 1.0f, 10.5f, -10.5f, -1.0f, 0.0f));

	ASSERT_THAT(result_struct.member_set_string, UnorderedElementsAre("first", "second", "first", "second"));
}

TEST(map_json_to_struct, member_set_struct)
{
	struct map_json_to_struct_member_set_struct_A
	{
		std::string member_string;

		bool operator<(const map_json_to_struct_member_set_struct_A& o) const
		{
			return member_string < o.member_string;
		}
	};

	struct map_json_to_struct_member_set_struct_B{
		int member_int;
		std::set<map_json_to_struct_member_set_struct_A> member_set;

		bool operator<(const map_json_to_struct_member_set_struct_B& o) const
		{
			return member_int < o.member_int;
		}
	};

	struct map_json_to_struct_member_set_struct_C
	{
		std::set<map_json_to_struct_member_set_struct_B> member;
	};

	map_json_to_struct_member_set_struct_C result_struct;

	struct_mapping::reg(&map_json_to_struct_member_set_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_set_struct_B::member_int, "member_int");
	struct_mapping::reg(&map_json_to_struct_member_set_struct_B::member_set, "member_set");
	struct_mapping::reg(&map_json_to_struct_member_set_struct_C::member, "member");

	std::istringstream json_data(R"json(
	{
		"member": [
			{
				"member_int": 42,
				"member_set": [
					{
						"member_string": "first"
					},
					{
						"member_string": "second"
					}
				]
			},
			{
				"member_int": 13,
				"member_set": [
					{
						"member_string": "third"
					}
				]
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member.size(), 2);

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_set_struct_B{
			13,
			std::set<map_json_to_struct_member_set_struct_A>
			{
				{
					"third"
				}
			}
		}
	), result_struct.member.end());

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_set_struct_B
		{
			42,
			std::set<map_json_to_struct_member_set_struct_A>
			{
				map_json_to_struct_member_set_struct_A
				{
					"first"
				},
				map_json_to_struct_member_set_struct_A
				{
					"second"
				}
			}
		}
	), result_struct.member.end());
}

TEST(map_json_to_struct, member_unordered_set_struct)
{
	struct map_json_to_struct_member_unordered_set_struct_A
	{
		std::string member_string;

		bool operator==(const map_json_to_struct_member_unordered_set_struct_A& o) const
		{
			return member_string == o.member_string;
		}
	};

	struct map_json_to_struct_member_unordered_set_struct_A_hash
	{
		size_t operator()(const map_json_to_struct_member_unordered_set_struct_A& o) const
		{
			return static_cast<size_t>(o.member_string.size());
		}
	};

	struct map_json_to_struct_member_unordered_set_struct_B{
		int member_int;
		std::unordered_set<
			map_json_to_struct_member_unordered_set_struct_A,
			map_json_to_struct_member_unordered_set_struct_A_hash> member_set;

		bool operator==(const map_json_to_struct_member_unordered_set_struct_B& o) const
		{
			return member_int == o.member_int;
		}
	};

	struct map_json_to_struct_member_unordered_set_struct_B_hash
	{
		size_t operator()(const map_json_to_struct_member_unordered_set_struct_B& o) const
		{
			return static_cast<size_t>(o.member_int);
		}
	};

	struct map_json_to_struct_member_unordered_set_struct_C
	{
		std::unordered_set<
			map_json_to_struct_member_unordered_set_struct_B,
			map_json_to_struct_member_unordered_set_struct_B_hash> member;
	};

	map_json_to_struct_member_unordered_set_struct_C result_struct;

	struct_mapping::reg(&map_json_to_struct_member_unordered_set_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_unordered_set_struct_B::member_int, "member_int");
	struct_mapping::reg(&map_json_to_struct_member_unordered_set_struct_B::member_set, "member_set");
	struct_mapping::reg(&map_json_to_struct_member_unordered_set_struct_C::member, "member");

	std::istringstream json_data(R"json(
	{
		"member": [
			{
				"member_int": 42,
				"member_set": [
					{
						"member_string": "first"
					},
					{
						"member_string": "second"
					}
				]
			},
			{
				"member_int": 13,
				"member_set": [
					{
						"member_string": "third"
					}
				]
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member.size(), 2);

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_unordered_set_struct_B
		{
			13,
			std::unordered_set<
				map_json_to_struct_member_unordered_set_struct_A,
				map_json_to_struct_member_unordered_set_struct_A_hash>
			{
				{
					"third"
				}
			}
		}
	), result_struct.member.end());

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_unordered_set_struct_B
		{
			42,
			std::unordered_set<
				map_json_to_struct_member_unordered_set_struct_A,
				map_json_to_struct_member_unordered_set_struct_A_hash>
			{
				map_json_to_struct_member_unordered_set_struct_A
				{
					"first"
				},
				map_json_to_struct_member_unordered_set_struct_A
				{
					"second"
				}
			}
		}
	), result_struct.member.end());
}

TEST(map_json_to_struct, member_multiset_struct)
{
	struct map_json_to_struct_member_multiset_struct_A
	{
		std::string member_string;

		bool operator<(const map_json_to_struct_member_multiset_struct_A& o) const
		{
			return member_string < o.member_string;
		}
	};

	struct map_json_to_struct_member_multiset_struct_B
	{
		int member_int;
		std::set<map_json_to_struct_member_multiset_struct_A> member_set;

		bool operator<(const map_json_to_struct_member_multiset_struct_B& o) const
		{
			return member_int < o.member_int;
		}
	};

	struct map_json_to_struct_member_multiset_struct_C
	{
		std::set<map_json_to_struct_member_multiset_struct_B> member;
	};

	map_json_to_struct_member_multiset_struct_C result_struct;

	struct_mapping::reg(&map_json_to_struct_member_multiset_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_multiset_struct_B::member_int, "member_int");
	struct_mapping::reg(&map_json_to_struct_member_multiset_struct_B::member_set, "member_set");
	struct_mapping::reg(&map_json_to_struct_member_multiset_struct_C::member, "member");

	std::istringstream json_data(R"json(
	{
		"member": [
			{
				"member_int": 42,
				"member_set": [
					{
						"member_string": "first"
					},
					{
						"member_string": "second"
					}
				]
			},
			{
				"member_int": 13,
				"member_set": [
					{
						"member_string": "third"
					}
				]
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member.size(), 2);

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_multiset_struct_B
		{
			13,
			std::set<map_json_to_struct_member_multiset_struct_A>
			{
				{
					"third"
				}
			}
		}
	), result_struct.member.end());

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_multiset_struct_B
		{
			42,
			std::set<map_json_to_struct_member_multiset_struct_A>
			{
				map_json_to_struct_member_multiset_struct_A
				{
					"first"
				},
				map_json_to_struct_member_multiset_struct_A
				{
					"second"
				}
			}
		}
	), result_struct.member.end());
}

TEST(map_json_to_struct, member_unordered_multiset_struct)
{
	struct map_json_to_struct_member_unordered_multiset_struct_A
	{
		std::string member_string;

		bool operator==(const map_json_to_struct_member_unordered_multiset_struct_A& o) const
		{
			return member_string == o.member_string;
		}
	};

	struct map_json_to_struct_member_unordered_multiset_struct_A_hash
	{
		size_t operator()(const map_json_to_struct_member_unordered_multiset_struct_A& o) const
		{
			return static_cast<size_t>(o.member_string.size());
		}
	};

	struct map_json_to_struct_member_unordered_multiset_struct_B
	{
		int member_int;
		std::unordered_set<
			map_json_to_struct_member_unordered_multiset_struct_A,
			map_json_to_struct_member_unordered_multiset_struct_A_hash> member_set;

		bool operator==(const map_json_to_struct_member_unordered_multiset_struct_B& o) const
		{
			return member_int == o.member_int;
		}
	};

	struct map_json_to_struct_member_unordered_multiset_struct_B_hash
	{
		size_t operator()(const map_json_to_struct_member_unordered_multiset_struct_B& o) const
		{
			return static_cast<size_t>(o.member_int);
		}
	};

	struct map_json_to_struct_member_unordered_multiset_struct_C
	{
		std::unordered_set<
			map_json_to_struct_member_unordered_multiset_struct_B,
			map_json_to_struct_member_unordered_multiset_struct_B_hash> member;
	};

	map_json_to_struct_member_unordered_multiset_struct_C result_struct;

	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset_struct_A::member_string, "member_string");
	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset_struct_B::member_int, "member_int");
	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset_struct_B::member_set, "member_set");
	struct_mapping::reg(&map_json_to_struct_member_unordered_multiset_struct_C::member, "member");

	std::istringstream json_data(R"json(
	{
		"member": [
			{
				"member_int": 42,
				"member_set": [
					{
						"member_string": "first"
					},
					{
						"member_string": "second"
					}
				]
			},
			{
				"member_int": 13,
				"member_set": [
					{
						"member_string": "third"
					}
				]
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member.size(), 2);

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_unordered_multiset_struct_B
		{
			13,
			std::unordered_set<
				map_json_to_struct_member_unordered_multiset_struct_A,
				map_json_to_struct_member_unordered_multiset_struct_A_hash>
			{
				{
					"third"
				}
			}
		}
	), result_struct.member.end());

	ASSERT_NE(result_struct.member.find(
		map_json_to_struct_member_unordered_multiset_struct_B
		{
			42,
			std::unordered_set<
				map_json_to_struct_member_unordered_multiset_struct_A,
				map_json_to_struct_member_unordered_multiset_struct_A_hash>
			{
				map_json_to_struct_member_unordered_multiset_struct_A
				{
					"first"
				},
				map_json_to_struct_member_unordered_multiset_struct_A
				{
					"second"
				}
			}
		}
	), result_struct.member.end());
}

TEST(map_json_to_struct, class_from_to_string)
{
	struct map_json_to_struct_class_from_to_string_a
	{
		int value;
	};

	struct map_json_to_struct_class_from_to_string_b
	{
		map_json_to_struct_class_from_to_string_a value;
	};

	struct_mapping::MemberString<map_json_to_struct_class_from_to_string_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return map_json_to_struct_class_from_to_string_a{1};
			}
			else if (o == "value_2")
			{
				return map_json_to_struct_class_from_to_string_a{2};
			}
			
			return map_json_to_struct_class_from_to_string_a{0};
		},
		[] (map_json_to_struct_class_from_to_string_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(&map_json_to_struct_class_from_to_string_b::value, "value");

	map_json_to_struct_class_from_to_string_b result_struct;

	std::istringstream json_data(R"json(
	{
		"value": "value_2"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value.value, 2);
}

TEST(map_json_to_struct, class_from_to_string_array)
{
	struct map_json_to_struct_class_from_to_string_array_a
	{
		int value;
	};

	struct map_json_to_struct_class_from_to_string_array_b
	{
		std::vector<map_json_to_struct_class_from_to_string_array_a> value;
	};

	struct_mapping::MemberString<map_json_to_struct_class_from_to_string_array_a>::set(
		[] (const std::string& o) {
			if (o == "value_1")
			{
				return map_json_to_struct_class_from_to_string_array_a{1};
			}
			else if (o == "value_2")
			{
				return map_json_to_struct_class_from_to_string_array_a{2};
			}
			
			return map_json_to_struct_class_from_to_string_array_a{0};
		},
		[] (map_json_to_struct_class_from_to_string_array_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(&map_json_to_struct_class_from_to_string_array_b::value, "value");

	map_json_to_struct_class_from_to_string_array_b result_struct;

	std::istringstream json_data(R"json(
	{
		"value": [
			"value_2",
			"value_1",
			"value_0"
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value[0].value, 2);
	EXPECT_EQ(result_struct.value[1].value, 1);
	EXPECT_EQ(result_struct.value[2].value, 0);
}

TEST(map_json_to_struct, class_from_to_string_map)
{
	struct map_json_to_struct_class_from_to_string_map_a
	{
		int value;
	};

	struct map_json_to_struct_class_from_to_string_map_b
	{
		std::map<std::string, map_json_to_struct_class_from_to_string_map_a> value;
	};

	struct_mapping::MemberString<map_json_to_struct_class_from_to_string_map_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return map_json_to_struct_class_from_to_string_map_a{1};
			}
			else if (o == "value_2")
			{
				return map_json_to_struct_class_from_to_string_map_a{2};
			}
			
			return map_json_to_struct_class_from_to_string_map_a{0};
		},
		[] (map_json_to_struct_class_from_to_string_map_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(&map_json_to_struct_class_from_to_string_map_b::value, "value");

	map_json_to_struct_class_from_to_string_map_b result_struct;

	std::istringstream json_data(R"json(
	{
		"value": {
			"1": "value_2",
			"2": "value_1",
			"3": "value_0"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value["1"].value, 2);
	EXPECT_EQ(result_struct.value["2"].value, 1);
	EXPECT_EQ(result_struct.value["3"].value, 0);
}

} // namespace
