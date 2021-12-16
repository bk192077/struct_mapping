#include "struct_mapping/struct_mapping.h"

#include "gtest/gtest.h"

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace
{

TEST(option_bounds, successful_bounds)
{
	struct option_bounds_successful_bounds
	{
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
	};

	option_bounds_successful_bounds result_struct;
	
	struct_mapping::reg(&option_bounds_successful_bounds::member_char, "member_char", struct_mapping::Bounds{-1, 10});
	struct_mapping::reg(&option_bounds_successful_bounds::member_unsigned_char, "member_unsigned_char",
		struct_mapping::Bounds{2, 20});

	struct_mapping::reg(&option_bounds_successful_bounds::member_short, "member_short", struct_mapping::Bounds{-3, 30});
	struct_mapping::reg(&option_bounds_successful_bounds::member_unsigned_short, "member_unsigned_short",
		struct_mapping::Bounds{4, 40});

	struct_mapping::reg(&option_bounds_successful_bounds::member_int, "member_int", struct_mapping::Bounds{-5, 50});
	struct_mapping::reg(&option_bounds_successful_bounds::member_unsigned_int, "member_unsigned_int",
		struct_mapping::Bounds{6, 60});

	struct_mapping::reg(&option_bounds_successful_bounds::member_long, "member_long", struct_mapping::Bounds{-7, 70});
	struct_mapping::reg(&option_bounds_successful_bounds::member_long_long, "member_long_long",
		struct_mapping::Bounds{8, 80});

	struct_mapping::reg(&option_bounds_successful_bounds::member_float, "member_float",
		struct_mapping::Bounds{-9.5, 90.5});

	struct_mapping::reg(&option_bounds_successful_bounds::member_double, "member_double",
		struct_mapping::Bounds{-10.2, 100.2});

	struct_mapping::reg(&option_bounds_successful_bounds::member_char_op, "member_char_op",
		struct_mapping::Bounds{-1, 10});

	struct_mapping::reg(
		&option_bounds_successful_bounds::member_unsigned_char_op,
		"member_unsigned_char_op",
		struct_mapping::Bounds{2, 20});

	struct_mapping::reg(&option_bounds_successful_bounds::member_short_op, "member_short_op",
		struct_mapping::Bounds{-3, 30});

	struct_mapping::reg(
		&option_bounds_successful_bounds::member_unsigned_short_op,
		"member_unsigned_short_op",
		struct_mapping::Bounds{4, 40});

	struct_mapping::reg(&option_bounds_successful_bounds::member_int_op, "member_int_op", struct_mapping::Bounds{-5, 50});
	struct_mapping::reg(&option_bounds_successful_bounds::member_unsigned_int_op, "member_unsigned_int_op",
		struct_mapping::Bounds{6, 60});

	struct_mapping::reg(&option_bounds_successful_bounds::member_long_op, "member_long_op",
		struct_mapping::Bounds{-7, 70});

	struct_mapping::reg(&option_bounds_successful_bounds::member_long_long_op, "member_long_long_op",
		struct_mapping::Bounds{8, 80});

	struct_mapping::reg(&option_bounds_successful_bounds::member_float_op, "member_float_op",
		struct_mapping::Bounds{-9.5, 90.5});

	struct_mapping::reg(&option_bounds_successful_bounds::member_double_op, "member_double_op",
		struct_mapping::Bounds{-10.2, 100.2});

	std::istringstream json_data(R"json(
	{
		"member_char": 0,
		"member_unsigned_char": 3,
		"member_short": -2,
		"member_unsigned_short": 4,
		"member_int": -5,
		"member_unsigned_int": 60,
		"member_long": 8,
		"member_long_long": 77,
		"member_float": -3.2,
		"member_double": 80.5,
		"member_char_op": 0,
		"member_unsigned_char_op": 3,
		"member_short_op": -2,
		"member_unsigned_short_op": 4,
		"member_int_op": -5,
		"member_unsigned_int_op": 60,
		"member_long_op": 8,
		"member_long_long_op": 77,
		"member_float_op": -3.2,
		"member_double_op": 80.5
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_char, 0);
	EXPECT_EQ(result_struct.member_unsigned_char, 3);
	EXPECT_EQ(result_struct.member_short, -2);
	EXPECT_EQ(result_struct.member_unsigned_short, 4);
	EXPECT_EQ(result_struct.member_int, -5);
	EXPECT_EQ(result_struct.member_unsigned_int, 60);
	EXPECT_EQ(result_struct.member_long, 8);
	EXPECT_EQ(result_struct.member_long_long, 77);
	EXPECT_EQ(result_struct.member_float, -3.2f);
	EXPECT_EQ(result_struct.member_double, 80.5);

	ASSERT_TRUE(result_struct.member_char_op.has_value());
	EXPECT_EQ(result_struct.member_char_op, 0);
	ASSERT_TRUE(result_struct.member_unsigned_char_op.has_value());
	EXPECT_EQ(result_struct.member_unsigned_char_op, 3);
	ASSERT_TRUE(result_struct.member_short_op.has_value());
	EXPECT_EQ(result_struct.member_short_op, -2);
	ASSERT_TRUE(result_struct.member_unsigned_short_op.has_value());
	EXPECT_EQ(result_struct.member_unsigned_short_op, 4);
	ASSERT_TRUE(result_struct.member_int_op.has_value());
	EXPECT_EQ(result_struct.member_int_op, -5);
	ASSERT_TRUE(result_struct.member_unsigned_int_op.has_value());
	EXPECT_EQ(result_struct.member_unsigned_int_op, 60);
	ASSERT_TRUE(result_struct.member_long_op.has_value());
	EXPECT_EQ(result_struct.member_long_op, 8);
	ASSERT_TRUE(result_struct.member_long_long_op.has_value());
	EXPECT_EQ(result_struct.member_long_long_op, 77);
	ASSERT_TRUE(result_struct.member_float_op.has_value());
	EXPECT_EQ(result_struct.member_float_op, -3.2f);
	ASSERT_TRUE(result_struct.member_double_op.has_value());
	EXPECT_EQ(result_struct.member_double_op, 80.5);
}

TEST(option_bounds, less_than_lowest)
{
	struct option_bounds_less_than_lowest
	{
		int value;
	};

	option_bounds_less_than_lowest result_struct;

	std::istringstream json_data(R"json(
	{
		"value": -128
	}
	)json");

	try
	{
		struct_mapping::reg(&option_bounds_less_than_lowest::value, "value", struct_mapping::Bounds{-36, 42});
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

TEST(option_bounds, more_than_upper)
{
	struct option_bounds_more_than_upper
	{
		int value;
	};

	option_bounds_more_than_upper result_struct;

	std::istringstream json_data(R"json(
	{
		"value": 128
	}
	)json");

	try
	{
		struct_mapping::reg(&option_bounds_more_than_upper::value, "value", struct_mapping::Bounds{-36, 42});
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

TEST(option_bounds, multiple_members_of_the_same_type)
{
	struct option_bounds_multiple_members_of_the_same_type
	{
		int member_int_1;
		int member_int_2;
		int member_int_3;
	};

	option_bounds_multiple_members_of_the_same_type result_struct;
	
	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_int_1,
		"member_int_1",
		struct_mapping::Bounds{1, 3});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_int_2,
		"member_int_2",
		struct_mapping::Bounds{10, 30});

	struct_mapping::reg(
		&option_bounds_multiple_members_of_the_same_type::member_int_3,
		"member_int_3",
		struct_mapping::Bounds{100, 300});

	std::istringstream json_data(R"json(
	{
		"member_int_1": 2,
		"member_int_2": 20,
		"member_int_3": 200
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.member_int_1, 2);
	EXPECT_EQ(result_struct.member_int_2, 20);
	EXPECT_EQ(result_struct.member_int_3, 200);
}

} // namespace
