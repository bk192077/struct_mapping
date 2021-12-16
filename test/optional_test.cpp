#include "struct_mapping/struct_mapping.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <map>
#include <string>
#include <vector>

using ::testing::ElementsAre;
using ::testing::Pair;

namespace
{

TEST(optional, bool_empty)
{
	struct optional_bool_empty
	{
		std::optional<bool> v_op;
	};

	optional_bool_empty test_bool;

	struct_mapping::reg(&optional_bool_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_bool, json_data);

	EXPECT_FALSE(test_bool.v_op.has_value());
}

TEST(optional, bool_non_empty)
{
	struct optional_bool_non_empty
	{
		std::optional<bool> v_op;
	};

	optional_bool_non_empty test_bool;

	struct_mapping::reg(&optional_bool_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": true
	}
	)json");

	struct_mapping::map_json_to_struct(test_bool, json_data);

	ASSERT_TRUE(test_bool.v_op.has_value());
	EXPECT_TRUE(test_bool.v_op.value());
}

TEST(optional, char_empty)
{
	struct optional_char_empty
	{
		std::optional<char> v_op;
	};

	optional_char_empty test_char;

	struct_mapping::reg(&optional_char_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_char, json_data);

	EXPECT_FALSE(test_char.v_op.has_value());
}

TEST(optional, char_non_empty)
{
	struct optional_char_non_empty
	{
		std::optional<char> v_op;
	};

	optional_char_non_empty test_char;

	struct_mapping::reg(&optional_char_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": -42
	}
	)json");

	struct_mapping::map_json_to_struct(test_char, json_data);

	ASSERT_TRUE(test_char.v_op.has_value());
	EXPECT_EQ(test_char.v_op.value(), -42);
}

TEST(optional, unsigned_char_empty)
{
	struct optional_unsigned_char_empty
	{
		std::optional<unsigned char> v_op;
	};

	optional_unsigned_char_empty test_unsigned_char;

	struct_mapping::reg(&optional_unsigned_char_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_unsigned_char, json_data);

	EXPECT_FALSE(test_unsigned_char.v_op.has_value());
}

TEST(optional, unsigned_char_non_empty)
{
	struct optional_unsigned_char_non_empty
	{
		std::optional<unsigned char> v_op;
	};

	optional_unsigned_char_non_empty test_unsigned_char;

	struct_mapping::reg(&optional_unsigned_char_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": 42
	}
	)json");

	struct_mapping::map_json_to_struct(test_unsigned_char, json_data);

	ASSERT_TRUE(test_unsigned_char.v_op.has_value());
	EXPECT_EQ(test_unsigned_char.v_op.value(), 42);
}

TEST(optional, short_empty)
{
	struct optional_short_empty
	{
		std::optional<short> v_op;
	};

	optional_short_empty test_short;

	struct_mapping::reg(&optional_short_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_short, json_data);

	EXPECT_FALSE(test_short.v_op.has_value());
}

TEST(optional, short_non_empty)
{
	struct optional_short_non_empty
	{
		std::optional<short> v_op;
	};

	optional_short_non_empty test_short;

	struct_mapping::reg(&optional_short_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": -1234
	}
	)json");

	struct_mapping::map_json_to_struct(test_short, json_data);

	ASSERT_TRUE(test_short.v_op.has_value());
	EXPECT_EQ(test_short.v_op.value(), -1234);
}

TEST(optional, unsigned_short_empty)
{
	struct optional_unsigned_short_empty
	{
		std::optional<unsigned short> v_op;
	};

	optional_unsigned_short_empty test_unsigned_short;

	struct_mapping::reg(&optional_unsigned_short_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_unsigned_short, json_data);

	EXPECT_FALSE(test_unsigned_short.v_op.has_value());
}

TEST(optional, unsigned_short_non_empty)
{
	struct optional_unsigned_short_non_empty
	{
		std::optional<unsigned short> v_op;
	};

	optional_unsigned_short_non_empty test_unsigned_short;

	struct_mapping::reg(&optional_unsigned_short_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": 1234
	}
	)json");

	struct_mapping::map_json_to_struct(test_unsigned_short, json_data);

	ASSERT_TRUE(test_unsigned_short.v_op.has_value());
	EXPECT_EQ(test_unsigned_short.v_op.value(), 1234);
}

TEST(optional, int_empty)
{
	struct optional_int_empty
	{
		std::optional<int> v_op;
	};

	optional_int_empty test_int;

	struct_mapping::reg(&optional_int_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_int, json_data);

	EXPECT_FALSE(test_int.v_op.has_value());
}

