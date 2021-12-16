#include "struct_mapping/struct_mapping.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cstdint>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <string>

using ::testing::ElementsAre;
using ::testing::Pair;

namespace
{

TEST(option_default, set_default)
{
	struct option_bounds_multiple_members_of_the_same_type
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

		std::optional<bool> member_bool_op;
		std::optional<char> member_char_op;
		std::optional<unsigned char> member_unsigned_char_op;
		std::optional<short> member_short_op;
		std::optional<unsigned short> member_unsigned_short_op;
		std::optional<int> member_int_op;
		std::optional<unsigned int> member_unsigned_int_op;
		std::optional<long> member_long_op;
		std::optional<long long> member_long_long_op;
		std::optional<float> member_float_op;
		std::optional<double> member_double_op;
		std::optional<std::string> member_string_op;
	};

	option_bounds_multiple_members_of_the_same_type result_struct;
	
	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_bool,
		"member_bool",
		struct_mapping::Default{true});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_char,
		"member_char",
		struct_mapping::Default{1});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_unsigned_char,
		"member_unsigned_char",
		struct_mapping::Default{2});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_short,
		"member_short",
		struct_mapping::Default{3});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_unsigned_short,
		"member_unsigned_short",
		struct_mapping::Default{4});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_int,
		"member_int",
		struct_mapping::Default{5});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_unsigned_int,
		"member_unsigned_int",
		struct_mapping::Default{6});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_long,
		"member_long",
		struct_mapping::Default{7});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_long_long,
		"member_long_long",
		struct_mapping::Default{8});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_float,
		"member_float",
		struct_mapping::Default{9});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_double,
		"member_double",
		struct_mapping::Default{10});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_string,
		"member_string",
		struct_mapping::Default{"string"});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_bool_op,
		"member_bool_op",
		struct_mapping::Default{true});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_char_op,
		"member_char_op",
		struct_mapping::Default{1});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_unsigned_char_op,
		"member_unsigned_char_op",
		struct_mapping::Default{2});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_short_op,
		"member_short_op",
		struct_mapping::Default{3});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_unsigned_short_op,
		"member_unsigned_short_op",
		struct_mapping::Default{4});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_int_op,
		"member_int_op",
		struct_mapping::Default{5});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_unsigned_int_op,
		"member_unsigned_int_op",
		struct_mapping::Default{6});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_long_op,
		"member_long_op",
		struct_mapping::Default{7});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_long_long_op,
		"member_long_long_op",
		struct_mapping::Default{8});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_float_op,
		"member_float_op",
		struct_mapping::Default{9});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_double_op,
		"member_double_op",
		struct_mapping::Default{10});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_string_op,
		"member_string_op",
		struct_mapping::Default{"string"});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_bool, true);
	EXPECT_EQ(result_struct.member_char, 1);
	EXPECT_EQ(result_struct.member_unsigned_char, 2);
	EXPECT_EQ(result_struct.member_short, 3);
	EXPECT_EQ(result_struct.member_unsigned_short, 4);
	EXPECT_EQ(result_struct.member_int, 5);
	EXPECT_EQ(result_struct.member_unsigned_int, 6);
	EXPECT_EQ(result_struct.member_long, 7);
	EXPECT_EQ(result_struct.member_long_long, 8);
	EXPECT_EQ(result_struct.member_float, 9.0f);
	EXPECT_EQ(result_struct.member_double, 10);
	EXPECT_EQ(result_struct.member_string, "string");

	ASSERT_TRUE(result_struct.member_bool_op.has_value());
	EXPECT_EQ(result_struct.member_bool_op, true);
	ASSERT_TRUE(result_struct.member_char_op.has_value());
	EXPECT_EQ(result_struct.member_char_op, 1);
	ASSERT_TRUE(result_struct.member_unsigned_char_op.has_value());
	EXPECT_EQ(result_struct.member_unsigned_char_op, 2);
	ASSERT_TRUE(result_struct.member_short_op.has_value());
	EXPECT_EQ(result_struct.member_short_op, 3);
	ASSERT_TRUE(result_struct.member_unsigned_short_op.has_value());
	EXPECT_EQ(result_struct.member_unsigned_short_op, 4);
	ASSERT_TRUE(result_struct.member_int_op.has_value());
	EXPECT_EQ(result_struct.member_int_op, 5);
	ASSERT_TRUE(result_struct.member_unsigned_int_op.has_value());
	EXPECT_EQ(result_struct.member_unsigned_int_op, 6);
	ASSERT_TRUE(result_struct.member_long_op.has_value());
	EXPECT_EQ(result_struct.member_long_op, 7);
	ASSERT_TRUE(result_struct.member_long_long_op.has_value());
	EXPECT_EQ(result_struct.member_long_long_op, 8);
	ASSERT_TRUE(result_struct.member_float_op.has_value());
	EXPECT_EQ(result_struct.member_float_op, 9.0f);
	ASSERT_TRUE(result_struct.member_double_op.has_value());
	EXPECT_EQ(result_struct.member_double_op, 10);
	ASSERT_TRUE(result_struct.member_string_op.has_value());
	EXPECT_EQ(result_struct.member_string_op, "string");
}

