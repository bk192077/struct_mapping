#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/exception.h"
#include "struct_mapping/managed/array.h"
#include "struct_mapping/managed/struct.h"

using ::testing::ElementsAreArray;

namespace {

TEST(struct_mapping_managed_array, set_bool) {
	struct_mapping::managed::ManagedArray<bool> ar;

	ar.set("", false);
	ar.set("", true);
	ar.set("", true);
	ar.set("", false);
	ar.set("", true);

	ASSERT_THAT(ar.get_data(), ElementsAreArray({
		false,
		true,
		true,
		false,
		true
	}));
}

TEST(struct_mapping_managed_array, set_int) {
	struct_mapping::managed::ManagedArray<int> ar;

	ar.set("", 42);
	ar.set("", -424242);
	ar.set("", 1.23);

	ASSERT_THAT(ar.get_data(), ElementsAreArray({
		42,
		-424242,
		1
	}));
}

TEST(struct_mapping_managed_array, set_double) {
	struct_mapping::managed::ManagedArray<double> ar;

	ar.set("", 42);
	ar.set("", -424242);
	ar.set("", 1.23);

	ASSERT_THAT(ar.get_data(), ElementsAreArray({
		42.0,
		-424242.0,
		1.23
	}));
}

TEST(struct_mapping_managed_array, set_string) {
	struct_mapping::managed::ManagedArray<std::string> ar;

	ar.set("", std::string("42"));
	ar.set("", std::string("-424242"));
	ar.set("", std::string("1.23"));

	ASSERT_THAT(ar.get_data(), ElementsAreArray({
		"42",
		"-424242",
		"1.23"
	}));
}

class struct_mapping_managed_array {
public:
	struct_mapping_managed_array()
		:	history(":ctor") {}

	bool release() {
		if (f_use) {
			history += std::string(":release:false");
			f_use = false;
			return false;
		}

		history += std::string(":release:true");
		return true;
	}

	void set(std::string name, int value) {
		history += std::string(":set:") + name + std::string(":") + std::to_string(value);
	}

	void use(std::string name) {
		history += std::string(":use:") + name;
		f_use = true;
	}

	std::string history = "";
	bool f_use = false;
};

TEST(struct_mapping_managed_array, use_for_new_element) {
	struct_mapping::managed::ManagedArray<struct_mapping_managed_array> ar;

	ar.use("");

	ASSERT_EQ(ar.get_data()[0].history, ":ctor");
}

TEST(struct_mapping_managed_array, use_for_existing_element) {
	struct_mapping::managed::ManagedArray<struct_mapping_managed_array> ar;

	ar.use("");
	ar.use("name_1");

	ASSERT_EQ(ar.get_data()[0].history, ":ctor:use:name_1");
}

TEST(struct_mapping_managed_array, release) {
	struct_mapping::managed::ManagedArray<struct_mapping_managed_array> ar;

	ar.use("");
	ar.use("name_1");
	ASSERT_FALSE(ar.release());
	ASSERT_FALSE(ar.release());
	ASSERT_TRUE(ar.release());

	ASSERT_EQ(ar.get_data()[0].history, ":ctor:use:name_1:release:false:release:true");
}

TEST(struct_mapping_managed_array, set_managed) {
	struct_mapping::managed::ManagedArray<struct_mapping_managed_array> ar;

	ar.use("");
	ar.set("name_1", 42);
	ASSERT_FALSE(ar.release());
	ASSERT_TRUE(ar.release());

	ASSERT_EQ(ar.get_data()[0].history, ":ctor:set:name_1:42:release:true");
}

#define MANAGED_STRUCT_NAME set_string_instead_of_student_Student
BEGIN_MANAGED_STRUCT

MANAGED_FIELD(std::string, name)

END_MANAGED_STRUCT
#undef MANAGED_STRUCT_NAME

TEST(struct_mapping_managed_array, set_string_instead_of_student) {
	struct_mapping::managed::ManagedArray<set_string_instead_of_student_Student> ar;

	try {
		ar.set("name", std::string("student name"));
	} catch (struct_mapping::StructMappingException& e) {
		if (std::string("ManagedArray::set: attempt to add a value of the wrong type: name = name").compare(e.what()) == 0) {
			SUCCEED();
		} else {
			FAIL() << "Expected: throws an exception of type ManagedException with what(): ManagedArray::set: attempt to add a value of the wrong type: name = name\n  Actual: throws an exception of type ManagedException with what(): " << e.what();
		}

		return;
	} catch (...) {
		FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ManagedException\n  Actual: it throws nothing";
}

}
