#ifndef STRUCT_MAPPING_OPTIONS_OPTION_REQUIRED_H
#define STRUCT_MAPPING_OPTIONS_OPTION_REQUIRED_H

#include <string>

namespace struct_mapping
{

template<typename T = void>
class Required
{
public:
	template<typename M>
	void check_option() const {}

	static void check_result(bool changed, const std::string& name)
	{
		if (!changed)
		{
			throw StructMappingException("no value has been set for the required member '" + name + "'");
		}
	}
};

} // struct_mapping

#endif
