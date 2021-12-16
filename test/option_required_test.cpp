#include "struct_mapping/struct_mapping.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cstdint>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <string>

namespace
{

TEST(option_required, required_success)
{
	enum class option_required_required_success_enum
	{
		v1,
		v2,
		v3
	};

	struct option_required_required_success_a {};

	struct option_required_required_success
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
		option_required_required_success_enum member_enum;

		option_required_required_success_a member_a;
		std::list<int> member_list;
		std::map<std::string, int> member_map;
	};

	struct_mapping::MemberString<option_required_required_success_enum>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return option_required_required_success_enum::v1;
			}
			else if (value == "v2")
			{
				return option_required_required_success_enum::v2;
			}
			else if (value == "v3")
			{
				return option_required_required_success_enum::v3;
			}

			throw struct_mapping::StructMappingException(
				"bad convert '"
				+ value
				+ "' to option_required_required_success_enum");
		},
		[] (option_required_required_success_enum value)
		{
			switch (value)
			{
			case option_required_required_success_enum::v1: return "v1";
			case option_required_required_success_enum::v2: return "v2";
			default: return "v3";
			}
		});

	option_required_required_success result_struct;
	
	struct_mapping::reg(&option_required_required_success::member_bool, "member_bool", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_char, "member_char", struct_mapping::Required{});
	struct_mapping::reg(
		&option_required_required_success::member_unsigned_char,
		"member_unsigned_char",
		struct_mapping::Required{});

	struct_mapping::reg(&option_required_required_success::member_short, "member_short", struct_mapping::Required{});
	struct_mapping::reg(
		&option_required_required_success::member_unsigned_short,
		"member_unsigned_short",
		struct_mapping::Required{});

	struct_mapping::reg(&option_required_required_success::member_int, "member_int", struct_mapping::Required{});
	struct_mapping::reg(
		&option_required_required_success::member_unsigned_int,
		"member_unsigned_int",
		struct_mapping::Required{});

	struct_mapping::reg(&option_required_required_success::member_long, "member_long", struct_mapping::Required{});
	struct_mapping::reg(
		&option_required_required_success::member_long_long, "member_long_long", struct_mapping::Required{});

	struct_mapping::reg(&option_required_required_success::member_float, "member_float", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_double, "member_double", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_string, "member_string", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_enum, "member_enum", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_a, "member_a", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_list, "member_list", struct_mapping::Required{});
	struct_mapping::reg(&option_required_required_success::member_map, "member_map", struct_mapping::Required{});

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

TEST(option_required, required_bool)
{
	struct option_required_required_bool
	{
		bool value;
	};

	option_required_required_bool result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_bool::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_char)
{
	struct option_required_required_char
	{
		char value;
	};

	option_required_required_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_char::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_unsigned_char)
{
	struct option_required_required_unsigned_char
	{
		unsigned char value;
	};

	option_required_required_unsigned_char result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_unsigned_char::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_short)
{
	struct option_required_required_short
	{
		short value;
	};

	option_required_required_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_short::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_unsigned_short)
{
	struct option_required_required_unsigned_short
	{
		unsigned short value;
	};

	option_required_required_unsigned_short result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_unsigned_short::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_int)
{
	struct option_required_required_int
	{
		int value;
	};

	option_required_required_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_int::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_unsigned_int)
{
	struct option_required_required_unsigned_int
	{
		unsigned int value;
	};

	option_required_required_unsigned_int result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_unsigned_int::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_long)
{
	struct option_required_required_long
	{
		long value;
	};

	option_required_required_long result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_long::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_string)
{
	struct option_required_required_string
	{
		std::string value;
	};

	option_required_required_string result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_string::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_struct)
{
	struct option_required_required_struct_a {};

	struct option_required_required_struct
	{
		option_required_required_struct_a value;
	};

	option_required_required_struct result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_struct::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_list)
{
	struct option_required_required_list
	{
		std::list<int> value;
	};

	option_required_required_list result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_list::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_map)
{
	struct option_required_required_map
	{
		std::map<std::string, int> value;
	};

	option_required_required_map result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_map::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_required, required_enum)
{
	enum class option_required_required_enum
	{
		v1,
		v2,
		v3
	};

	struct option_required_required_enum_struct
	{
		option_required_required_enum value;
	};

	struct_mapping::MemberString<option_required_required_enum>::set(
		[] (const std::string& value)
		{
			if (value == "v1")
			{
				return option_required_required_enum::v1;
			}
			else if (value == "v2")
			{
				return option_required_required_enum::v2;
			}
			else if (value == "v3")
			{
				return option_required_required_enum::v3;
			} 

			throw struct_mapping::StructMappingException("bad convert '" + value + "' to option_required_required_enum");
		},
		[] (option_required_required_enum value)
		{
			switch (value)
			{
			case option_required_required_enum::v1: return "v1";
			case option_required_required_enum::v2: return "v2";
			default: return "v3";
			}
		});

	option_required_required_enum_struct result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::reg(&option_required_required_enum_struct::value, "value", struct_mapping::Required{});

	try
	{
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

TEST(option_default, required_class_from_to_string)
{
	struct option_default_required_class_from_to_string_a
	{
		int value;
	};

	struct option_default_required_class_from_to_string_b
	{
		option_default_required_class_from_to_string_a value;
	};

	struct_mapping::MemberString<option_default_required_class_from_to_string_a>::set(
		[] (const std::string& o)
		{
			if (o == "value_1")
			{
				return option_default_required_class_from_to_string_a{1};
			}
			else if (o == "value_2")
			{
				return option_default_required_class_from_to_string_a{2};
			}
			
			return option_default_required_class_from_to_string_a{0};
		},
		[] (option_default_required_class_from_to_string_a o)
		{
			switch (o.value)
			{
			case 1: return "value_1";
			case 2: return "value_2";
			default: return "value_0";
			}
		});

	struct_mapping::reg(&option_default_required_class_from_to_string_b::value, "value", struct_mapping::Required{});

	option_default_required_class_from_to_string_b result_struct;

	std::istringstream json_data(R"json(
	{
	}
	)json");

	try
	{
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

} // namespace
