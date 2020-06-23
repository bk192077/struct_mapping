#ifndef STRUCT_MAPPING_F_MAP_H
#define STRUCT_MAPPING_F_MAP_H

#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "f.h"
#include "f_struct.h"

namespace struct_mapping::detail {
					
template<typename T>
class F<T, false, true> {
public:
	template<typename V>
	using Member_ptr = V T::*;

	template<typename V>
	using ValueType = typename V::mapped_type;

	using Iterator = typename T::iterator;

	static void iterate_over(T & o, const std::string & name) {
		F_iterate_over::start_struct(name);
		
		for (auto & [n, v] : o) {
			if constexpr (std::is_same_v<ValueType<T>, bool>) F_iterate_over::set_bool(n, v);
			else if constexpr (std::is_integral_v<ValueType<T>>) F_iterate_over::set_integral(n, v);
			else if constexpr (std::is_floating_point_v<ValueType<T>>) F_iterate_over::set_floating_point(n, v);
			else if constexpr (std::is_same_v<ValueType<T>, std::string>) F_iterate_over::set_string(n, v);
			else F<ValueType<T>>::iterate_over(v, n);
		}

		F_iterate_over::end_struct();
	}

	static bool release(T &) {
		if (!used) {
			return true;
		}	else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				if (F<ValueType<T>>::release(get_last_inserted())) {
					used = false;
				}
				return false;
			}
		}
		return false;
	}

	static void set_bool(T & o, const std::string & name, bool value) {
		if (!used) {
			if constexpr (std::is_same_v<ValueType<T>, bool>) {
				last_inserted = insert(o, name, value);
			}
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_bool(get_last_inserted(), name, value);
			}
		}
	}

	static void set_floating_point(T & o, const std::string & name, double value) {
		if (!used) {
			if constexpr ((std::is_integral_v<ValueType<T>> || std::is_floating_point_v<ValueType<T>>) && !std::is_same_v<ValueType<T>, bool>) {
				last_inserted = insert(o, name, static_cast<ValueType<T>>(value));
			}
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_floating_point(get_last_inserted(), name, value);
			}
		}
	}

	static void set_integral(T & o, const std::string & name, long long value) {
		if (!used) {
			if constexpr ((std::is_integral_v<ValueType<T>> || std::is_floating_point_v<ValueType<T>>) && !std::is_same_v<ValueType<T>, bool>) {
				last_inserted = insert(o, name, static_cast<ValueType<T>>(value));
			}
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_integral(get_last_inserted(), name, value);
			}
		}
	}

	static void set_string(T & o, const std::string & name, const std::string & value) {
		if (!used) {
			if constexpr (std::is_same_v<ValueType<T>, std::string>) {
				last_inserted = insert(o, name, value);
			}
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_string(get_last_inserted(), name, value);
			}
		}
	}

	static void use(T & o, const std::string & name) {
		if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
			if (!used) {
				used = true;
				last_inserted = insert(o, name, ValueType<T>{});
			}	else {
				F<ValueType<T>>::use(get_last_inserted(), name);
			}
		}
	}

private:
	static inline bool used = false;
	static inline Iterator last_inserted;

	static auto & get_last_inserted() {
		if constexpr (has_mapped_type_v<T>) return last_inserted->second;
		else return *last_inserted;
	}

	template<typename V>
	static Iterator insert(T & o, const std::string & name, const V & value) {
		if constexpr (std::is_same_v<decltype(std::declval<T>().insert(typename T::value_type())), std::pair<Iterator, bool>>) {
			auto [it, ok] = o.insert(std::make_pair(name, value));
			return it;
		} else if constexpr (std::is_same_v<decltype(std::declval<T>().insert(typename T::value_type())), Iterator>) {
			return o.insert(std::make_pair(name, value));
		}
	}
};

}

#endif
