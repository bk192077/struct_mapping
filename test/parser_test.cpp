#include "struct_mapping/parser.h"

#include "gtest/gtest.h"

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

namespace
{

struct TestCase
{
	std::string title;
	std::string source;
	std::vector<std::string> expected;
};

struct TestCaseExceptionEndOfData
{
	std::string title;
	std::string source;
	std::string exception_message;
};

struct TestCaseExceptionUnexpectedCharacter
{
	std::string title;
	std::string source;
	std::string exception_message;
};

const std::vector<TestCase> test_cases
{
	{
		"empty top struct",
		R"json(
			{
			}
		)json",
		{
			"start_struct:",
			"end_struct",
		},
	},
	{
		"single object",
		R"json(
			{
				"name_1": "value_1"
			}
		)json",
		{
			"start_struct:",
			"set_string:name_1:value_1",
			"end_struct",
		},
	},
	{
		"multiple objects",
		R"json(
			{
				"name_1": "value_1",
				"name_2": "value_2",
				"name_3": "value_3"
			}
		)json",
		{
			"start_struct:",
			"set_string:name_1:value_1",
			"set_string:name_2:value_2",
			"set_string:name_3:value_3",
			"end_struct",
		},
	},
	{
		"null value",
		R"json(
			{
				"name_1": null
			}
		)json",
		{
			"start_struct:",
			"null:name_1",
			"end_struct",
		},
	},
	{
		"bool value true",
		R"json(
			{
				"name_1": true
			}
		)json",
		{
			"start_struct:",
			"set_bool:name_1:true",
			"end_struct",
		},
	},
	{
		"bool value false",
		R"json(
			{
				"name_1": false
			}
		)json",
		{
			"start_struct:",
			"set_bool:name_1:false",
			"end_struct",
		},
	},
	{
		"string value",
		R"json(
			{
				"name_1": "value_1"
			}
		)json",
		{
			"start_struct:",
			"set_string:name_1:value_1",
			"end_struct",
		},
	},
	{
		"integral zero",
		R"json(
			{
				"name_1": 0
			}
		)json",
		{
			"start_struct:",
			"set_integral:name_1:0",
			"end_struct",
		},
	},
	{
		"integral positive",
		R"json(
			{
				"name_1": 9223372036854775807
			}
		)json",
		{
			"start_struct:",
			"set_integral:name_1:9223372036854775807",
			"end_struct",
		},
	},
	{
		"integral negative",
		R"json(
			{
				"name_1": -9223372036854775807
			}
		)json",
		{
			"start_struct:",
			"set_integral:name_1:-9223372036854775807",
			"end_struct",
		},
	},
	{
		"floating point zero",
		R"json(
			{
				"name_1": 0.0
			}
		)json",
		{
			"start_struct:",
			"set_floating_point:name_1:0.0",
			"end_struct",
		},
	},
	{
		"floating point positive",
		R"json(
			{
				"name_1": 123456.789
			}
		)json",
		{
			"start_struct:",
			"set_floating_point:name_1:123456.789",
			"end_struct",
		},
	},
	{
		"floating point negative",
		R"json(
			{
				"name_1": -123456.789
			}
		)json",
		{
			"start_struct:",
			"set_floating_point:name_1:-123456.789",
			"end_struct",
		},
	},
	{
		"floating point positive with leading zero",
		R"json(
			{
				"name_1": 0.012345
			}
		)json",
		{
			"start_struct:",
			"set_floating_point:name_1:0.012345",
			"end_struct",
		},
	},
	{
		"floating point negative with leading zero",
		R"json(
			{
				"name_1": -0.012345
			}
		)json",
		{
			"start_struct:",
			"set_floating_point:name_1:-0.012345",
			"end_struct",
		},
	},
	{
		"single struct with single value",
		R"json(
			{
				"name_1": {
					"name_2": "value_2"
				}
			}
		)json",
		{
			"start_struct:",
			"start_struct:name_1",
			"set_string:name_2:value_2",
			"end_struct",
			"end_struct",
		},
	},
	{
		"multiple structs with single value",
		R"json(
			{
				"name_1": {
					"name_2": "value_2"
				},
				"name_11": {
					"name_12": "value_12"
				},
				"name_21": {
					"name_22": "value_22"
				}
			}
		)json",
		{
			"start_struct:",
			"start_struct:name_1",
			"set_string:name_2:value_2",
			"end_struct",
			"start_struct:name_11",
			"set_string:name_12:value_12",
			"end_struct",
			"start_struct:name_21",
			"set_string:name_22:value_22",
			"end_struct",
			"end_struct",
		},
	},
	{
		"nested struct without value",
		R"json(
			{
				"name_1": {
					"name_2": {
						"name_3": {
							"name_4": {
							}
						}
					}
				}
			}
		)json",
		{
			"start_struct:",
			"start_struct:name_1",
			"start_struct:name_2",
			"start_struct:name_3",
			"start_struct:name_4",
			"end_struct",
			"end_struct",
			"end_struct",
			"end_struct",
			"end_struct",
		},
	},
	{
		"nested struct with value",
		R"json(
			{
				"name_1": {
					"name_1_value": "value_1",
					"name_2": {
						"name_3": {
							"name_3_value": "value_3",
							"name_4": {
								"name_4_value": "value_4"
							}
						},
						"name_2_value": "value_2"
					}
				}
			}
		)json",
		{
			"start_struct:",
			"start_struct:name_1",
			"set_string:name_1_value:value_1",
			"start_struct:name_2",
			"start_struct:name_3",
			"set_string:name_3_value:value_3",
			"start_struct:name_4",
			"set_string:name_4_value:value_4",
			"end_struct",
			"end_struct",
			"set_string:name_2_value:value_2",
			"end_struct",
			"end_struct",
			"end_struct",
		},
	},
	{
		"empty array",
		R"json(
			{
				"name_1": []
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"end_array",
			"end_struct",
		},
	},
	{
		"array of bool",
		R"json(
			{
				"name_1": [
					true,
					false,
					false,
					true
				]
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"set_bool::true",
			"set_bool::false",
			"set_bool::false",
			"set_bool::true",
			"end_array",
			"end_struct",
		},
	},
	{
		"array of string",
		R"json(
			{
				"name_1": [
					"string_value_1",
					"string_value_2",
					"string_value_3"
				]
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"set_string::string_value_1",
			"set_string::string_value_2",
			"set_string::string_value_3",
			"end_array",
			"end_struct",
		},
	},
	{
		"array of number",
		R"json(
			{
				"name_1": [
					0,
					-9223372036854775807,
					9223372036854775807,
					0.0,
					-123456.987,
					-0.987654321,
					123456.987,
					0.987654321
				]
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"set_integral::0",
			"set_integral::-9223372036854775807",
			"set_integral::9223372036854775807",
			"set_floating_point::0.0",
			"set_floating_point::-123456.987",
			"set_floating_point::-0.987654",
			"set_floating_point::123456.987",
			"set_floating_point::0.987654",
			"end_array",
			"end_struct",
		},
	},
	{
		"array of struct",
		R"json(
			{
				"name_1": [
					{
						"name_2": "string_value_1",
						"name_3": true
					},
					{
						"name_2": "string_value_2",
						"name_3": false
					}
				]
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"start_struct:",
			"set_string:name_2:string_value_1",
			"set_bool:name_3:true",
			"end_struct",
			"start_struct:",
			"set_string:name_2:string_value_2",
			"set_bool:name_3:false",
			"end_struct",
			"end_array",
			"end_struct",
		},
	},
	{
		"array of array",
		R"json(
			{
				"name_1": [
					[
						"string_value_1",
						"string_value_2",
						"string_value_3"
					],
					[],
					[
						"string_value_4",
						"string_value_5",
						"string_value_6"
					]
				]
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"start_array:",
			"set_string::string_value_1",
			"set_string::string_value_2",
			"set_string::string_value_3",
			"end_array",
			"start_array:",
			"end_array",
			"start_array:",
			"set_string::string_value_4",
			"set_string::string_value_5",
			"set_string::string_value_6",
			"end_array",
			"end_array",
			"end_struct",
		},
	},
	{
		"null in struct",
		R"json(
			{
				"name_1": null
			}
		)json",
		{
			"start_struct:",
			"null:name_1",
			"end_struct",
		},
	},
	{
		"null in array",
		R"json(
			{
				"name_1": [
					null,
					null,
					null
				]
			}
		)json",
		{
			"start_struct:",
			"start_array:name_1",
			"null:",
			"null:",
			"null:",
			"end_array",
			"end_struct",
		},
	},
	{
		"russian",
		R"json(
			{
				"name_1": "русский язык"
			}
		)json",
		{
			"start_struct:",
			"set_string:name_1:русский язык",
			"end_struct",
		},
	},
};

