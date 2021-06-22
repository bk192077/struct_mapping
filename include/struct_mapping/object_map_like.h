#ifndef STRUCT_MAPPING_OBJECT_MAP_LIKE_H
#define STRUCT_MAPPING_OBJECT_MAP_LIKE_H

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "iterate_over.h"
#include "member_string.h"
#include "object.h"
#include "options/option_not_empty.h"
#include "utility.h"

namespace struct_mapping::detail
{
					
template<typename T>
class Object<T, false, true>
{
public:
	using Iterator = typename T::iterator;

	template<typename V>
	using ValueType = typename V::mapped_type;

	static void check_not_empty(T& o, const std::string& name)
	{
		NotEmpty<>::check_result(o, name);
	}

	static void init() {}

	static void iterate_over(T& o, const std::string& name)
	{
		IterateOver::start_struct(name);
		
		for (auto& [n, v] : o)
		{
			if constexpr (std::is_same_v<ValueType<T>, bool>)
			{
				IterateOver::set<bool>(n, v);
			}
			else if constexpr (std::is_integral_v<ValueType<T>>)
			{
				IterateOver::set<long long>(n, v);
			}
			else if constexpr (std::is_floating_point_v<ValueType<T>>)
			{
				IterateOver::set<double>(n, v);
			}
			else if constexpr (std::is_same_v<ValueType<T>, std::string>)
			{
				IterateOver::set<std::string>(n, v);
			}
			else if constexpr (std::is_enum_v<ValueType<T>>)
			{
				IterateOver::set<std::string>(n, MemberString<ValueType<T>>::to_string()(v));
			}
			else
			{
				if (IsMemberStringExist<ValueType<T>>::value)
				{
					IterateOver::set<std::string>(n, MemberString<ValueType<T>>::to_string()(v));
				}
				else
				{
					Object<ValueType<T>>::iterate_over(v, n);
				}
			}
		}

		IterateOver::end_struct();
	}

	static bool release(T&)
	{
		if (!used)
		{
			return true;
		}
		else
		{
			if constexpr (is_complex_v<ValueType<T>>)
			{
				if (Object<ValueType<T>>::release(get_last_inserted()))
				{
					used = false;
				}

				return false;
			}
		}

		return false;
	}

	static void reset()
	{
		used = false;
	}

	static void set_bool(T& o, const std::string& name, bool value)
	{
		if (!used)
		{
			if constexpr (std::is_same_v<ValueType<T>, bool>)
			{
				insert(o, name, value);
			}
			else
			{
				throw StructMappingException(
					"bad type (bool) '"
						+ (value ? std::string("true") : std::string("false"))
						+ "' at name '"
						+ name
						+ "' in map_like");
			}
		}
		else
		{
			if constexpr (is_complex_v<ValueType<T>>)
			{
				Object<ValueType<T>>::set_bool(get_last_inserted(), name, value);
			}
		}
	}

	static void set_floating_point(T& o, const std::string& name, double value)
	{
		if (!used)
		{
			if constexpr (std::is_floating_point_v<ValueType<T>>)
			{
				if (!detail::in_limits<ValueType<T>>(value))
				{
					throw StructMappingException(
						"bad value '"
							+ std::to_string(value)
							+ "' at name '"
							+ name
							+ "' in map_like is out of limits of type ["
							+	std::to_string(std::numeric_limits<ValueType<T>>::lowest())
							+	" : "
							+	std::to_string(std::numeric_limits<ValueType<T>>::max())
							+ "]");
				}

				insert(o, name, static_cast<ValueType<T>>(value));
			}
			else
			{
				throw StructMappingException(
					"bad type (floating point) '" + std::to_string(value) + "' at name '" + name + "' in map_like");
			}
		}
		else
		{
			if constexpr (is_complex_v<ValueType<T>>)
			{
				Object<ValueType<T>>::set_floating_point(get_last_inserted(), name, value);
			}
		}
	}

	static void set_integral(T& o, const std::string& name, long long value)
	{
		if (!used)
		{
			if constexpr (detail::is_integer_or_floating_point_v<ValueType<T>>)
			{
				if (!detail::in_limits<ValueType<T>>(value))
				{
					throw StructMappingException(
						"bad value '"
							+ std::to_string(value)
							+ "' at name '"
							+ name
							+ "' in map_like is out of limits of type ["
							+	std::to_string(std::numeric_limits<ValueType<T>>::lowest())
							+	" : "
							+	std::to_string(std::numeric_limits<ValueType<T>>::max())
							+ "]");
				}

				insert(o, name, static_cast<ValueType<T>>(value));
			}
			else
			{
				throw StructMappingException(
					"bad type (integer) '" + std::to_string(value) + "' at name '" + name + "' in map_like");
			}
		}
		else
		{
			if constexpr (is_complex_v<ValueType<T>>)
			{
				Object<ValueType<T>>::set_integral(get_last_inserted(), name, value);
			}
		}
	}

	static void set_string(T& o, const std::string& name, const std::string& value)
	{
		if (!used)
		{
			if constexpr (std::is_same_v<ValueType<T>, std::string>)
			{
				insert(o, name, value);
			}
			else if constexpr (std::is_enum_v<ValueType<T>>)
			{
 				insert(o, name, MemberString<ValueType<T>>::from_string()(value));
			}
			else
			{
				if (is_complex_v<ValueType<T>>&& IsMemberStringExist<ValueType<T>>::value)
				{
					insert(o, name, MemberString<ValueType<T>>::from_string()(value));
				}
				else
				{
					throw StructMappingException("bad type (string) '" + value + "' at name '" + name + "' in map_like");
				}
			}
		}
		else
		{
			if constexpr (is_complex_v<ValueType<T>>)
			{
				Object<ValueType<T>>::set_string(get_last_inserted(), name, value);
			}
		}
	}

	static void use(T& o, const std::string& name)
	{
		if constexpr (is_complex_v<ValueType<T>>)
		{
			if (!used)
			{
				used = true;
				last_inserted = insert(o, name, ValueType<T>{});
				Object<ValueType<T>>::init();
			}
			else
			{
				Object<ValueType<T>>::use(get_last_inserted(), name);
			}
		}
	}

private:
	static inline Iterator last_inserted;
	static inline bool used = false;

	static auto& get_last_inserted()
	{
		return last_inserted->second;
	}

	template<typename V>
	static Iterator insert(T& o, const std::string& name, const V& value)
	{
		if constexpr (
			std::is_same_v<
				decltype(std::declval<T>().insert(typename T::value_type())),
				std::pair<Iterator, bool>>)
		{
			auto [it, ok] = o.insert(std::make_pair(name, value));
			return it;
		}
		else if constexpr (std::is_same_v<decltype(std::declval<T>().insert(typename T::value_type())), Iterator>)
		{
			return o.insert(std::make_pair(name, value));
		}
	}
};

} // struct_mapping::detail

#endif
