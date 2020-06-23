#ifndef STRUCT_MAPPING_STRUCT_MAPPING_H
#define STRUCT_MAPPING_STRUCT_MAPPING_H

#include <string>

#include "exception.h"
#include "f_struct.h"
#include "mapper.h"

namespace struct_mapping {

template<typename T, typename V>
inline void reg(V T::* ptr, std::string const & name) {
	detail::F<T>::reg(ptr, name);
}

}

#define BEGIN_STRUCT(STRUCT_NAME) struct STRUCT_NAME {using Self_Q5w6E7r8 = STRUCT_NAME;

#define MEMBER(TYPE, NAME) TYPE NAME = [] {struct_mapping::reg(&Self_Q5w6E7r8::NAME, #NAME); using MEMBER_TYPE = TYPE; return MEMBER_TYPE{};} ();

#define END_STRUCT };

#endif