const std::vector<TestCaseExceptionEndOfData> test_cases_exception_end_of_data
{
	{
		"end of data",
		R"json(
			{
				"name": [
					true
		)json",
		"parser: unexpected end of data"
	},
	{
		"end of data in string",
		R"json(
			{
				"name_1": {
					"name_2": "42
		)json",
		"parser: unexpected end of data"
	},
};

const std::vector<TestCaseExceptionUnexpectedCharacter> test_cases_exception_unexpected_character
{
	{
		"unexpected character after begin of the struct",
		R"json(
			{
				true
		)json",
		"parser: unexpected character 't' at line 3"
	},
	{
		"unexpected character after comma in the struct",
		R"json(
			{
				"name": true,
			}
		)json",
		"parser: unexpected character '}' at line 4"
	},
	{
		"unexpected character after value in the struct",
		R"json(
			{
				"name": true
				false
		)json",
		"parser: unexpected character 'f' at line 4"
	},
};

std::string trim_zero(std::string number)
{
	size_t length;
	for (length = number.size() - 1; number[length] == '0'; --length);

	if (number[length] == '.')
	{
		number = number.substr(0, length + 2);
	}
	else
	{
		number = number.substr(0, length + 1);
	}

	return number;
}

TEST(parser, test_cases)
{
	for(const auto& t : test_cases)
	{
		std::cout << "TEST CASE [" << t.title << "] : RUN" << std::endl;

		std::vector<std::string> result;
		std::istringstream data(t.source);

		auto set_bool = [&result] (const std::string& name, bool value)
		{
			result.push_back("set_bool:" + name + ":" + (value ? "true" : "false"));
		};

		auto set_integral = [&result] (const std::string& name, long long value)
		{
			result.push_back("set_integral:" + name + ":" + std::to_string(value));
		};

		auto set_floating_point = [&result] (const std::string& name, double value)
		{
			result.push_back("set_floating_point:" + name + ":" + trim_zero(std::to_string(value)));
		};

		auto set_string = [&result] (const std::string& name, const std::string& value)
		{
			result.push_back("set_string:" + name + ":" + value);
		};

		auto set_null = [&result] (const std::string& name)
		{
			result.push_back("null:" + name);
		};

		auto start_struct = [&result] (const std::string& name)
		{
			result.push_back("start_struct:" + name);
		};

		auto end_struct = [&result] {
			result.push_back("end_struct");
		};

		auto start_array = [&result] (const std::string& name)
		{
			result.push_back("start_array:" + name);
		};

		auto end_array = [&result]
		{
			result.push_back("end_array");
		};

		struct_mapping::detail::Parser parser(
			set_bool,
			set_integral,
			set_floating_point,
			set_string,
			set_null,
			start_struct,
			end_struct,
			start_array,
			end_array);
		
		parser.parse(data);

		ASSERT_EQ(t.expected, result) << "=== [ title  : " << t.title << " ] ===";
	}
}

TEST(parser, test_cases_exception_end_of_data)
{
	for(const auto& t : test_cases_exception_end_of_data)
	{
		std::cout << "TEST CASE [" << t.title << "] : RUN" << std::endl;

		std::istringstream data(t.source);

		auto set_bool = [] (const std::string&, bool) {};
		auto set_integral = [] (const std::string&, long long) {};
		auto set_floating_point = [] (const std::string&, double) {};
		auto set_string = [] (const std::string&, const std::string&) {};
		auto set_null = [] (const std::string&) {};
		auto start_struct = [] (const std::string&) {};
		auto end_struct = [] {};
		auto start_array = [] (const std::string&) {};
		auto end_array = [] {};

		try
		{
			struct_mapping::detail::Parser parser(
				set_bool,
				set_integral,
				set_floating_point,
				set_string,
				set_null,
				start_struct,
				end_struct,
				start_array,
				end_array);

			parser.parse(data);
		}
		catch (struct_mapping::StructMappingException& e)
		{
			if (t.exception_message.compare(e.what()) != 0)
			{
				FAIL()
					<< "Expected: exception message: "
					<< t.exception_message
					<< "\n  Actual: exception message: "
					<< e.what();
			}

			continue;
		}
		catch (...)
		{
			FAIL() << "Expected: throws an exception of type ExceptionEndOfData\n  Actual: it throws a different type";
		}

		FAIL() << "Expected: throws an exception of type ExceptionEndOfData\n  Actual: it throws nothing";
	}
}

TEST(parser, test_cases_exception_unexpected_character)
{
	for(const auto& t : test_cases_exception_unexpected_character)
	{
		std::cout << "TEST CASE [" << t.title << "] : RUN" << std::endl;

		std::istringstream data(t.source);

		auto set_bool = [] (const std::string&, bool) {};
		auto set_integral = [] (const std::string&, long long) {};
		auto set_floating_point = [] (const std::string&, double) {};
		auto set_string = [] (const std::string&, const std::string&) {};
		auto set_null = [] (const std::string&) {};
		auto start_struct = [] (const std::string&) {};
		auto end_struct = [] {};
		auto start_array = [] (const std::string&) {};
		auto end_array = [] {};

		try
		{
			struct_mapping::detail::Parser parser(
				set_bool,
				set_integral,
				set_floating_point,
				set_string,
				set_null,
				start_struct,
				end_struct,
				start_array,
				end_array);

			parser.parse(data);
		}
		catch (struct_mapping::StructMappingException& e)
		{
			if (t.exception_message.compare(e.what()) != 0)
			{
				FAIL()
					<< "Expected: exception message: "
					<< t.exception_message
					<< "\n  Actual: exception message: "
					<< e.what();
			}

			continue;
		}
		catch (...)
		{
			FAIL()
				<< "Expected: throws an exception of type ExceptionUnexpectedCharacter\n  Actual: it throws a different type";
		}

		FAIL() << "Expected: throws an exception of type ExceptionUnexpectedCharacter\n  Actual: it throws nothing";
	}
}

TEST(parser, positive_floating_point_with_positive_exponent)
{
	std::istringstream data(
		R"json(
			{
				"name": 19.345e156
			}
		)json"
	);

	auto set_bool = [] (const std::string&, bool) {};
	auto set_integral = [] (const std::string&, long long) {};

	auto set_floating_point = [] (const std::string&, double value)
	{
		ASSERT_DOUBLE_EQ(value, 19.345e156);
	};

	auto set_string = [] (const std::string&, const std::string&) {};
	auto set_null = [] (const std::string&) {};
	auto start_struct = [] (const std::string&) {};
	auto end_struct = [] {};
	auto start_array = [] (const std::string&) {};
	auto end_array = [] {};

	struct_mapping::detail::Parser parser(
		set_bool,
		set_integral,
		set_floating_point,
		set_string,
		set_null,
		start_struct,
		end_struct,
		start_array,
		end_array);

	parser.parse(data);
}

