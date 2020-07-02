#ifndef STRUCT_MAPPING_OPTIONS_OPTION_NOT_EMPTY_H
#define STRUCT_MAPPING_OPTIONS_OPTION_NOT_EMPTY_H

#include <string>

namespace struct_mapping {

template<typename T = void>
class NotEmpty {
public:
	template<typename M>
	void check_option() const {
		static_assert(std::is_same_v<std::string, M>, "bad option (NotEmpty): option can only be applied to types: string");
	}

	template<typename V>
	static void check_result(V value, const std::string & name) {
		if constexpr (std::is_same_v<std::string, V>) {
			if (value.empty()) throw StructMappingException("value for '" + name + "' cannot be empty");
		}
	}
};

}

#endif
