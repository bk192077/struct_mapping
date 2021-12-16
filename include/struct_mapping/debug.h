#pragma once

#include "utility.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace struct_mapping
{

#ifdef DEBUG_OUTPUT
	constexpr bool debug = true;
#else
	constexpr bool debug = false;
#endif

namespace nsdebug
{

template<
	typename,
	typename = std::void_t<>>
struct has_TYPE_NAME : std::false_type{};

template<typename T>
struct has_TYPE_NAME<T, std::void_t<decltype(T::TYPE_NAME)>> : std::true_type{};

template<typename T>
constexpr bool has_TYPE_NAME_v = has_TYPE_NAME<T>::value;

template<typename T>
struct GetTypeName
{
	static std::string get()
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			return "bool";
		}
		else if constexpr (std::is_same_v<T, char>)
		{
			return "char";
		}
		else if constexpr (std::is_same_v<T, unsigned char>)
		{
			return "unsigned char";
		}
		else if constexpr (std::is_same_v<T, short>)
		{
			return "short";
		}
		else if constexpr (std::is_same_v<T, unsigned short>)
		{
			return "unsigned short";
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			return "int";
		}
		else if constexpr (std::is_same_v<T, unsigned int>)
		{
			return "unsigned int";
		}
		else if constexpr (std::is_same_v<T, long>)
		{
			return "long";
		}
		else if constexpr (std::is_same_v<T, long long>)
		{
			return "long long";
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			return "float";
		}
		else if constexpr (std::is_same_v<T, double>)
		{
			return "double";
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			return "std::string";
		}
		else if constexpr (std::is_class_v<T>)
		{
			if constexpr (has_TYPE_NAME_v<T>)
			{
				return T::TYPE_NAME;
			}

			return "UNKNOWN_CLASS";
		}
		else
		{
			return "UNKNOWN";
		}
	}

	static std::string get(bool& is_first)
	{
		if (is_first)
		{
			is_first = false;
			return get();
		}

		return ", " + get();
	}
};

template<typename T>
struct GetTypeName<std::optional<T>>
{
	static std::string get()
	{
		return "std::optional<" + GetTypeName<detail::remove_optional_t<T>>::get() + ">";
	}

	static std::string get(bool& is_first)
	{
		if (is_first)
		{
			is_first = false;
			return get();
		}

		return ", " + get();
	}
};

template<typename T>
struct GetTypeName<std::vector<T>>
{
	static std::string get()
	{
		return "std::vector<" + GetTypeName<T>::get() + ">";
	}

	static std::string get(bool& is_first)
	{
		if (is_first)
		{
			is_first = false;
			return get();
		}

		return ", " + get();
	}
};

template<
	typename ... ClassTypes,
	typename ... FunctionTypes>
void print_info(
	const std::string& class_name,
	const std::string& function_name,
	const std::string& argument_name = "",
	FunctionTypes ...)
{
	bool is_first = true;

	std::cout << "D: " << class_name << "<";
	(std::cout << ... << GetTypeName<ClassTypes>::get(is_first));
	std::cout << ">::" << function_name << "<";

	is_first = true;
	if constexpr (sizeof...(FunctionTypes) != 0)
	{
		(std::cout << ... <<  GetTypeName<FunctionTypes>::get(is_first));
	}
	std::cout << ">(" << argument_name << ")" << std::endl;
}

} // nsdebug

} // struct_mapping