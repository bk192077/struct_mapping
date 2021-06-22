#ifndef STRUCT_MAPPING_UTILITY_H
#define STRUCT_MAPPING_UTILITY_H

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

namespace struct_mapping::detail
{

template<typename T>
static constexpr bool is_integer_v = !std::is_same_v<T, bool>&& std::is_integral_v<T>;

template<typename T>
static constexpr bool is_integer_or_floating_point_v = !std::is_same_v<T, bool>
	&& (std::is_integral_v<T> || std::is_floating_point_v<T>);

template<typename T>
static constexpr bool is_integral_or_floating_point_or_string_v = std::is_integral_v<T>
	|| std::is_floating_point_v<T>
	|| std::is_same_v<T, std::string>;

template<typename T>
static constexpr bool is_complex_v = !is_integral_or_floating_point_or_string_v<T>&& !std::is_enum_v<T>;


template<
	typename,
	typename = std::void_t<>>
struct has_mapped_type : std::false_type{};

template<typename T>
struct has_mapped_type<T, std::void_t<typename T::mapped_type>> : std::true_type{};

template<typename T>
constexpr bool has_mapped_type_v = has_mapped_type<T>::value;


template<
	typename,
	typename = std::void_t<>>
struct has_key_type : std::false_type{};

template<typename T>
struct has_key_type<T, std::void_t<typename T::key_type>> : std::true_type{};

template<typename T>
constexpr bool has_key_type_v = has_key_type<T>::value;


template<
	typename,
	typename = std::void_t<>>
struct is_container_like : std::false_type{};

template<>
struct is_container_like<std::string> : std::false_type{};

template<typename T>
struct is_container_like<
	T,
	std::void_t<
		decltype(std::declval<T>().insert(typename T::iterator(), typename T::value_type()))>> : std::true_type{};

template<typename T>
constexpr bool is_container_like_v = is_container_like<T>::value;


template<typename T>
constexpr bool is_array_like_v = is_container_like_v<T>&& !has_mapped_type_v<T>;

template<typename T>
constexpr bool is_map_like_v = is_container_like_v<T>&& has_mapped_type_v<T>;


using Index = unsigned int;
constexpr Index NO_INDEX = std::numeric_limits<Index>::max();

template<
	typename T,
	typename V>
using MemberPtr = V T::*;

template<typename T>
struct TypeHolder {};

template<
	typename U,
	typename V>
inline bool in_limits(V value)
{
	if constexpr (std::is_integral_v<U>)
	{
		return (value >= std::numeric_limits<U>::lowest()&& value <= std::numeric_limits<U>::max());
	}
	else
	{
		return static_cast<double>(value) >= static_cast<double>(std::numeric_limits<U>::lowest())
			&& static_cast<double>(value) <= static_cast<double>(std::numeric_limits<U>::max());
	}
}

} // struct_mapping::detail

#endif
