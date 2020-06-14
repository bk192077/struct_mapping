#ifndef STRUCT_MAPPING_MAPPER_JSON_H
#define STRUCT_MAPPING_MAPPER_JSON_H

#include <functional>
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

template<typename T>
void map_struct_to_json(T & result_struct, std::basic_ostream<char> & json_data) {
	bool first_element = true;

	struct_mapping::managed::Fs_iterate_over::set_bool = [&json_data, &first_element] (std::string const & name, bool value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_bool: " << name << " : " << std::boolalpha << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << std::boolalpha << value;
		else json_data << "\"" << name << "\":" << std::boolalpha << value;
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::set_integral = [&json_data, &first_element] (std::string const & name, long long value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_integral: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\":" << value;
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::set_floating_point = [&json_data, &first_element] (std::string const & name, double value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_floating_point: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\":" << value;
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::set_string = [&json_data, &first_element] (std::string const & name, std::string value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_string: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << "\"" << value << "\"";
		else json_data << "\"" << name << "\":\"" << value << "\"";
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::start_struct = [&json_data, &first_element] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.start_struct: " << name << std::endl;
		if (!first_element) json_data << ",";
		first_element = true;
		if (name.empty()) json_data << "{";
		else json_data << "\"" << name << "\":{";
	};

	struct_mapping::managed::Fs_iterate_over::end_struct = [&json_data, &first_element] () {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.end_struct:" << std::endl;
		json_data << "}";
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::start_array = [&json_data, &first_element] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.start_array: " << name << std::endl;
		if (!first_element) json_data << ",";
		first_element = true;
		if (name.empty()) json_data << "[";
		else json_data << "\"" << name << "\":[";
	};

	struct_mapping::managed::Fs_iterate_over::end_array = [&json_data, &first_element] () {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.end_array:" << std::endl;
		json_data << "]";
		first_element = false;
	};

	result_struct.iterate_over("");
}

template<typename T>
void map_struct_to_json(T & result_struct, std::basic_ostream<char> & json_data, std::string indent) {
	bool first_element = true;
	int indent_count = 0;

	struct_mapping::managed::Fs_iterate_over::set_bool = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, bool value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_bool: " << name << " : " << std::boolalpha << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << std::boolalpha << value;
		else json_data << "\"" << name << "\": " << std::boolalpha << value;
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::set_integral = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, long long value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_integral: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\": " << value;
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::set_floating_point = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, double value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_floating_point: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\": " << value;
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::set_string = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, std::string value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.set_string: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << "\"" << value << "\"";
		else json_data << "\"" << name << "\": \"" << value << "\"";
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::start_struct = [&json_data, &first_element, &indent_count, &indent] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.start_struct: " << name << std::endl;
		if (!first_element) json_data << ",";
 		if (indent_count != 0) json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		first_element = true;
		if (name.empty()) json_data << "{";
		else json_data << "\"" << name << "\": {";
		++indent_count;
	};

	struct_mapping::managed::Fs_iterate_over::end_struct = [&json_data, &first_element, &indent_count, &indent] () {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.end_struct:" << std::endl;
		--indent_count;
		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		json_data << "}";
		first_element = false;
	};

	struct_mapping::managed::Fs_iterate_over::start_array = [&json_data, &first_element, &indent_count, &indent] (std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.start_array: " << name << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		first_element = true;
		if (name.empty()) json_data << "[";
		else json_data << "\"" << name << "\": [";
		++indent_count;
	};

	struct_mapping::managed::Fs_iterate_over::end_array = [&json_data, &first_element, &indent_count, &indent] () {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: map_struct_to_json.end_array:" << std::endl;
		--indent_count;
		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		json_data << "]";
		first_element = false;
	};

	result_struct.iterate_over("");
}

}

#endif
