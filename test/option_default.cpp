#include <cstdint>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/struct_mapping.h"

using ::testing::ElementsAre;
using ::testing::Pair;

namespace
{

struct Struct_default
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

TEST(option_default, set_default)
{
	Struct_default result_struct;
	
	struct_mapping::reg(&Struct_default::member_bool, "member_bool", struct_mapping::Default{true});
	struct_mapping::reg(&Struct_default::member_char, "member_char", struct_mapping::Default{1});
	struct_mapping::reg(&Struct_default::member_unsigned_char, "member_unsigned_char", struct_mapping::Default{2});
	struct_mapping::reg(&Struct_default::member_short, "member_short", struct_mapping::Default{3});
	struct_mapping::reg(&Struct_default::member_unsigned_short, "member_unsigned_short", struct_mapping::Default{4});
	struct_mapping::reg(&Struct_default::member_int, "member_int", struct_mapping::Default{5});
	struct_mapping::reg(&Struct_default::member_unsigned_int, "member_unsigned_int", struct_mapping::Default{6});
	struct_mapping::reg(&Struct_default::member_long, "member_long", struct_mapping::Default{7});
	struct_mapping::reg(&Struct_default::member_long_long, "member_long_long", struct_mapping::Default{8});
	struct_mapping::reg(&Struct_default::member_float, "member_float", struct_mapping::Default{9});
	struct_mapping::reg(&Struct_default::member_double, "member_double", struct_mapping::Default{10});
	struct_mapping::reg(&Struct_default::member_string, "member_string", struct_mapping::Default{"string"});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_bool, true);
	ASSERT_EQ(result_struct.member_char, 1);
	ASSERT_EQ(result_struct.member_unsigned_char, 2);
	ASSERT_EQ(result_struct.member_short, 3);
	ASSERT_EQ(result_struct.member_unsigned_short, 4);
	ASSERT_EQ(result_struct.member_int, 5);
	ASSERT_EQ(result_struct.member_unsigned_int, 6);
	ASSERT_EQ(result_struct.member_long, 7);
	ASSERT_EQ(result_struct.member_long_long, 8);
	ASSERT_EQ(result_struct.member_float, 9.0f);
	ASSERT_EQ(result_struct.member_double, 10);
	ASSERT_EQ(result_struct.member_string, "string");
}

struct Struct_default_limits_lowest_char
{
	char member_char;
};