TEST(optional, int_non_empty)
{
	struct optional_int_non_empty
	{
		std::optional<int> v_op;
	};

	optional_int_non_empty test_int;

	struct_mapping::reg(&optional_int_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": -12345678
	}
	)json");

	struct_mapping::map_json_to_struct(test_int, json_data);

	ASSERT_TRUE(test_int.v_op.has_value());
	EXPECT_EQ(test_int.v_op.value(), -12345678);
}

TEST(optional, unsigned_int_empty)
{
	struct optional_unsigned_int_empty
	{
		std::optional<unsigned int> v_op;
	};

	optional_unsigned_int_empty test_unsigned_int;

	struct_mapping::reg(&optional_unsigned_int_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_unsigned_int, json_data);

	EXPECT_FALSE(test_unsigned_int.v_op.has_value());
}

TEST(optional, unsigned_int_non_empty)
{
	struct optional_unsigned_int_non_empty
	{
		std::optional<unsigned int> v_op;
	};

	optional_unsigned_int_non_empty test_unsigned_int;

	struct_mapping::reg(&optional_unsigned_int_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": 12345678
	}
	)json");

	struct_mapping::map_json_to_struct(test_unsigned_int, json_data);

	ASSERT_TRUE(test_unsigned_int.v_op.has_value());
	EXPECT_EQ(test_unsigned_int.v_op.value(), 12345678);
}

TEST(optional, long_empty)
{
	struct optional_long_empty
	{
		std::optional<long> v_op;
	};

	optional_long_empty test_long;

	struct_mapping::reg(&optional_long_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_long, json_data);

	EXPECT_FALSE(test_long.v_op.has_value());
}

TEST(optional, long_non_empty)
{
	struct optional_long_non_empty
	{
		std::optional<long> v_op;
	};

	optional_long_non_empty test_long;

	struct_mapping::reg(&optional_long_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": -12345678
	}
	)json");

	struct_mapping::map_json_to_struct(test_long, json_data);

	ASSERT_TRUE(test_long.v_op.has_value());
	EXPECT_EQ(test_long.v_op.value(), -12345678);
}

TEST(optional, long_long_empty)
{
	struct optional_long_long_empty
	{
		std::optional<long long> v_op;
	};

	optional_long_long_empty test_long_long;

	struct_mapping::reg(&optional_long_long_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_long_long, json_data);

	EXPECT_FALSE(test_long_long.v_op.has_value());
}

TEST(optional, long_long_non_empty)
{
	struct optional_long_long_non_empty
	{
		std::optional<long long> v_op;
	};

	optional_long_long_non_empty test_long_long;

	struct_mapping::reg(&optional_long_long_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": 12345678
	}
	)json");

	struct_mapping::map_json_to_struct(test_long_long, json_data);

	ASSERT_TRUE(test_long_long.v_op.has_value());
	EXPECT_EQ(test_long_long.v_op.value(), 12345678);
}

TEST(optional, float_empty)
{
	struct optional_float_empty
	{
		std::optional<float> v_op;
	};

	optional_float_empty test_float;

	struct_mapping::reg(&optional_float_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_float, json_data);

	EXPECT_FALSE(test_float.v_op.has_value());
}

TEST(optional, float_non_empty)
{
	struct optional_float_non_empty
	{
		std::optional<float> v_op;
		std::optional<float> v1_op;
	};

	optional_float_non_empty test_float;

	struct_mapping::reg(&optional_float_non_empty::v_op, "v_op");
	struct_mapping::reg(&optional_float_non_empty::v1_op, "v1_op");

	std::istringstream json_data(R"json(
	{
		"v_op": -12.345678,
		"v1_op": 12345678
	}
	)json");

	struct_mapping::map_json_to_struct(test_float, json_data);

	ASSERT_TRUE(test_float.v_op.has_value());
	EXPECT_FLOAT_EQ(test_float.v_op.value(), -12.345678f);

	ASSERT_TRUE(test_float.v1_op.has_value());
	EXPECT_FLOAT_EQ(test_float.v1_op.value(), 12345678.0f);
}

TEST(optional, double_empty)
{
	struct optional_double_empty
	{
		std::optional<double> v_op;
	};

	optional_double_empty test_double;

	struct_mapping::reg(&optional_double_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_double, json_data);

	EXPECT_FALSE(test_double.v_op.has_value());
}

