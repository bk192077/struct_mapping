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

struct Struct_not_empty
{
	std::string name;
};

TEST(option_not_empty, not_empty_value)
{
	Struct_not_empty result_struct;
	
	struct_mapping::reg(&Struct_not_empty::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"name": "Frank"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.name, "Frank");
}

struct Struct_empty
{
	std::string name;
};

TEST(option_not_empty, empty_value)
{
	Struct_empty result_struct;
	
	struct_mapping::reg(&Struct_empty::name, "name", struct_mapping::NotEmpty{});

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

struct Struct_list_not_empty
{
	std::list<int> values;
};

TEST(option_not_empty, list_not_empty)
{
	Struct_list_not_empty result_struct;
	
	struct_mapping::reg(&Struct_list_not_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": [1,2,3]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(1,2,3));
}

struct Struct_list_empty
{
	std::list<int> values;
};

TEST(option_not_empty, list_empty)
{
	Struct_list_empty result_struct;
	
	struct_mapping::reg(&Struct_list_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": []
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

struct Struct_list_not_exist
{
	std::list<int> values;
};

TEST(option_not_empty, list_not_exist)
{
	Struct_list_not_exist result_struct;
	
	struct_mapping::reg(&Struct_list_not_exist::values, "values", struct_mapping::NotEmpty{});

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

struct Struct_map_not_empty
{
	std::map<std::string, int> values;
};

TEST(option_not_empty, map_not_empty)
{
	Struct_map_not_empty result_struct;
	
	struct_mapping::reg(&Struct_map_not_empty::values, "values", struct_mapping::NotEmpty{});

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

struct Struct_map_empty
{
	std::map<std::string, int> values;
};

TEST(option_not_empty, map_empty)
{
	Struct_map_empty result_struct;
	
	struct_mapping::reg(&Struct_map_empty::values, "values", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
		"values": {}
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

struct Struct_map_not_exist
{
	std::map<std::string, int> values;
};

TEST(option_not_empty, map_not_exist)
{
	Struct_map_not_exist result_struct;
	
	struct_mapping::reg(&Struct_map_not_exist::values, "values", struct_mapping::NotEmpty{});

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
