#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/exception.h"
#include "struct_mapping/managed/struct.h"

namespace {

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_long_long_throw_exception_on_unknown_field_name
BEGIN_MANAGED_STRUCT
END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_long_long_throw_exception_on_unknown_field_name) {
	struct_mapping_managed_struct_set_long_long_throw_exception_on_unknown_field_name test_struct;

	try {
		test_struct.set("name_0", 1LL);
	} catch (struct_mapping::StructMappingException&) {
		SUCCEED();
		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_double_throw_exception_on_unknown_field_name
BEGIN_MANAGED_STRUCT
END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_double_throw_exception_on_unknown_field_name) {
	struct_mapping_managed_struct_set_double_throw_exception_on_unknown_field_name test_struct;

	try {
		test_struct.set("name_0", 0.0);
	} catch (struct_mapping::StructMappingException&) {
		SUCCEED();
		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_template_throw_exception_on_unknown_field_name
BEGIN_MANAGED_STRUCT
END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_string_throw_exception_on_unknown_field_name) {
	struct_mapping_managed_struct_set_template_throw_exception_on_unknown_field_name test_struct;

	try {
		test_struct.set("name_0", std::string(""));
	} catch (struct_mapping::StructMappingException&) {
		SUCCEED();
		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_t_different_type
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(float, name_1)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_t_different_type_throw_unknown_field_name) {
	struct_mapping_managed_struct_set_t_different_type test_struct;

	try {
		test_struct.set("name_1", std::string("string"));
	} catch (struct_mapping::StructMappingException& e) {
		if (std::string("struct_mapping_managed_struct_set_t_different_type::set(std::string const &, std::string const &): unknown field name: name_1").compare(e.what()) == 0) {
			SUCCEED();
		} else {
			FAIL() << "Expected: throws an exception of type ManagedException with what(): struct_mapping_managed_struct_set_t_different_type::set(std::string const &, std::string const &): unknown field name: name_1\n  Actual: throws an exception of type ManagedException with what(): " << e.what();
		}

		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_long_long_different_type
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name_1)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_long_long_different_type_throw_unknown_field_name) {
	struct_mapping_managed_struct_set_long_long_different_type test_struct;

	try {
		test_struct.set("name_1", 1LL);
	} catch (struct_mapping::StructMappingException& e) {
		if (std::string("struct_mapping_managed_struct_set_long_long_different_type::set(std::string const &, long long): unknown field name: name_1").compare(e.what()) == 0) {
			SUCCEED();
		} else {
			FAIL() << "Expected: throws an exception of type ManagedException with what(): struct_mapping_managed_struct_set_long_long_different_type::set(std::string const &, long long): unknown field name: name_1\n  Actual: throws an exception of type ManagedException with what(): " << e.what();
		}

		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_double_different_type
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name_1)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_double_different_type_throw_unknown_field_name) {
	struct_mapping_managed_struct_set_double_different_type test_struct;

	try {
		test_struct.set("name_1", 1.0);
	} catch (struct_mapping::StructMappingException& e) {
		if (std::string("struct_mapping_managed_struct_set_double_different_type::set(std::string const &, double): unknown field name: name_1").compare(e.what()) == 0) {
			SUCCEED();
		} else {
			FAIL() << "Expected: throws an exception of type ManagedException with what(): struct_mapping_managed_struct_set_double_different_type::set(std::string const &, double): unknown field name: name_1\n  Actual: throws an exception of type ManagedException with what(): " << e.what();
		}

		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_long_long
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(int, name_1)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_long_long_with_long_long) {
	struct_mapping_managed_struct_set_long_long test_struct;

	ASSERT_NO_THROW({
		test_struct.set("name_1", 42LL);
	});

	ASSERT_EQ(test_struct.name_1, 42);
}

TEST(struct_mapping_managed_struct, set_long_long_with_double) {
	struct_mapping_managed_struct_set_long_long test_struct;

	ASSERT_NO_THROW({
		test_struct.set("name_1", 42.1);
	});

	ASSERT_EQ(test_struct.name_1, 42);
}

#define MANAGED_STRUCT_NAME struct_mapping_managed_struct_set_double
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(float, name_1)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_struct, set_double_with_double) {
	struct_mapping_managed_struct_set_double test_struct;

	ASSERT_NO_THROW({
		test_struct.set("name_1", 42.3);
	});

	ASSERT_EQ(test_struct.name_1, 42.3f);
}

TEST(struct_mapping_managed_struct, set_double_with_long_long) {
	struct_mapping_managed_struct_set_double test_struct;

	ASSERT_NO_THROW({
		test_struct.set("name_1", 42LL);
	});

	ASSERT_EQ(test_struct.name_1, 42.0f);
}

}
