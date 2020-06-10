#ifndef STRUCT_MAPPING_MAPPER_JSON_H
#define STRUCT_MAPPING_MAPPER_JSON_H

#include <istream>
#include <string>

#include "../debug.h"
#include "../parser/json.h"

namespace struct_mapping::mapper {

template<typename T>
void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data) {
	int struct_level = 0;

	auto set_bool = [&result_struct] (std::string const & name, bool value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.set_bool: " << name << " : " << std::boolalpha << value << std::endl;
		result_struct.set(name, value);
	};

	auto set_integral = [&result_struct] (std::string const & name, long long value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.set_integral: " << name << " : " << value << std::endl;
		result_struct.set(name, value);
	};

	auto set_floating_point = [&result_struct] (std::string const & name, double value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.set_loating_point: " << name << " : " << value << std::endl;
		result_struct.set(name, value);
	};

	auto set_string = [&result_struct] (std::string const & name, std::string const & value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.set_string: " << name << " : " << value << std::endl;
		result_struct.set(name, value);
	};

	auto set_null = [] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.set_null: " << name << std::endl;
	};

	auto start_struct = [&result_struct, &struct_level] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.start_struct: " << name << std::endl;
		if (++struct_level != 1) result_struct.use(name);
	};

	auto end_struct = [&result_struct, &struct_level] {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.end_struct:" << std::endl;
		if (--struct_level != 0) result_struct.release();
	};

	auto start_array = [&result_struct] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.start_array: " << name << std::endl;
		result_struct.use(name);
	};

	auto end_array = [&result_struct] {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_json_to_struct.end_array:" << std::endl;
		result_struct.release();
	};

	struct_mapping::parser::Json jp(
			set_bool,
			set_integral,
			set_floating_point,
			set_string,
			set_null,
			start_struct,
			end_struct,
			start_array,
			end_array);
		jp.parse(&json_data);
}

}

#endif
