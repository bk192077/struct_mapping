#pragma once

#include "debug.h"
#include "iterate_over.h"
#include "object.h"
#include "object_array_like.h"
#include "object_map_like.h"
#include "parser.h"
#include "reset.h"
#include "utility.h"

#include <istream>
#include <ostream>
#include <string>

namespace struct_mapping
{

template<typename T>
inline void map_json_to_struct(T& result_struct, std::basic_istream<char>& json_data)
{
	detail::Reset::reset();

	unsigned struct_level = 0;

	auto set_bool = [&] (const std::string& name, bool value)
	{
		if constexpr (debug)
		{
			std::cout
				<< "struct_mapping: map_json_to_struct.set_bool: "
				<< name
				<< " : "
				<< std::boolalpha
				<< value
				<< std::endl;
		}

		detail::Object<T>::set_bool(result_struct, name, value);
	};

	auto set_integral = [&] (const std::string& name, long long value)
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.set_integral: " << name << " : " << value << std::endl;
		}

		detail::Object<T>::set_integral(result_struct, name, value);
	};

	auto set_floating_point = [&] (const std::string& name, double value)
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.set_floating_point: " << name << " : " << value << std::endl;
		}

		detail::Object<T>::set_floating_point(result_struct, name, value);
	};

	auto set_string = [&] (const std::string& name, const std::string& value)
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.set_string: " << name << " : " << value << std::endl;
		}

		detail::Object<T>::set_string(result_struct, name, value);
	};

	auto set_null = [] (const std::string& name)
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.set_null: " << name << std::endl;
		}
	};

	auto start_struct = [&] (const std::string& name)
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.start_struct: " << name << std::endl;
		}

		if (++struct_level == 1)
		{
			detail::Object<T>::init(result_struct);
		}
		else
		{
			detail::Object<T>::use(result_struct, name);
		}
	};

	auto end_struct = [&]
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.end_struct:" << std::endl;
		}

		detail::Object<T>::release(result_struct);
		--struct_level;
	};

	auto start_array = [&] (const std::string& name)
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.start_array: " << name << std::endl;
		}

		detail::Object<T>::use(result_struct, name);
	};

	auto end_array = [&]
	{
		if constexpr (debug)
		{
			std::cout << "struct_mapping: map_json_to_struct.end_array:" << std::endl;
		}

		detail::Object<T>::release(result_struct);
	};

	detail::Parser parser(
		set_bool,
		set_integral,
		set_floating_point,
		set_string,
		set_null,
		start_struct,
		end_struct,
		start_array,
		end_array);
	
	parser.parse(json_data);
}

