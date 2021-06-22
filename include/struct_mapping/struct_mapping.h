#ifndef STRUCT_MAPPING_STRUCT_MAPPING_H
#define STRUCT_MAPPING_STRUCT_MAPPING_H

#include <string>
#include <utility>

#include "exception.h"
#include "object.h"
#include "member_string.h"
#include "mapper.h"
#include "options/option_bounds.h"
#include "options/option_default.h"
#include "options/option_not_empty.h"
#include "options/option_required.h"

namespace struct_mapping
{

template<
	typename T,
	typename V,
	typename ... U,
	template<typename> typename ... Options>
inline void reg(V T::* ptr, const std::string& name, Options<U>&& ... options)
{
	detail::Object<T>::reg(ptr, name, std::forward<Options<U>>(options)...);
}

} // struct_mapping

#define BEGIN_STRUCT(STRUCT_NAME) struct STRUCT_NAME {using Self_Q5w6E7r8 = STRUCT_NAME;

#define MEMBER(TYPE, NAME) TYPE NAME = [] {\
	struct_mapping::reg(&Self_Q5w6E7r8::NAME, #NAME);\
	using MEMBER_TYPE = TYPE;\
	return MEMBER_TYPE{};\
} ();

#define MEMBER_OPTIONS(TYPE, NAME, ...) TYPE NAME = [] {\
	struct_mapping::reg(&Self_Q5w6E7r8::NAME, #NAME, __VA_ARGS__);\
	using MEMBER_TYPE = TYPE;\
	return MEMBER_TYPE{};\
} ();

#define END_STRUCT };

#endif
