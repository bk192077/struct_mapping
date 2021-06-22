#ifndef STRUCT_MAPPING_PARSER_H
#define STRUCT_MAPPING_PARSER_H

#include <istream>
#include <string>

#include "exception.h"

namespace struct_mapping::detail
{

template<
	typename SetBool,
	typename SetFloatingPoint,
	typename SetIntegral,
	typename SetString,
	typename SetNull,
	typename StartStruct,
	typename EndStruct,
	typename StartArray,
	typename EndArray>
class Parser
{
public:
	using stream_type = std::basic_istream<char>;

	Parser (
		SetBool set_bool_,
		SetIntegral set_integral_,
		SetFloatingPoint set_floating_point_,
		SetString set_string_,
		SetNull set_null_,
		StartStruct start_struct_,
		EndStruct end_struct_,
		StartArray start_array_,
		EndArray end_array_)
		:	set_bool(set_bool_),
			set_integral(set_integral_),
			set_floating_point(set_floating_point_),
			set_string(set_string_),
			set_null(set_null_),
			start_struct(start_struct_),
			end_struct(end_struct_),
			start_array(start_array_),
			end_array(end_array_)
	{}

	void parse(stream_type* data_)
	{
		data = data_;

		wait("{");
		start_struct("");
		parse_struct();
	}

private:
	SetBool set_bool;
	SetIntegral set_integral;
	SetFloatingPoint set_floating_point;
	SetString set_string;
	SetNull set_null;
	StartStruct start_struct;
	EndStruct end_struct;
	StartArray start_array;
	EndArray end_array;

	stream_type* data;
	size_t line_number = 1;
	char wait_char = '\0';

	stream_type& get_next_char(char& ch)
	{
		if (wait_char != '\0')
		{
			ch = wait_char;
			wait_char = '\0';
		}
		else
		{
			data->get(ch);
		}

		return *data;
	}

	std::string get_string()
	{
		std::string result;
		char next_ch;

		while (data->get(next_ch))
		{
			if (next_ch != '\"')
			{
				result += next_ch;
			}
			else if (next_ch == '\"')
			{
				return result;
			}
		}

		throw StructMappingException("parser: unexpected end of data");
	}

	bool is_empty_char(char ch) const
	{
		return ch == ' ' || ch == '\t' || ch == '\r';
	}

	bool is_new_line_char(char ch) const
	{
		return ch == '\n';
	}

	void parse_array()
	{
		constexpr const char* EXPECTED_AFTER_START = "]{[\"tf-.0123456789n";
		constexpr const char* EXPECTED_AFTER_VALUE = "]{[\"tf,-.0123456789n";
		constexpr const char* EXPECTED_AFTER_COMMA = "{[\"tf-.0123456789n";
		const char* expected_characters = EXPECTED_AFTER_START;

		for (;;)
		{
			char ch = wait(expected_characters);

			if (ch == ']')
			{
				end_array();
				return;
			} 

			if (ch == ',')
			{
				expected_characters = EXPECTED_AFTER_COMMA;
			}
			else
			{
				parse_array_value(ch);
				expected_characters = EXPECTED_AFTER_VALUE;
			}
		}
	}

	void parse_array_value(char start_ch)
	{
		std::string name("");
		if (start_ch == '{')
		{
			start_struct(name);
			parse_struct();
		}
		else if (start_ch == '[')
		{
			start_array(name);
			parse_array();
		}
		else if (start_ch == 't')
		{
			wait("r");
			wait("u");
			wait("e");
			set_bool(name, true);
		}
		else if (start_ch == 'f')
		{
			wait("a");
			wait("l");
			wait("s");
			wait("e");
			set_bool(name, false);
		}
		else if (start_ch == 'n')
		{
			wait("u");
			wait("l");
			wait("l");
			set_null(name);
		}
		else if (start_ch == '\"')
		{
			set_string(name, get_string());
		}
		else
		{
			set_number(name, start_ch);
		}
	}

	void parse_struct()
	{
		constexpr const char* EXPECTED_AFTER_START = "\"}";
		constexpr const char* EXPECTED_AFTER_VALUE = ",}";
		constexpr const char* EXPECTED_AFTER_COMMA = "\"";
		const char* expected_characters = EXPECTED_AFTER_START;

		for (;;)
		{
			char ch = wait(expected_characters);

			if (ch == '}')
			{
				end_struct();
				return;
			}

			if (ch == ',')
			{
				expected_characters = EXPECTED_AFTER_COMMA;
			}
			else
			{
				parse_struct_value();
				expected_characters = EXPECTED_AFTER_VALUE;
			}
		}
	}

	void parse_struct_value()
	{
		auto name = get_string();
		wait(":");

		char value_start_ch = wait("\"{[tf-0123456789n");

		if (value_start_ch == '{')
		{
			start_struct(name);
			parse_struct();
		}
		else if (value_start_ch == '[')
		{
			start_array(name);
			parse_array();
		}
		else if (value_start_ch == 't')
		{
			wait("r");
			wait("u");
			wait("e");
			set_bool(name, true);
		}
		else if (value_start_ch == 'f')
		{
			wait("a");
			wait("l");
			wait("s");
			wait("e");
			set_bool(name, false);
		}
		else if (value_start_ch == 'n')
		{
			wait("u");
			wait("l");
			wait("l");
			set_null(name);
		}
		else if (value_start_ch == '\"')
		{
			set_string(name, get_string());
		}
		else
		{
			set_number(name, value_start_ch);
		}
	}

	void set_number(std::string& name, char start_ch)
	{
		std::string value{start_ch};
		char next_ch;
		bool is_floating_point_number = false;

		for (;;)
		{
			next_ch = wait("}],.0123456789eE+-");
			if (next_ch == '.')
			{
				is_floating_point_number = true;
			}

			if (next_ch == ',' || next_ch == '}' || next_ch == ']')
			{
				wait_char = next_ch;
				try
				{
					if (is_floating_point_number)
					{
						set_floating_point(name, std::stod(value));
					}
					else
					{
						set_integral(name, std::stoll(value));
					}
				}
				catch (std::invalid_argument&)
				{
					throw StructMappingException(
						std::string("parser: bad number [") + value + std::string("] at line ") + std::to_string(line_number));
				}
				catch (std::out_of_range&)
				{
					throw StructMappingException(
						std::string("parser: bad number [") + value + std::string("] at line ") + std::to_string(line_number));
				}

				return;
			}

			value += next_ch;
		}
	}

	char wait(char const* characters_)
	{
		char test_ch;
		while (get_next_char(test_ch))
		{
			char const* characters = characters_;
			while (*characters)
			{
				if (test_ch ==*characters)
				{
					return test_ch;
				}

				++characters;
			}
 			
			if (is_new_line_char(test_ch))
			{
				++line_number;
			}
			else if (!is_empty_char(test_ch))
			{
				throw StructMappingException(
					std::string("parser: unexpected character '")
						+ std::string(1, test_ch)
						+ std::string("' at line ")
						+ std::to_string(line_number));
			}
		}

		throw StructMappingException("parser: unexpected end of data");
	}
};

} // struct_mapping::detail

#endif