TEST(optional, double_non_empty)
{
	struct optional_double_non_empty
	{
		std::optional<double> v_op;
		std::optional<double> v1_op;
	};

	optional_double_non_empty test_double;

	struct_mapping::reg(&optional_double_non_empty::v_op, "v_op");
	struct_mapping::reg(&optional_double_non_empty::v1_op, "v1_op");

	std::istringstream json_data(R"json(
	{
		"v_op": -212.345678,
		"v1_op": 212345678
	}
	)json");

	struct_mapping::map_json_to_struct(test_double, json_data);

	ASSERT_TRUE(test_double.v_op.has_value());
	EXPECT_DOUBLE_EQ(test_double.v_op.value(), -212.345678);

	ASSERT_TRUE(test_double.v1_op.has_value());
	EXPECT_DOUBLE_EQ(test_double.v1_op.value(), 212345678.0);
}

TEST(optional, string_empty)
{
	struct optional_string_empty
	{
		std::optional<std::string> v_op;
	};

	optional_string_empty test_string;

	struct_mapping::reg(&optional_string_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_string, json_data);

	EXPECT_FALSE(test_string.v_op.has_value());
}

TEST(optional, string_non_empty)
{
	struct optional_string_non_empty
	{
		std::optional<std::string> v_op;
	};

	optional_string_non_empty test_string;

	struct_mapping::reg(&optional_string_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": "test_string"
	}
	)json");

	struct_mapping::map_json_to_struct(test_string, json_data);

	ASSERT_TRUE(test_string.v_op.has_value());
	EXPECT_EQ(test_string.v_op.value(), "test_string");
}

TEST(optional, array_like_empty)
{
	struct optional_array_like_empty
	{
		std::optional<std::vector<int>> v_op;
	};

	optional_array_like_empty test_array_like;

	struct_mapping::reg(&optional_array_like_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_array_like, json_data);

	EXPECT_FALSE(test_array_like.v_op.has_value());
}

TEST(optional, array_like_non_empty)
{
	struct optional_array_like_non_empty
	{
		std::optional<std::vector<int>> v_op;
	};

	optional_array_like_non_empty test_array_like;

	struct_mapping::reg(&optional_array_like_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": [1, 3, 5]
	}
	)json");

	struct_mapping::map_json_to_struct(test_array_like, json_data);

	ASSERT_TRUE(test_array_like.v_op.has_value());
	EXPECT_THAT(test_array_like.v_op.value(), ElementsAre(1, 3, 5));
}

TEST(optional, array_in_array)
{
	struct optiona_array_in_arrayA
	{
		int v_a;
	};

	struct optiona_array_in_array
	{
		std::optional<std::vector<std::vector<optiona_array_in_arrayA>>> v_op;
	};

	optiona_array_in_array test_array_in_array;

	struct_mapping::reg(&optiona_array_in_array::v_op, "v_op");
	struct_mapping::reg(&optiona_array_in_arrayA::v_a, "v_a");

	std::istringstream json_data(R"json(
	{
		"v_op":
		[
			[
				{
					"v_a": 1
				},
				{
					"v_a": 2
				},
				{
					"v_a": 3
				}
			],
			[
				{
					"v_a": 4
				},
				{
					"v_a": 5
				}
			]
		]
	}
	)json");

	struct_mapping::map_json_to_struct(test_array_in_array, json_data);

	ASSERT_TRUE(test_array_in_array.v_op.has_value());
	EXPECT_EQ(test_array_in_array.v_op.value().size(), 2);
	EXPECT_EQ(test_array_in_array.v_op.value()[0][0].v_a, 1);
}

TEST(optional, map_like_empty)
{
	struct optional_map_like_empty
	{
		std::optional<std::map<std::string, int>> v_op;
	};

	optional_map_like_empty test_map_like;

	struct_mapping::reg(&optional_map_like_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_map_like, json_data);

	EXPECT_FALSE(test_map_like.v_op.has_value());
}

TEST(optional, map_like_non_empty)
{
	struct optional_map_like_non_empty
	{
		std::optional<std::map<std::string, int>> v_op;
	};

	optional_map_like_non_empty test_map_like;

	struct_mapping::reg(&optional_map_like_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op":
		{
			"first": -10,
			"second": 0,
			"third": 10
		}
	}
	)json");

	struct_mapping::map_json_to_struct(test_map_like, json_data);

	ASSERT_TRUE(test_map_like.v_op.has_value());
	EXPECT_THAT(test_map_like.v_op.value(), ElementsAre(Pair("first", -10), Pair("second", 0), Pair("third", 10)));
}

