#pragma once

#include <string>

namespace struct_mapping
{

template<typename T = void>
class Required
{
public:
	template<typename M>
	void check_option() const 
	{
		static_assert(!detail::is_optional_v<M>,
			"bad option (Required): the option cannot be set for an optional type");
	}

	static void check_result(bool changed, const std::string& name)
	{
		if (!changed)
		{
			throw StructMappingException("no value has been set for the required member '" + name + "'");
		}
	}
};

} // struct_mapping