#ifndef STRUCT_MAPPING_MEMBER_STRING_H
#define STRUCT_MAPPING_MEMBER_STRING_H

#include <functional>
#include <string>

#include "exception.h"

namespace struct_mapping
{

template<
	typename T,
	bool exist = false>
struct IsMemberStringExist
{
	static inline bool value = exist;
};

template<typename T>
class MemberString
{
public:
	using FromString = T (const std::string&);
	using ToString = std::string (T);

	template<
		typename From,
		typename To>
	static void set(From function_from_string_, To function_to_string_)
	{
		IsMemberStringExist<T>::value = true;
		function_from_string = std::function<FromString>(function_from_string_);
		function_to_string = std::function<ToString>(function_to_string_);
	}

	static auto& from_string(const std::string& name = "")
	{
		if (!function_from_string)
		{
			throw StructMappingException("MemberString not set for member: " + name);
		}

		return function_from_string;
	}

	static auto& to_string(const std::string& name = "")
	{
		if (!function_to_string)
		{
			throw StructMappingException("MemberString not set for member: " + name);
		}

		return function_to_string;
	}

private:
	static inline std::function<FromString> function_from_string;
	static inline std::function<ToString> function_to_string;
};

} // struct_mapping

#endif