TEST(option_default, default_limits_lowest_char)
{
	struct option_default_default_limits_lowest_char
	{
		char member_char;
	};

	option_default_default_limits_lowest_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_char::member_char,
			"member_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<char>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_char_optional)
{
	struct option_default_default_limits_lowest_char_optional
	{
		std::optional<char> member_char;
	};

	option_default_default_limits_lowest_char_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_char_optional::member_char,
			"member_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<char>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_char)
{
	struct option_default_default_limits_max_char
	{
		char member_char;
	};

	option_default_default_limits_max_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_char::member_char,
			"member_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<char>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_char_optional)
{
	struct option_default_default_limits_max_char_optional
	{
		std::optional<char> member_char;
	};

	option_default_default_limits_max_char_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_char_optional::member_char,
			"member_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<char>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_unsigned_char)
{
	struct option_default_default_limits_lowest_unsigned_char
	{
		unsigned char member_unsigned_char;
	};

	option_default_default_limits_lowest_unsigned_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_unsigned_char::member_unsigned_char,
			"member_unsigned_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned char>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_unsigned_char_optional)
{
	struct option_default_default_limits_lowest_unsigned_char_optional
	{
		std::optional<unsigned char> member_unsigned_char;
	};

	option_default_default_limits_lowest_unsigned_char_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_unsigned_char_optional::member_unsigned_char,
			"member_unsigned_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned char>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_unsigned_char)
{
	struct option_default_default_limits_max_unsigned_char
	{
		unsigned char member_unsigned_char;
	};

	option_default_default_limits_max_unsigned_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_unsigned_char::member_unsigned_char,
			"member_unsigned_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned char>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_unsigned_char_optional)
{
	struct option_default_default_limits_max_unsigned_char_optional
	{
		std::optional<unsigned char> member_unsigned_char;
	};

	option_default_default_limits_max_unsigned_char_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_unsigned_char_optional::member_unsigned_char,
			"member_unsigned_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned char>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_short)
{
	struct option_default_default_limits_lowest_short
	{
		short member_short;
	};

	option_default_default_limits_lowest_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_short::member_short,
			"member_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<short>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_short_optional)
{
	struct option_default_default_limits_lowest_short_optional
	{
		std::optional<short> member_short;
	};

	option_default_default_limits_lowest_short_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_short_optional::member_short,
			"member_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<short>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_short)
{
	struct option_default_default_limits_max_short
	{
		short member_short;
	};

	option_default_default_limits_max_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_short::member_short,
			"member_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<short>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_short_optional)
{
	struct option_default_default_limits_max_short_optional
	{
		std::optional<short> member_short;
	};

	option_default_default_limits_max_short_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_short_optional::member_short,
			"member_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<short>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_unsigned_short)
{
	struct option_default_default_limits_lowest_unsigned_short
	{
		unsigned short member_unsigned_short;
	};

	option_default_default_limits_lowest_unsigned_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_unsigned_short::member_unsigned_short,
			"member_unsigned_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned short>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_unsigned_short_optional)
{
	struct option_default_default_limits_lowest_unsigned_short_optional
	{
		std::optional<unsigned short> member_unsigned_short;
	};

	option_default_default_limits_lowest_unsigned_short_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_unsigned_short_optional::member_unsigned_short,
			"member_unsigned_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned short>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_unsigned_short)
{
	struct option_default_default_limits_max_unsigned_short
	{
		unsigned short member_unsigned_short;
	};

	option_default_default_limits_max_unsigned_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_unsigned_short::member_unsigned_short,
			"member_unsigned_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned short>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_unsigned_short_optional)
{
	struct option_default_default_limits_max_unsigned_short_optional
	{
		std::optional<unsigned short> member_unsigned_short;
	};

	option_default_default_limits_max_unsigned_short_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_unsigned_short_optional::member_unsigned_short,
			"member_unsigned_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned short>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_int)
{
	struct option_default_default_limits_lowest_int
	{
		int member_int;
	};

	option_default_default_limits_lowest_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_int::member_int,
			"member_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<int>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_int_optional)
{
	struct option_default_default_limits_lowest_int_optional
	{
		std::optional<int> member_int;
	};

	option_default_default_limits_lowest_int_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_int_optional::member_int,
			"member_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<int>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_int)
{
	struct option_default_default_limits_max_int
	{
		int member_int;
	};

	option_default_default_limits_max_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_int::member_int,
			"member_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<int>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_int_optional)
{
	struct option_default_default_limits_max_int_optional
	{
		std::optional<int> member_int;
	};

	option_default_default_limits_max_int_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_int_optional::member_int,
			"member_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<int>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_unsigned_int)
{
	struct option_default_default_limits_lowest_unsigned_int
	{
		unsigned int member_unsigned_int;
	};

	option_default_default_limits_lowest_unsigned_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_unsigned_int::member_unsigned_int,
			"member_unsigned_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned int>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_unsigned_int_optional)
{
	struct option_default_default_limits_lowest_unsigned_int_optional
	{
		std::optional<unsigned int> member_unsigned_int;
	};

	option_default_default_limits_lowest_unsigned_int_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_unsigned_int_optional::member_unsigned_int,
			"member_unsigned_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned int>::lowest()) - 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_unsigned_int)
{
	struct option_default_default_limits_max_unsigned_int
	{
		unsigned int member_unsigned_int;
	};

	option_default_default_limits_max_unsigned_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_unsigned_int::member_unsigned_int,
			"member_unsigned_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned int>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_unsigned_int_optional)
{
	struct option_default_default_limits_max_unsigned_int_optional
	{
		std::optional<unsigned int> member_unsigned_int;
	};

	option_default_default_limits_max_unsigned_int_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_unsigned_int_optional::member_unsigned_int,
			"member_unsigned_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned int>::max()) + 1});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_float)
{
	struct option_default_default_limits_lowest_float
	{
		float member_float;
	};

	option_default_default_limits_lowest_float result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_float::member_float,
			"member_float",
			struct_mapping::Default{static_cast<double>(std::numeric_limits<float>::lowest()) - 1e38});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_lowest_float_optional)
{
	struct option_default_default_limits_lowest_float_optional
	{
		std::optional<float> member_float;
	};

	option_default_default_limits_lowest_float_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_lowest_float_optional::member_float,
			"member_float",
			struct_mapping::Default{static_cast<double>(std::numeric_limits<float>::lowest()) - 1e38});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_float)
{
	struct option_default_default_limits_max_float
	{
		float member_float;
	};

	option_default_default_limits_max_float result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_float::member_float,
			"member_float",
			struct_mapping::Default{static_cast<double>(std::numeric_limits<float>::max()) + 1e38});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, default_limits_max_float_optional)
{
	struct option_default_default_limits_max_float_optional
	{
		std::optional<float> member_float;
	};

	option_default_default_limits_max_float_optional result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&option_default_default_limits_max_float_optional::member_float,
			"member_float",
			struct_mapping::Default{static_cast<double>(std::numeric_limits<float>::max()) + 1e38});

		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException&)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

TEST(option_default, list_default)
{
	struct option_default_list_default
	{
		std::list<std::string> values;
	};

	option_default_list_default result_struct;
	
	struct_mapping::reg(
		&option_default_list_default::values,
		"values",
		struct_mapping::Default{std::list<std::string>{"first", "second"}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre("first", "second"));
}

TEST(option_default, list_default_optional)
{
	struct option_default_list_default_optional
	{
		std::optional<std::list<std::string>> values;
	};

	option_default_list_default_optional result_struct;
	
	struct_mapping::reg(
		&option_default_list_default_optional::values,
		"values",
		struct_mapping::Default{std::list<std::string>{"first", "second"}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.values.has_value());
	ASSERT_THAT(result_struct.values.value(), ElementsAre("first", "second"));
}

TEST(option_default, map_default)
{
	struct option_default_map_default
	{
		std::map<std::string, int> values;
	};

	option_default_map_default result_struct;
	
	struct_mapping::reg(
		&option_default_map_default::values,
		"values",
		struct_mapping::Default{std::map<std::string, int>{{"first", 1}, {"second", 2}}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(Pair("first", 1), Pair("second", 2)));
}

TEST(option_default, map_default_optional)
{
	struct option_default_map_default_optional
	{
		std::optional<std::map<std::string, int>> values;
	};

	option_default_map_default_optional result_struct;
	
	struct_mapping::reg(
		&option_default_map_default_optional::values,
		"values",
		struct_mapping::Default{std::map<std::string, int>{{"first", 1}, {"second", 2}}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.values.has_value());
	ASSERT_THAT(result_struct.values.value(), ElementsAre(Pair("first", 1), Pair("second", 2)));
}

TEST(option_default, cppstruct_default)
{
	struct option_default_cppstruct_default_a
	{
		std::string name;
	};

	struct option_default_cppstruct_default
	{
		option_default_cppstruct_default_a value;
	};

	option_default_cppstruct_default result_struct;
	
	struct_mapping::reg(&option_default_cppstruct_default_a::name, "name");
	struct_mapping::reg(
		&option_default_cppstruct_default::value,
		"value",
		struct_mapping::Default{option_default_cppstruct_default_a{"cppstruct name"}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value.name, "cppstruct name");
}

TEST(option_default, cppstruct_default_optional)
{
	struct option_default_cppstruct_default_optional_a
	{
		std::string name;
	};

	struct option_default_cppstruct_default_optional
	{
		std::optional<option_default_cppstruct_default_optional_a> value;
	};

	option_default_cppstruct_default_optional result_struct;
	
	struct_mapping::reg(&option_default_cppstruct_default_optional_a::name, "name");
	struct_mapping::reg(
		&option_default_cppstruct_default_optional::value,
		"value",
		struct_mapping::Default{option_default_cppstruct_default_optional_a{"cppstruct name"}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.value.has_value());
	EXPECT_EQ(result_struct.value.value().name, "cppstruct name");
}

TEST(option_default, enum_default)
{
	enum class option_default_enum_default
	{
		v1,
		v2,
		v3
	};

	struct Struct_enum_default
	{
		option_default_enum_default value;
	};

	struct_mapping::MemberString<option_default_enum_default>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return option_default_enum_default::v1;
			}
			else if (value == "v2")
			{
				return option_default_enum_default::v2;
			}
			else if (value == "v3")
			{
				return option_default_enum_default::v3;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to option_default_enum_default");
		},
		[] (option_default_enum_default value)
		{
			switch (value)
			{
			case option_default_enum_default::v1: return "v1";
			case option_default_enum_default::v2: return "v2";
			default: return "v3";
			}
		});

	Struct_enum_default result_struct;
	
	struct_mapping::reg(&Struct_enum_default::value, "value", struct_mapping::Default{option_default_enum_default::v3});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value, option_default_enum_default::v3);
}

TEST(option_default, enum_default_optional)
{
	enum class option_default_enum_default_optional
	{
		v1,
		v2,
		v3
	};

	struct Struct_enum_default
	{
		std::optional<option_default_enum_default_optional> value;
	};

	struct_mapping::MemberString<option_default_enum_default_optional>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return option_default_enum_default_optional::v1;
			}
			else if (value == "v2")
			{
				return option_default_enum_default_optional::v2;
			}
			else if (value == "v3")
			{
				return option_default_enum_default_optional::v3;
			}

			throw struct_mapping::StructMappingException(
				"bad convert '" + value + "' to option_default_enum_default_optional");
		},
		[] (option_default_enum_default_optional value)
		{
			switch (value)
			{
			case option_default_enum_default_optional::v1: return "v1";
			case option_default_enum_default_optional::v2: return "v2";
			default: return "v3";
			}
		});

	Struct_enum_default result_struct;
	
	struct_mapping::reg(
		&Struct_enum_default::value,
		"value",
		struct_mapping::Default{option_default_enum_default_optional::v3});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.value.has_value());
	EXPECT_EQ(result_struct.value.value(), option_default_enum_default_optional::v3);
}

TEST(option_default, class_from_to_string_default)
{
	struct option_default_class_from_to_string_default_a
	{
		int value;
	};

	struct option_default_class_from_to_string_default_b
	{
		option_default_class_from_to_string_default_a value;
	};

	struct_mapping::MemberString<option_default_class_from_to_string_default_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return option_default_class_from_to_string_default_a{1};
			}
			else if (o == "value_2")
			{
				return option_default_class_from_to_string_default_a{2};
			}
			
			return option_default_class_from_to_string_default_a{0};
		},
		[] (option_default_class_from_to_string_default_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(
		&option_default_class_from_to_string_default_b::value,
		"value",
		struct_mapping::Default{"value_2"});

	option_default_class_from_to_string_default_b result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.value.value, 2);
}

TEST(option_default, class_from_to_string_default_optional)
{
	struct option_default_class_from_to_string_default_optional_a
	{
		int value;
	};

	struct option_default_class_from_to_string_default_optional_b
	{
		std::optional<option_default_class_from_to_string_default_optional_a> value;
	};

	struct_mapping::MemberString<option_default_class_from_to_string_default_optional_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return option_default_class_from_to_string_default_optional_a{1};
			}
			else if (o == "value_2")
			{
				return option_default_class_from_to_string_default_optional_a{2};
			}
			
			return option_default_class_from_to_string_default_optional_a{0};
		},
		[] (option_default_class_from_to_string_default_optional_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(
		&option_default_class_from_to_string_default_optional_b::value,
		"value",
		struct_mapping::Default{"value_2"});

	option_default_class_from_to_string_default_optional_b result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.value.has_value());
	EXPECT_EQ(result_struct.value.value().value, 2);
}

} // namespace