template<typename T>
inline void map_struct_to_json(
	T& source_struct,
	std::basic_ostream<char>& json_data,
	std::string indent = "",
	bool hide_null = true)
{
	bool first_element = true;
	unsigned indent_count = 0;

	detail::IterateOver::set_null =	[&] (const std::string& name)
		{
			if constexpr (debug)
			{
				std::cout
					<< "struct_mapping: map_struct_to_json.set_null: "
					<< name
					<< std::endl;
			}

			if (!hide_null)
			{
				if (!first_element)
				{
					json_data << ",";
				}

				if (!indent.empty())
				{
					json_data << "\n";
				}

				for (unsigned i = indent_count; i != 0; --i)
				{
					json_data << indent; 
				}

				if (name.empty())
				{
					json_data << "null";
				}
				else
				{
					json_data << "\"" << name << "\":";
					
					if (!indent.empty())
					{
						json_data << " ";
					}

 					json_data << "null";
				}
			}

			first_element = false;
		};

	detail::IterateOver::set<bool> = [&] (const std::string& name, bool value)
		{
			if constexpr (debug)
			{
				std::cout
					<< "struct_mapping: map_struct_to_json.set<bool>: "
					<< name
					<< " : "
					<< std::boolalpha
					<< value
					<< std::endl;
			}

			if (!first_element)
			{
				json_data << ",";
			}

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			if (name.empty())
			{
				json_data << std::boolalpha << value;
			}
			else
			{
				json_data << "\"" << name << "\":";
					
				if (!indent.empty())
				{
					json_data << " ";
				}

				json_data << std::boolalpha << value;
			}

			first_element = false;
		};


	detail::IterateOver::set<long long> = [&] (const std::string& name, long long value)
		{
			if constexpr (debug)
			{
				std::cout << "struct_mapping: map_struct_to_json.set<long long>: " << name << " : " << value << std::endl;
			}

			if (!first_element)
			{
				json_data << ",";
			}

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			if (name.empty())
			{
				json_data << value;
			}
			else
			{
				json_data << "\"" << name << "\":";
					
				if (!indent.empty())
				{
					json_data << " ";
				}

				json_data << value;
			}

			first_element = false;
		};

	detail::IterateOver::set<double> = [&] (const std::string& name, double value)
		{
			if constexpr (debug)
			{
				std::cout << "struct_mapping: map_struct_to_json.set<double>: " << name << " : " << value << std::endl;
			}

			if (!first_element)
			{
				json_data << ",";
			}

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			if (name.empty())
			{
				json_data << value;
			}
			else
			{
				json_data << "\"" << name << "\":";
					
				if (!indent.empty())
				{
					json_data << " ";
				}

				json_data << value;
			}

			first_element = false;
		};

	detail::IterateOver::set<std::string> =	[&] (const std::string& name, std::string value)
		{
			if constexpr (debug)
			{
				std::cout
					<< "struct_mapping: map_struct_to_json.set<std::string>string: "
					<< name
					<< " : "
					<< value
					<< std::endl;
			}

			if (!first_element)
			{
				json_data << ",";
			}

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			if (name.empty())
			{
				json_data << "\"" << value << "\"";
			}
			else
			{
				json_data << "\"" << name << "\":";
					
				if (!indent.empty())
				{
					json_data << " ";
				}

				json_data << "\"" << value << "\"";
			}

			first_element = false;
		};

	detail::IterateOver::start_struct =	[&] (const std::string& name)
		{
			if constexpr (debug)
			{
				std::cout << "struct_mapping: map_struct_to_json.start_struct: " << name << std::endl;
			}

			if (!first_element)
			{
				json_data << ",";
			}

			if (indent_count != 0)
			{
				if (!indent.empty())
				{
					json_data << "\n";
				}
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			first_element = true;
			if (name.empty())
			{
				json_data << "{";
			}
			else
			{
				json_data << "\"" << name << "\":";
					
				if (!indent.empty())
				{
					json_data << " ";
				}

				json_data << "{";
			}

			++indent_count;
		};

	detail::IterateOver::end_struct =	[&] ()
		{
			if constexpr (debug)
			{
				std::cout << "struct_mapping: map_struct_to_json.end_struct:" << std::endl;
			}

			--indent_count;

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			json_data << "}";
			first_element = false;
		};

	detail::IterateOver::start_array = [&] (const std::string& name)
		{
			if constexpr (debug)
			{
				std::cout << "struct_mapping: map_struct_to_json.start_array: " << name << std::endl;
			}

			if (!first_element)
			{
				json_data << ",";
			}

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			first_element = true;
			if (name.empty())
			{
				json_data << "[";
			}
			else
			{
				json_data << "\"" << name << "\":";
					
				if (!indent.empty())
				{
					json_data << " ";
				}

				json_data << "[";
			}

			++indent_count;
		};

	detail::IterateOver::end_array = [&] ()
		{
			if constexpr (debug)
			{
				std::cout << "struct_mapping: map_struct_to_json.end_array:" << std::endl;
			}

			--indent_count;

			if (!indent.empty())
			{
				json_data << "\n";
			}

			for (unsigned i = indent_count; i != 0; --i)
			{
				json_data << indent; 
			}

			json_data << "]";
			first_element = false;
		};

	detail::Object<T>::iterate_over(source_struct, "");
}

} // struct_mapping