#pragma once

#include <string>

namespace struct_mapping
{

template<typename T = void>
class NotEmpty
{
public:
	template<typename M>
	void check_option() const
	{
		static_assert(
			std::is_same_v<std::string, detail::remove_optional_t<M>>
				|| detail::is_container_like_v<detail::remove_optional_t<M>>,
			"bad option (NotEmpty): option can only be applied to types: string, sequence container");
	}

	template<typename V>
	static void check_result(const V& value, const std::string& name)
	{
		if constexpr (std::is_same_v<std::string, detail::remove_optional_t<V>>
			|| detail::is_container_like_v<detail::remove_optional_t<V>>)
		{
			if constexpr (detail::is_optional_v<V>)
			{
				if (!value || !value.value().empty())
				{
					return;
				}
			}
			else
			{
				if (!value.empty())
				{
					return;
				}
			}
		}

		throw StructMappingException("value for '" + name + "' cannot be empty");
	}
};

} // struct_mapping