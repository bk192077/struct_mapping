#ifndef STRUCT_MAPPING_MANAGED_ARRAY_H
#define STRUCT_MAPPING_MANAGED_ARRAY_H

#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "../debug.h"
#include "../exception.h"

namespace struct_mapping::managed {

template<typename T>
class ManagedArray {
public:
	std::vector<T> & get_data() {
		return data;
	}

	bool release() {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: ManagedArray::release: " << std::endl;
		if (!f_use) return true;

		if constexpr (!is_integral_or_floating_point_or_string<T>()) {
			if (data.back().release()) f_use = false;
		}

		return false;
	}

	template<typename E>
	void set(std::string const & name, E value) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: ManagedArray::set: " << name << " : " << std::boolalpha << value << std::endl;
		if (!f_use) {
			if constexpr (is_integral_or_floating_point_or_string<E>() && (
					std::is_same_v<T, E> ||	(
						!std::is_same_v<T, bool> &&
						!std::is_same_v<E, bool> &&
						(std::is_integral_v<T> ||	std::is_floating_point_v<T>) &&
						(std::is_integral_v<E> || std::is_floating_point_v<E>)))) {
				data.push_back(static_cast<T>(value));
			} else {
				throw StructMappingException(std::string("ManagedArray::set: attempt to add a value of the wrong type: name = ") + name);
			}
		} else {
			if constexpr (!is_integral_or_floating_point_or_string<T>()) data.back().set(name, value);
		}
	}

	void use(std::string const & name) {
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: ManagedArray::use: " << name << std::endl;
		if (!f_use) {
			data.emplace_back();
			f_use = true;
		} else {
			if constexpr (!is_integral_or_floating_point_or_string<T>()) data.back().use(name);
		}
	} 

private:
	std::vector<T> data;
	bool f_use = false;
	
	template<typename P>
	static constexpr bool is_integral_or_floating_point_or_string() {
		return std::is_integral_v<P> || std::is_floating_point_v<P> || std::is_same_v<T, std::string>;
	}
};

}

#define MANAGED_ARRAY(ELEMENT_TYPE) struct_mapping::managed::ManagedArray<ELEMENT_TYPE>
#define MANAGED_FIELD_ARRAY(ELEMENT_TYPE, FIELD_NAME) MANAGED_FIELD_STRUCT(MANAGED_ARRAY(ELEMENT_TYPE), FIELD_NAME)

#endif
