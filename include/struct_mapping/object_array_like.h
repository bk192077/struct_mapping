#ifndef STRUCT_MAPPING_OBJECT_ARRAY_LIKE_H
#define STRUCT_MAPPING_OBJECT_ARRAY_LIKE_H

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
class Object<T, true, false>
{
public:
	template<typename V>
	using ValueType = typename V::value_type;

	using LastInserted = std::conditional_t<has_key_type_v<T>, ValueType<T>, typename T::iterator>;

	static void check_not_empty(T& o, const std::string& name)
	{
		NotEmpty<>::check_result(o, name);
	}

	static void init() {}

	static void iterate_over(T& o, const std::string& name)
	{
		IterateOver::start_array(name);
		
		for (auto& v : o)
		{
			if constexpr (std::is_same_v<ValueType<T>, bool>)
			{
				IterateOver::set<bool>("", v);
			}
			else if constexpr (std::is_integral_v<ValueType<T>>)
			{
				IterateOver::set<long long>("", v);
			}
			else if constexpr (std::is_floating_point_v<ValueType<T>>)
			{
				IterateOver::set<double>("", v);
			}
			else if constexpr (std::is_same_v<ValueType<T>, std::string>)
			{
				IterateOver::set<std::string>("", v);
			}
			else if constexpr (std::is_enum_v<ValueType<T>>)
			{
				IterateOver::set<std::string>("", MemberString<ValueType<T>>::to_string()(v));
			}
			else
			{
				if (IsMemberStringExist<ValueType<T>>::value)
				{
					IterateOver::set<std::string>("", MemberString<ValueType<T>>::to_string()(v));
				}
				else
				{
					if constexpr (has_key_type_v<T>)
					{
						Object<ValueType<T>>::iterate_over(const_cast<ValueType<T>&>(v), "");
					}
					else
					{
						Object<ValueType<T>>::iterate_over(v, "");
					}
				}
			}
		}

		IterateOver::end_array();
	}

	static bool release(T& o)
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
					if constexpr (has_key_type_v<T>)
					{
						insert(o, std::move(last_inserted));
					}
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
				insert(o, value);
			}
			else
			{
				throw StructMappingException(
					"bad type (bool) '"
						+ (value ? std::string("true") : std::string("false"))
						+ "' in array_like at index "
						+ std::to_string(o.size()));
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
							+ "' in array_like at index "
							+ std::to_string(o.size())
							+ " is out of limits of type ["
							+	std::to_string(std::numeric_limits<ValueType<T>>::lowest())
							+	" : "
							+	std::to_string(std::numeric_limits<ValueType<T>>::max())
							+ "]");
				}

				insert(o, static_cast<ValueType<T>>(value));
			}
			else
			{
				throw StructMappingException(
					"bad type (floating point) '"
						+ std::to_string(value)
						+ "' in array_like at index "
						+ std::to_string(o.size()));
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
							+ "' in array_like at index "
							+ std::to_string(o.size())
							+ " is out of limits of type ["
							+	std::to_string(std::numeric_limits<ValueType<T>>::lowest())
							+	" : "
							+ std::to_string(std::numeric_limits<ValueType<T>>::max())
							+ "]");
				}

				insert(o, static_cast<ValueType<T>>(value));
			}
			else
			{
				throw StructMappingException(
					"bad type (integer) '" + std::to_string(value) + "' in array_like at index " + std::to_string(o.size()));
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
				insert(o, value);
			}
			else if constexpr (std::is_enum_v<ValueType<T>>)
			{
 				insert(o, MemberString<ValueType<T>>::from_string()(value));
			}
			else
			{
				if (is_complex_v<ValueType<T>>&& IsMemberStringExist<ValueType<T>>::value)
				{
					insert(o, MemberString<ValueType<T>>::from_string()(value));
				}
				else
				{
					throw StructMappingException(
						"bad type (string) '" + value + "' in array_like at index " + std::to_string(o.size()));
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

				if constexpr (has_key_type_v<T>)
				{
					last_inserted = ValueType<T>{};
				}
				else
				{
					last_inserted = o.insert(o.end(), ValueType<T>{});
				}

				Object<ValueType<T>>::init();
			}
			else
			{
				Object<ValueType<T>>::use(get_last_inserted(), name);
			}
		}
	}

private:
	static inline LastInserted last_inserted;
	static inline bool used = false;

	static auto& get_last_inserted()
	{
		if constexpr (has_key_type_v<T>)
		{
			return last_inserted;
		}
		else
		{
			return *last_inserted;
		}
	}

	template<typename V>
	static void insert(T& o, const V& value)
	{
		if constexpr (has_key_type_v<T>)
		{
			o.insert(value);
		}
		else
		{
			o.insert(o.end(), value);
		}
	}
};

} // struct_mapping::detail

#endif
