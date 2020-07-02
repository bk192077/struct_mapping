#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "struct_mapping/struct_mapping.h"

namespace {

struct Struct_not_empty {
	std::string name;
};

TEST(option_not_empty, non_empty_empty) {
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

struct Struct_empty {
	std::string name;
};

TEST(option_not_empty, empty_value) {
	Struct_empty result_struct;
	
	struct_mapping::reg(&Struct_empty::name, "name", struct_mapping::NotEmpty{});

	std::istringstream json_data(R"json(
	{
	}
	)json");


	try {
		struct_mapping::map_json_to_struct(result_struct, json_data);
	} catch (struct_mapping::StructMappingException& e) {
		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type StructMappingException\n  Actual: it throws nothing";
}

}