TEST(parser, negative_floating_point_with_negative_exponent)
{
	std::istringstream data(
		R"json(
			{
				"name": -19.345e-156
			}
		)json"
	);

	auto set_bool = [] (const std::string&, bool) {};
	auto set_integral = [] (const std::string&, long long) {};

	auto set_floating_point = [] (const std::string&, double value)
	{
		ASSERT_DOUBLE_EQ(value, -19.345E-156);
	};

	auto set_string = [] (const std::string&, const std::string&) {};
	auto set_null = [] (const std::string&) {};
	auto start_struct = [] (const std::string&) {};
	auto end_struct = [] {};
	auto start_array = [] (const std::string&) {};
	auto end_array = [] {};

	struct_mapping::detail::Parser parser(
		set_bool,
		set_integral,
		set_floating_point,
		set_string,
		set_null,
		start_struct,
		end_struct,
		start_array,
		end_array);

	parser.parse(data);
}

TEST(parser, exception_bad_number_invalid_argument)
{
	std::istringstream data(
		R"json(
			{
				"name": -...99999
			}
		)json"
	);

	auto set_bool = [] (const std::string&, bool) {};
	auto set_integral = [] (const std::string&, long long) {};
	auto set_floating_point = [] (const std::string&, double) {};
	auto set_string = [] (const std::string&, const std::string&) {};
	auto set_null = [] (const std::string&) {};
	auto start_struct = [] (const std::string&) {};
	auto end_struct = [] {};
	auto start_array = [] (const std::string&) {};
	auto end_array = [] {};

	try
	{
		struct_mapping::detail::Parser parser(
			set_bool,
			set_integral,
			set_floating_point,
			set_string,
			set_null,
			start_struct,
			end_struct,
			start_array,
			end_array);

		parser.parse(data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		if (std::string("parser: bad number [-...99999] at line 4").compare(e.what()) != 0)
		{
			FAIL()
				<< "Expected: exception message: parser: bad number [-...99999] at line 4\n  Actual: exception message: "
				<< e.what();
		}

		SUCCEED();
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type ExceptionBadNumber\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ExceptionBadNumber\n  Actual: it throws nothing";
}

TEST(parser, exception_bad_number_out_of_range)
{
	std::istringstream data(
		R"json(
			{
				"name": 10.0e99999
			}
		)json"
	);

	auto set_bool = [] (const std::string&, bool) {};
	auto set_integral = [] (const std::string&, long long) {};
	auto set_floating_point = [] (const std::string&, double) {};
	auto set_string = [] (const std::string&, const std::string&) {};
	auto set_null = [] (const std::string&) {};
	auto start_struct = [] (const std::string&) {};
	auto end_struct = [] {};
	auto start_array = [] (const std::string&) {};
	auto end_array = [] {};

	try
	{
		struct_mapping::detail::Parser parser(
			set_bool,
			set_integral,
			set_floating_point,
			set_string,
			set_null,
			start_struct,
			end_struct,
			start_array,
			end_array);

		parser.parse(data);
	}
	catch (struct_mapping::StructMappingException& e)
	{
		if (std::string("parser: bad number [10.0e99999] at line 4").compare(e.what()) != 0)
		{
			FAIL()
				<< "Expected: exception message: parser: bad number [10.0e99999] at line 4\n  Actual: exception message: "
				<< e.what();
		}

		SUCCEED();
		return;
	}
	catch (...)
	{
		FAIL() << "Expected: throws an exception of type ExceptionBadNumber\n  Actual: it throws a different type";
	}

	FAIL() << "Expected: throws an exception of type ExceptionBadNumber\n  Actual: it throws nothing";
}

} // namespace
