#ifndef STRUCT_MAPPING_OPTIONS_OPTION_DEFAULT_H
#define STRUCT_MAPPING_OPTIONS_OPTION_DEFAULT_H

#include <limits>
#include <string>

#include "../utility.h"
#include "../exception.h"

namespace struct_mapping
{

template<typename T>
class Default
{
public:
	Default(T value_)
		:	value(value_) {}

	template<typename M>
	void check_option(const std::string& name) const
	{
		static_assert(
			!std::is_same_v<M, bool> || std::is_same_v<T, bool>,
			"bad option (Default): type error, expected bool");
		static_assert(
			!detail::is_integer_v<M> || detail::is_integer_v<T>,
			"bad option (Default): type error, expected integer");
		static_assert(
			!std::is_floating_point_v<M> || detail::is_integer_or_floating_point_v<T>,
			"bad option (Default): type error, expected integer or floating point");
		static_assert(
			!std::is_same_v<M, std::string> || std::is_same_v<T, std::string> || std::is_same_v<T, const char*>,
			"bad option (Default): type error, expected string");
		static_assert(!std::is_enum_v<M> || std::is_enum_v<T>, "bad option (Default): type error, expected enumeration");
		static_assert(
			detail::is_integral_or_floating_point_or_string_v<M>
				|| std::is_same_v<M, T>
				|| (std::is_class_v<M>&& (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>)),
			"bad option (Default): type error");

		if constexpr (detail::is_integer_or_floating_point_v<M>)
		{
			if (!in_limits<M>())
			{
				throw StructMappingException(
					"bad option (Default) for '"
						+ name
						+ "': "
						+ std::to_string(value)
						+ " is out of limits of type ["
						+ std::to_string(std::numeric_limits<M>::lowest())
						+	" : "
						+	std::to_string(std::numeric_limits<M>::max()) + "]");
			}
		}

		if constexpr (std::is_class_v<M>
			&& !std::is_same_v<M, std::string>
			&& (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>))
		{
			if (!IsMemberStringExist<M>::value)
			{
				throw StructMappingException(
					"bad option (Default) for '"
						+ name
						+ "': function to convert from string value to type is undefined");
			}
		}
	}

	auto get_value() const
	{
		return value;
	}

private:
	T value;

	template<typename M>
	bool in_limits() const
	{
		if constexpr (detail::is_integer_v<M>)
		{
			return static_cast<long long>(value) >= static_cast<long long>(std::numeric_limits<M>::lowest())
				&& static_cast<long long>(value) <= static_cast<long long>(std::numeric_limits<M>::max());
		}
		else
		{
			return static_cast<double>(value) >= static_cast<double>(std::numeric_limits<M>::lowest())
				&& static_cast<double>(value) <= static_cast<double>(std::numeric_limits<M>::max());
		}
	}
};

} // struct_mapping

#endif
