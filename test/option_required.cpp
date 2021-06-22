#include <cstdint>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/struct_mapping.h"

namespace
{

enum class Enum_required_success
{
	v1,
	v2,
	v3
};

struct Struct_required_success_a {};

struct Struct_required_success
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
	Enum_required_success member_enum;

	Struct_required_success_a member_a;
	std::list<int> member_list;
	std::map<std::string, int> member_map;
};

TEST(option_required, required_success)
{
	struct_mapping::MemberString<Enum_required_success>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return Enum_required_success::v1;
			}
			else if (value == "v2")
			{
				return Enum_required_success::v2;
			}
			else if (value == "v3")
			{
				return Enum_required_success::v3;
			}

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum_required_success");
		},
		[] (Enum_required_success value)
		{
			switch (value)
			{
			case Enum_required_success::v1: return "v1";
			case Enum_required_success::v2: return "v2";
			default: return "v3";
			}
		});

	Struct_required_success result_struct;
	
	struct_mapping::reg(&Struct_required_success::member_bool, "member_bool", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_char, "member_char", struct_mapping::Required{});
	struct_mapping::reg(
		&Struct_required_success::member_unsigned_char,
		"member_unsigned_char",
		struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_short, "member_short", struct_mapping::Required{});
	struct_mapping::reg(
		&Struct_required_success::member_unsigned_short,
		"member_unsigned_short",
		struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_int, "member_int", struct_mapping::Required{});
	struct_mapping::reg(
		&Struct_required_success::member_unsigned_int,
		"member_unsigned_int",
		struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_long, "member_long", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_long_long, "member_long_long", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_float, "member_float", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_double, "member_double", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_string, "member_string", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_enum, "member_enum", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_a, "member_a", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_list, "member_list", struct_mapping::Required{});
	struct_mapping::reg(&Struct_required_success::member_map, "member_map", struct_mapping::Required{});

	std::istringstream json_data(R"json(
	{
		"member_bool": true,
		"member_char": 1,
		"member_unsigned_char": 2,
		"member_short": 3,
		"member_unsigned_short": 4,
		"member_int": 5,
		"member_unsigned_int": 6,
		"member_long": 7,
		"member_long_long": 8,
		"member_float": 9,
		"member_double": 10,
		"member_string": "11",
		"member_enum": "v2",

		"member_a": {},
		"member_list": [],
		"member_map": {}
	}
	)json");

	ASSERT_NO_THROW({
		struct_mapping::map_json_to_struct(result_struct, json_data);
	});
}

struct Struct_required_bool
{
	bool value;
};

TEST(option_required, required_bool)
{
	Struct_required_bool result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_bool::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_char
{
	char value;
};

TEST(option_required, required_char)
{
	Struct_required_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_char::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_unsigned_char
{
	unsigned char value;
};

TEST(option_required, required_unsigned_char)
{
	Struct_required_unsigned_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_unsigned_char::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_short
{
	short value;
};

TEST(option_required, required_short)
{
	Struct_required_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_short::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_unsigned_short
{
	unsigned short value;
};

TEST(option_required, required_unsigned_short)
{
	Struct_required_unsigned_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_unsigned_short::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_int
{
	int value;
};

TEST(option_required, required_int)
{
	Struct_required_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_int::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_unsigned_int
{
	unsigned int value;
};

TEST(option_required, required_unsigned_int)
{
	Struct_required_unsigned_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_unsigned_int::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_long
{
	long value;
};

TEST(option_required, required_long)
{
	Struct_required_long result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_long::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_string
{
	std::string value;
};

TEST(option_required, required_string)
{
	Struct_required_string result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_string::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_struct_a {};

struct Struct_required_struct
{
	Struct_required_struct_a value;
};

TEST(option_required, required_struct)
{
	Struct_required_struct result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_struct::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_list
{
	std::list<int> value;
};

TEST(option_required, required_list)
{
	Struct_required_list result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_list::value, "value", struct_mapping::Required{});

	try
	{
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

struct Struct_required_map
{
	std::map<std::string, int> value;
};

TEST(option_required, required_map)
{
	Struct_required_map result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_map::value, "value", struct_mapping::Required{});

	try
	{
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

enum class Enum_required
{
	v1,
	v2,
	v3
};

struct Struct_required_enum
{
	Enum_required value;
};

TEST(option_required, required_enum)
{
	struct_mapping::MemberString<Enum_required>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return Enum_required::v1;
			}
			else if (value == "v2")
			{
				return Enum_required::v2;
			}
			else if (value == "v3")
			{
				return Enum_required::v3;
			} 

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum_required");
		},
		[] (Enum_required value)
		{
			switch (value)
			{
			case Enum_required::v1: return "v1";
			case Enum_required::v2: return "v2";
			default: return "v3";
			}
		});

	Struct_required_enum result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&Struct_required_enum::value, "value", struct_mapping::Required{});

	try
	{
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

struct class_from_to_string_struct_a
{
	int value;
};

struct class_from_to_string_struct_b
{
	class_from_to_string_struct_a value;
};

TEST(option_default, required_class_from_to_string)
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

	struct_mapping::reg(&class_from_to_string_struct_b::value, "value", struct_mapping::Required{});

	class_from_to_string_struct_b result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
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

} // namespace
