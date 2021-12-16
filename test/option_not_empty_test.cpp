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

TEST(option_not_empty, empty_value)
{
	struct option_not_empty_empty_value
	{
		std::string name;
	};

	option_not_empty_empty_value result_struct;
	
	struct_mapping::reg(&option_not_empty_empty_value::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"name": ""
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

TEST(option_not_empty, empty_value_optional)
{
	struct option_not_empty_empty_value_optional
	{
		std::optional<std::string> name;
	};

	option_not_empty_empty_value_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_empty_value_optional::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"name": ""
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

TEST(option_not_empty, not_exist_value)
{
	struct option_not_empty_not_exist_value
	{
		std::string name;
	};

	option_not_empty_not_exist_value result_struct;
	
	struct_mapping::reg(&option_not_empty_not_exist_value::name, "name", struct_mapping::NotEmpty{});

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

TEST(option_not_empty, not_exist_value_optional)
{
	struct option_not_empty_not_exist_value_optional
	{
		std::optional<std::string> name;
	};

	option_not_empty_not_exist_value_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_not_exist_value_optional::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_FALSE(result_struct.name.has_value());
}

TEST(option_not_empty, not_empty_value)
{
	struct option_not_empty_not_empty_value
	{
		std::string name;
	};

	option_not_empty_not_empty_value result_struct;
	
	struct_mapping::reg(&option_not_empty_not_empty_value::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"name": "Frank"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_EQ(result_struct.name, "Frank");
}

TEST(option_not_empty, not_empty_value_optional)
{
	struct option_not_empty_not_empty_value_optional
	{
		std::optional<std::string> name;
	};

	option_not_empty_not_empty_value_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_not_empty_value_optional::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"name": "Frank"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.name.has_value());
	EXPECT_EQ(result_struct.name, "Frank");
}

TEST(option_not_empty, list_empty)
{
	struct option_not_empty_list_empty
	{
		std::list<int> values;
	};

	option_not_empty_list_empty result_struct;
	
	struct_mapping::reg(&option_not_empty_list_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": []
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

TEST(option_not_empty, list_empty_optional)
{
	struct option_not_empty_list_empty_optional
	{
		std::optional<std::list<int>> values;
	};

	option_not_empty_list_empty_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_list_empty_optional::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": []
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

TEST(option_not_empty, list_not_exist)
{
	struct option_not_empty_list_not_exist
	{
		std::list<int> values;
	};

	option_not_empty_list_not_exist result_struct;
	
	struct_mapping::reg(&option_not_empty_list_not_exist::values, "values", struct_mapping::NotEmpty{});

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

TEST(option_not_empty, list_not_exist_optional)
{
	struct option_not_empty_list_not_exist
	{
		std::optional<std::list<int>> values;
	};

	option_not_empty_list_not_exist result_struct;
	
	struct_mapping::reg(&option_not_empty_list_not_exist::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);
	
	EXPECT_FALSE(result_struct.values.has_value());
}

TEST(option_not_empty, list_not_empty)
{
	struct option_not_empty_list_not_empty
	{
		std::list<int> values;
	};

	option_not_empty_list_not_empty result_struct;
	
	struct_mapping::reg(&option_not_empty_list_not_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": [1,2,3]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(1,2,3));
}

TEST(option_not_empty, list_not_empty_optional)
{
	struct option_not_empty_list_not_empty_optional
	{
		std::optional<std::list<int>> values;
	};

	option_not_empty_list_not_empty_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_list_not_empty_optional::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": [1,2,3]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.values.has_value());
	ASSERT_THAT(result_struct.values.value(), ElementsAre(1,2,3));
}

TEST(option_not_empty, map_empty)
{
	struct option_not_empty_map_empty
	{
		std::map<std::string, int> values;
	};

	option_not_empty_map_empty result_struct;
	
	struct_mapping::reg(&option_not_empty_map_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": {}
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

TEST(option_not_empty, map_empty_optional)
{
	struct option_not_empty_map_empty_optional
	{
		std::optional<std::map<std::string, int>> values;
	};

	option_not_empty_map_empty_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_map_empty_optional::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": {}
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

TEST(option_not_empty, map_not_exist)
{
	struct option_not_empty_map_not_exist
	{
		std::map<std::string, int> values;
	};

	option_not_empty_map_not_exist result_struct;
	
	struct_mapping::reg(&option_not_empty_map_not_exist::values, "values", struct_mapping::NotEmpty{});

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

TEST(option_not_empty, map_not_exist_optional)
{
	struct option_not_empty_map_not_exist_optional
	{
		std::optional<std::map<std::string, int>> values;
	};

	option_not_empty_map_not_exist_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_map_not_exist_optional::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	EXPECT_FALSE(result_struct.values.has_value());
}

TEST(option_not_empty, map_not_empty)
{
	struct option_not_empty_map_not_empty
	{
		std::map<std::string, int> values;
	};

	option_not_empty_map_not_empty result_struct;
	
	struct_mapping::reg(&option_not_empty_map_not_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": {
			"1": 1,
			"2": 2,
			"3": 3
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(Pair("1", 1), Pair("2", 2), Pair("3", 3)));
}

TEST(option_not_empty, map_not_empty_optional)
{
	struct option_not_empty_map_not_empty_optional
	{
		std::optional<std::map<std::string, int>> values;
	};

	option_not_empty_map_not_empty_optional result_struct;
	
	struct_mapping::reg(&option_not_empty_map_not_empty_optional::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": {
			"1": 1,
			"2": 2,
			"3": 3
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_TRUE(result_struct.values.has_value());
	ASSERT_THAT(result_struct.values.value(), ElementsAre(Pair("1", 1), Pair("2", 2), Pair("3", 3)));
}

} // namespace