TEST(optional, map_in_map)
{
	struct optional_map_in_mapA
	{
		int v_a;
	};

	struct optional_map_in_map
	{
		std::optional<std::map<std::string, std::map<std::string, optional_map_in_mapA>>> v_op;
	};

	optional_map_in_map test_map_in_map;

	struct_mapping::reg(&optional_map_in_map::v_op, "v_op");
	struct_mapping::reg(&optional_map_in_mapA::v_a, "v_a");

	std::istringstream json_data(R"json(
	{
		"v_op":
		{
			"first":
			{
				"a":
				{
					"v_a": 1
				},
				"b":
				{
					"v_a": 2
				},
				"c":
				{
					"v_a": 3
				}
			},
			"second":
			{
				"d":
				{
					"v_a": 4
				},
				"e":
				{
					"v_a": 5
				}
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(test_map_in_map, json_data);

	ASSERT_TRUE(test_map_in_map.v_op.has_value());

	const auto v_op_first_it = test_map_in_map.v_op.value().find("first");
	ASSERT_TRUE(v_op_first_it != std::cend(test_map_in_map.v_op.value()));

	const auto first_a_it = v_op_first_it->second.find("a");
	ASSERT_TRUE(first_a_it != std::cend(v_op_first_it->second));
	EXPECT_EQ(first_a_it->second.v_a, 1);

	const auto first_b_it = v_op_first_it->second.find("b");
	ASSERT_TRUE(first_b_it != std::cend(v_op_first_it->second));
	EXPECT_EQ(first_b_it->second.v_a, 2);

	const auto first_c_it = v_op_first_it->second.find("c");
	ASSERT_TRUE(first_c_it != std::cend(v_op_first_it->second));
	EXPECT_EQ(first_c_it->second.v_a, 3);

	const auto v_op_second_it = test_map_in_map.v_op.value().find("second");
	ASSERT_TRUE(v_op_second_it != std::cend(test_map_in_map.v_op.value()));

	const auto second_d_it = v_op_second_it->second.find("d");
	ASSERT_TRUE(second_d_it != std::cend(v_op_second_it->second));
	EXPECT_EQ(second_d_it->second.v_a, 4);

	const auto second_e_it = v_op_second_it->second.find("e");
	ASSERT_TRUE(second_e_it != std::cend(v_op_second_it->second));
	EXPECT_EQ(second_e_it->second.v_a, 5);
}

TEST(optional, enum_empty)
{
	enum class optional_enum_empty
	{
		first,
		second
	};

	struct optional_enum_empty_struct
	{
		std::optional<optional_enum_empty> v_op;
	};

	struct_mapping::MemberString<optional_enum_empty>::set(
		[] (const std::string& value)
		{
			if (value == "first")
			{
				return optional_enum_empty::first;
			}
			else if (value == "second")
			{
				return optional_enum_empty::second;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to optional_enum_empty");
		},
		[] (optional_enum_empty value)
		{
			switch (value)
			{
			case optional_enum_empty::first: return "first";
			case optional_enum_empty::second: return "second";
			}

			throw struct_mapping::StructMappingException(
				"bad convert optional_enum_empty '"
				+ std::to_string(static_cast<int>(value))
				+ "' to string");
		});

	optional_enum_empty_struct test_enum;

	struct_mapping::reg(&optional_enum_empty_struct::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_enum, json_data);

	EXPECT_FALSE(test_enum.v_op.has_value());
}

TEST(optional, enum_non_empty)
{
	enum class optional_enum_non_empty
	{
		first,
		second
	};

	struct optional_enum_non_empty_struct
	{
		std::optional<optional_enum_non_empty> v_op;
	};

	struct_mapping::MemberString<optional_enum_non_empty>::set(
		[] (const std::string& value)
		{
			if (value == "first")
			{
				return optional_enum_non_empty::first;
			}
			else if (value == "second")
			{
				return optional_enum_non_empty::second;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to optional_enum_non_empty");
		},
		[] (optional_enum_non_empty value)
		{
			switch (value)
			{
			case optional_enum_non_empty::first: return "first";
			case optional_enum_non_empty::second: return "second";
			}

			throw struct_mapping::StructMappingException(
				"bad convert optional_enum_non_empty '"
				+ std::to_string(static_cast<int>(value))
				+ "' to string");
		});

	optional_enum_non_empty_struct test_enum;

	struct_mapping::reg(&optional_enum_non_empty_struct::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": "second"
	}
	)json");

	struct_mapping::map_json_to_struct(test_enum, json_data);

	ASSERT_TRUE(test_enum.v_op.has_value());
	EXPECT_EQ(test_enum.v_op.value(), optional_enum_non_empty::second);
}

TEST(optional, struct_empty)
{
	struct optional_struct_empty_inner
	{
		std::optional<int> v_inner_op;
	};

	struct optional_struct_empty
	{
		std::optional<optional_struct_empty_inner> v_op;
	};

	optional_struct_empty test_struct;

	struct_mapping::reg(&optional_struct_empty_inner::v_inner_op, "v_inner_op");
	struct_mapping::reg(&optional_struct_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_struct, json_data);

	EXPECT_FALSE(test_struct.v_op.has_value());
}

TEST(optional, struct_non_empty)
{
	struct optional_struct_non_empty_inner
	{
		std::optional<int> v_inner_op;
	};

	struct optional_struct_non_empty
	{
		std::optional<optional_struct_non_empty_inner> v_op;
	};

	optional_struct_non_empty test_struct;

	struct_mapping::reg(&optional_struct_non_empty_inner::v_inner_op, "v_inner_op");
	struct_mapping::reg(&optional_struct_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": 
		{
			"v_inner_op": 81
		}
	}
	)json");

	struct_mapping::map_json_to_struct(test_struct, json_data);

	ASSERT_TRUE(test_struct.v_op.has_value());
	ASSERT_TRUE(test_struct.v_op.value().v_inner_op.has_value());
	EXPECT_EQ(test_struct.v_op.value().v_inner_op.value(), 81);
}

TEST(optional, struct_from_string_empty)
{
	struct optional_struct_from_string_empty_inner
	{
		int v_inner;
	};

	struct optional_struct_from_string_empty
	{
		std::optional<optional_struct_from_string_empty_inner> v_op;
	};

	struct_mapping::MemberString<optional_struct_from_string_empty_inner>::set(
		[] (const std::string& value)
		{
			if (value == "Pi")
			{
				return optional_struct_from_string_empty_inner{3};
			}
			else if (value == "Fi")
			{
				return optional_struct_from_string_empty_inner{5};
			}

			throw struct_mapping::StructMappingException(
				"bad convert '" + value + "' to optional_struct_from_string_empty_inner");
		},
		[] (optional_struct_from_string_empty_inner value)
		{
			switch (value.v_inner)
			{
			case 3: return "Pi";
			case 5: return "Fi";
			}

			throw struct_mapping::StructMappingException(
				"bad convert optional_struct_from_string_empty_inner '"
				+ std::to_string(value.v_inner)
				+ "' to string");
		});

	optional_struct_from_string_empty test_struct_from_string;

	struct_mapping::reg(&optional_struct_from_string_empty_inner::v_inner, "v_inner");
	struct_mapping::reg(&optional_struct_from_string_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(test_struct_from_string, json_data);

	EXPECT_FALSE(test_struct_from_string.v_op.has_value());
}

TEST(optional, struct_from_string_non_empty)
{
	struct optional_struct_from_string_non_empty_inner
	{
		int v_inner;
	};

	struct optional_struct_from_string_non_empty
	{
		std::optional<optional_struct_from_string_non_empty_inner> v_op;
	};

	struct_mapping::MemberString<optional_struct_from_string_non_empty_inner>::set(
		[] (const std::string& value)
		{
			if (value == "Pi")
			{
				return optional_struct_from_string_non_empty_inner{3};
			}
			else if (value == "Fi")
			{
				return optional_struct_from_string_non_empty_inner{5};
			}

			throw struct_mapping::StructMappingException(
				"bad convert '" + value + "' to optional_struct_from_string_non_empty_inner");
		},
		[] (optional_struct_from_string_non_empty_inner value)
		{
			switch (value.v_inner)
			{
			case 3: return "Pi";
			case 5: return "Fi";
			}

			throw struct_mapping::StructMappingException(
				"bad convert optional_struct_from_string_non_empty_inner '"
				+ std::to_string(value.v_inner)
				+ "' to string");
		});

	optional_struct_from_string_non_empty test_struct_from_string;

	struct_mapping::reg(&optional_struct_from_string_non_empty_inner::v_inner, "v_inner");
	struct_mapping::reg(&optional_struct_from_string_non_empty::v_op, "v_op");

	std::istringstream json_data(R"json(
	{
		"v_op": "Fi"
	}
	)json");

	struct_mapping::map_json_to_struct(test_struct_from_string, json_data);

	ASSERT_TRUE(test_struct_from_string.v_op.has_value());
	EXPECT_EQ(test_struct_from_string.v_op.value().v_inner, 5);
}

} // namespace