TEST(option_default, default_limits_lowest_char)
{
	Struct_default_limits_lowest_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(&Struct_default_limits_lowest_char::member_char,
			"member_char", struct_mapping::Default{static_cast<long long>(std::numeric_limits<char>::lowest()) - 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_char
{
	char member_char;
};

TEST(option_default, default_limits_max_char)
{
	Struct_default_limits_max_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(&Struct_default_limits_max_char::member_char,
			"member_char", struct_mapping::Default{static_cast<long long>(std::numeric_limits<char>::max()) + 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_lowest_unsigned_char
{
	unsigned char member_unsigned_char;
};

TEST(option_default, default_limits_lowest_unsigned_char)
{
	Struct_default_limits_lowest_unsigned_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_lowest_unsigned_char::member_unsigned_char,
			"member_unsigned_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned char>::lowest()) - 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_unsigned_char
{
	unsigned char member_unsigned_char;
};

TEST(option_default, default_limits_max_unsigned_char)
{
	Struct_default_limits_max_unsigned_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_max_unsigned_char::member_unsigned_char,
			"member_unsigned_char",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned char>::max()) + 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_lowest_short
{
	short member_short;
};

TEST(option_default, default_limits_lowest_short)
{
	Struct_default_limits_lowest_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_lowest_short::member_short,
			"member_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<short>::lowest()) - 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_short
{
	short member_short;
};

TEST(option_default, default_limits_max_short)
{
	Struct_default_limits_max_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_max_short::member_short,
			"member_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<short>::max()) + 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_lowest_unsigned_short
{
	unsigned short member_unsigned_short;
};

TEST(option_default, default_limits_lowest_unsigned_short)
{
	Struct_default_limits_lowest_unsigned_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_lowest_unsigned_short::member_unsigned_short,
			"member_unsigned_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned short>::lowest()) - 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_unsigned_short
{
	unsigned short member_unsigned_short;
};

TEST(option_default, default_limits_max_unsigned_short)
{
	Struct_default_limits_max_unsigned_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_max_unsigned_short::member_unsigned_short,
			"member_unsigned_short",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned short>::max()) + 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_lowest_int
{
	int member_int;
};

TEST(option_default, default_limits_lowest_int)
{
	Struct_default_limits_lowest_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_lowest_int::member_int,
			"member_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<int>::lowest()) - 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_int
{
	int member_int;
};

TEST(option_default, default_limits_max_int)
{
	Struct_default_limits_max_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_max_int::member_int,
			"member_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<int>::max()) + 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_lowest_unsigned_int
{
	unsigned int member_unsigned_int;
};

TEST(option_default, default_limits_lowest_unsigned_int)
{
	Struct_default_limits_lowest_unsigned_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_lowest_unsigned_int::member_unsigned_int,
			"member_unsigned_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned int>::lowest()) - 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_unsigned_int
{
	unsigned int member_unsigned_int;
};

TEST(option_default, default_limits_max_unsigned_int)
{
	Struct_default_limits_max_unsigned_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_max_unsigned_int::member_unsigned_int,
			"member_unsigned_int",
			struct_mapping::Default{static_cast<long long>(std::numeric_limits<unsigned int>::max()) + 1});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_lowest_float
{
	float member_float;
};

TEST(option_default, default_limits_lowest_float)
{
	Struct_default_limits_lowest_float result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_lowest_float::member_float,
			"member_float",
			struct_mapping::Default{static_cast<double>(std::numeric_limits<float>::lowest()) - 1e38});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_default_limits_max_float
{
	float member_float;
};

TEST(option_default, default_limits_max_float)
{
	Struct_default_limits_max_float result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
		struct_mapping::reg(
			&Struct_default_limits_max_float::member_float,
			"member_float",
			struct_mapping::Default{static_cast<double>(std::numeric_limits<float>::max()) + 1e38});
		struct_mapping::map_json_to_struct(result_struct, json_data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

struct Struct_list
{
	std::list<std::string> values;
};

TEST(option_default, list_default)
{
	Struct_list result_struct;
	
	struct_mapping::reg(
		&Struct_list::values,
		"values",
		struct_mapping::Default{std::list<std::string>{"first", "second"}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre("first", "second"));
}

struct Struct_map
{
	std::map<std::string, int> values;
};

TEST(option_default, map_default)
{
	Struct_map result_struct;
	
	struct_mapping::reg(
		&Struct_map::values,
		"values",
		struct_mapping::Default{std::map<std::string, int>{{"first", 1}, {"second", 2}}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(Pair("first", 1), Pair("second", 2)));
}

struct Struct_cppstruct_a
{
	std::string name;
};

struct Struct_cppstruct
{
	Struct_cppstruct_a value;
};

TEST(option_default, cppstruct_default)
{
	Struct_cppstruct result_struct;
	
	struct_mapping::reg(&Struct_cppstruct_a::name, "name");
	struct_mapping::reg(&Struct_cppstruct::value, "value", struct_mapping::Default{Struct_cppstruct_a{"cppstruct name"}});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.value.name, "cppstruct name");
}

enum class Enum_default
{
	v1,
	v2,
	v3
};

struct Struct_enum_default
{
	Enum_default value;
};

TEST(option_default, enum_default)
{
	struct_mapping::MemberString<Enum_default>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return Enum_default::v1;
			}
			else if (value == "v2")
			{
				return Enum_default::v2;
			}
			else if (value == "v3")
			{
				return Enum_default::v3;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum_default");
		},
		[] (Enum_default value)
		{
			switch (value)
			{
			case Enum_default::v1: return "v1";
			case Enum_default::v2: return "v2";
			default: return "v3";
			}
		});

	Struct_enum_default result_struct;
	
	struct_mapping::reg(&Struct_enum_default::value, "value", struct_mapping::Default{Enum_default::v3});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.value, Enum_default::v3);
}

struct class_from_to_string_struct_a
{
	int value;
};

struct class_from_to_string_struct_b
{
	class_from_to_string_struct_a value;
};

TEST(option_default, class_from_to_string_default)
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

	struct_mapping::reg(&class_from_to_string_struct_b::value, "value", struct_mapping::Default{"value_2"});

	class_from_to_string_struct_b result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.value.value, 2);
}

} // namespace
