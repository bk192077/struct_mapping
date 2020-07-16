#ifndef STRUCT_MAPPING_MAPPER_H
#define STRUCT_MAPPING_MAPPER_H

#include <functional>
#include <istream>
#include <iostream>
#include <ostream>
#include <string>

#include "debug.h"
#include "f.h"
#include "f_array_like.h"
#include "f_map_like.h"
#include "f_struct.h"
#include "parser.h"

namespace struct_mapping {

template<typename T>
inline void map_json_to_struct(T & result_struct, std::basic_istream<char> & json_data) {
	detail::F_reset::reset();
	int struct_level = 0;

	auto set_bool = [&result_struct] (std::string const & name, bool value) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.set_bool: " << name << " : " << std::boolalpha << value << std::endl;
		detail::F<T>::set_bool(result_struct, name, value);
	};

	auto set_integral = [&result_struct] (std::string const & name, long long value) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.set_integral: " << name << " : " << value << std::endl;
		detail::F<T>::set_integral(result_struct, name, value);
	};

	auto set_floating_point = [&result_struct] (std::string const & name, double value) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.set_loating_point: " << name << " : " << value << std::endl;
		detail::F<T>::set_floating_point(result_struct, name, value);
	};

	auto set_string = [&result_struct] (std::string const & name, std::string const & value) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.set_string: " << name << " : " << value << std::endl;
		detail::F<T>::set_string(result_struct, name, value);
	};

	auto set_null = [] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.set_null: " << name << std::endl;
	};

	auto start_struct = [&result_struct, &struct_level] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.start_struct: " << name << std::endl;
		if (++struct_level == 1) detail::F<T>::init();
		else detail::F<T>::use(result_struct, name);
	};

	auto end_struct = [&result_struct, &struct_level] {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.end_struct:" << std::endl;
		detail::F<T>::release(result_struct);
		--struct_level;
	};

	auto start_array = [&result_struct] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.start_array: " << name << std::endl;
		detail::F<T>::use(result_struct, name);
	};

	auto end_array = [&result_struct] {
		if constexpr (debug) std::cout << "struct_mapping: map_json_to_struct.end_array:" << std::endl;
		detail::F<T>::release(result_struct);
	};

	detail::Parser jp(
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
inline void map_struct_to_json(T & source_struct, std::basic_ostream<char> & json_data) {
	bool first_element = true;

	detail::F_iterate_over::set_bool = [&json_data, &first_element] (std::string const & name, bool value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_bool: " << name << " : " << std::boolalpha << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << std::boolalpha << value;
		else json_data << "\"" << name << "\":" << std::boolalpha << value;
		first_element = false;
	};

	detail::F_iterate_over::set_integral = [&json_data, &first_element] (std::string const & name, long long value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_integral: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\":" << value;
		first_element = false;
	};

	detail::F_iterate_over::set_floating_point = [&json_data, &first_element] (std::string const & name, double value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_floating_point: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\":" << value;
		first_element = false;
	};

	detail::F_iterate_over::set_string = [&json_data, &first_element] (std::string const & name, std::string value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_string: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
		if (name.empty()) json_data << "\"" << value << "\"";
		else json_data << "\"" << name << "\":\"" << value << "\"";
		first_element = false;
	};

	detail::F_iterate_over::start_struct = [&json_data, &first_element] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.start_struct: " << name << std::endl;
		if (!first_element) json_data << ",";
		first_element = true;
		if (name.empty()) json_data << "{";
		else json_data << "\"" << name << "\":{";
	};

	detail::F_iterate_over::end_struct = [&json_data, &first_element] () {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.end_struct:" << std::endl;
		json_data << "}";
		first_element = false;
	};

	detail::F_iterate_over::start_array = [&json_data, &first_element] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.start_array: " << name << std::endl;
		if (!first_element) json_data << ",";
		first_element = true;
		if (name.empty()) json_data << "[";
		else json_data << "\"" << name << "\":[";
	};

	detail::F_iterate_over::end_array = [&json_data, &first_element] () {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.end_array:" << std::endl;
		json_data << "]";
		first_element = false;
	};

	detail::F<T>::iterate_over(source_struct, "");
}

template<typename T>
inline void map_struct_to_json(T & source_struct, std::basic_ostream<char> & json_data, std::string indent) {
	bool first_element = true;
	int indent_count = 0;

	detail::F_iterate_over::set_bool = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, bool value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_bool: " << name << " : " << std::boolalpha << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << std::boolalpha << value;
		else json_data << "\"" << name << "\": " << std::boolalpha << value;
		first_element = false;
	};

	detail::F_iterate_over::set_integral = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, long long value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_integral: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\": " << value;
		first_element = false;
	};

	detail::F_iterate_over::set_floating_point = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, double value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_floating_point: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << value;
		else json_data << "\"" << name << "\": " << value;
		first_element = false;
	};

	detail::F_iterate_over::set_string = [&json_data, &first_element, &indent_count, &indent] (std::string const & name, std::string value) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.set_string: " << name << " : " << value << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		if (name.empty()) json_data << "\"" << value << "\"";
		else json_data << "\"" << name << "\": \"" << value << "\"";
		first_element = false;
	};

	detail::F_iterate_over::start_struct = [&json_data, &first_element, &indent_count, &indent] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.start_struct: " << name << std::endl;
		if (!first_element) json_data << ",";
 		if (indent_count != 0) json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		first_element = true;
		if (name.empty()) json_data << "{";
		else json_data << "\"" << name << "\": {";
		++indent_count;
	};

	detail::F_iterate_over::end_struct = [&json_data, &first_element, &indent_count, &indent] () {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.end_struct:" << std::endl;
		--indent_count;
		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		json_data << "}";
		first_element = false;
	};

	detail::F_iterate_over::start_array = [&json_data, &first_element, &indent_count, &indent] (std::string const & name) {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.start_array: " << name << std::endl;
		if (!first_element) json_data << ",";
 		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		first_element = true;
		if (name.empty()) json_data << "[";
		else json_data << "\"" << name << "\": [";
		++indent_count;
	};

	detail::F_iterate_over::end_array = [&json_data, &first_element, &indent_count, &indent] () {
		if constexpr (debug) std::cout << "struct_mapping: map_struct_to_json.end_array:" << std::endl;
		--indent_count;
		json_data << "\n";
		for (int i = indent_count; i != 0; --i) json_data << indent; 
		json_data << "]";
		first_element = false;
	};

	detail::F<T>::iterate_over(source_struct, "");
}

}

#endif
