#pragma once

#include "../utility.h"
#include "../exception.h"

#include <limits>
#include <string>

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
			!std::is_same_v<detail::remove_optional_t<M>, bool> || std::is_same_v<T, bool>,
			"bad option (Default): type error, expected bool");

		static_assert(
			!detail::is_integer_v<detail::remove_optional_t<M>> || detail::is_integer_v<T>,
			"bad option (Default): type error, expected integer");

		static_assert(
			!std::is_floating_point_v<detail::remove_optional_t<M>> || detail::is_integer_or_floating_point_v<T>,
			"bad option (Default): type error, expected integer or floating point");

		static_assert(
			!std::is_same_v<detail::remove_optional_t<M>, std::string>
				|| std::is_same_v<T, std::string>
				|| std::is_same_v<T, const char*>,
			"bad option (Default): type error, expected string");

		static_assert(
			!std::is_enum_v<detail::remove_optional_t<M>>
				|| std::is_enum_v<T>, "bad option (Default): type error, expected enumeration");

		static_assert(
			detail::is_integral_or_floating_point_or_string_v<detail::remove_optional_t<M>>
				|| std::is_same_v<detail::remove_optional_t<M>, T>
				|| (std::is_class_v<detail::remove_optional_t<M>>
				&& (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>)),
			"bad option (Default): type error");

		if constexpr (detail::is_integer_or_floating_point_v<detail::remove_optional_t<M>>)
		{
			if (!in_limits<detail::remove_optional_t<M>>())
			{
				throw StructMappingException(
					"bad option (Default) for '"
						+ name
						+ "': "
						+ std::to_string(value)
						+ " is out of limits of type ["
						+ std::to_string(std::numeric_limits<detail::remove_optional_t<M>>::lowest())
						+	" : "
						+	std::to_string(std::numeric_limits<detail::remove_optional_t<M>>::max()) + "]");
			}
		}

		if constexpr (std::is_class_v<detail::remove_optional_t<M>>
			&& !std::is_same_v<detail::remove_optional_t<M>, std::string>
			&& (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>))
		{
			if (!IsMemberStringExist<detail::remove_optional_t<M>>::value)
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

private:
	T value;
};

} // struct_mapping