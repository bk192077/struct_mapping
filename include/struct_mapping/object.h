#ifndef STRUCT_MAPPING_OBJECT_H
#define STRUCT_MAPPING_OBJECT_H

#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "functions.h"
#include "iterate_over.h"
#include "member.h"
#include "reset.h"
#include "utility.h"

namespace struct_mapping::detail
{

template<
	typename T,
	bool = is_array_like_v<T>,
	bool = is_map_like_v<T>>
class Object
{
public:
	using FunctionsType = Functions<T, Object>;
	using MemberType = Member<T, Object>;

	friend FunctionsType;
	friend MemberType;

	template<
		typename V,
		typename ... U,
		template<typename> typename ... Options>
	static void reg(MemberPtr<T, V> ptr, const std::string& name, Options<U>&& ... options)
	{
		if (members_name_index.find(name) == members_name_index.end())
		{
			reg_reset<V>();			

			members_name_index.emplace(name, static_cast<Index>(members.size()));
			MemberType member(name, ptr, std::forward<Options<U>>(options)...);

			members.push_back(std::move(member));
			members_ptr<V>.push_back(ptr);
		}
	}

	static void check_not_empty(T&, const std::string&) {}

	static void init()
	{
		for (auto& member : members)
		{
			member.init();
		}
	}

	static void iterate_over(T& o, const std::string& name)
	{
		IterateOver::start_struct(name);
		for (auto& member : members)
		{
			member.iterate_over(o);
		}

		IterateOver::end_struct();
	}

	static bool release(T& o)
	{
		if (member_deep_index == NO_INDEX)
		{
			for (auto& member : members)
			{
				member.release(o);
			}

			return true;
		}
		else if (functions.release[member_deep_index](o))
		{
			member_deep_index = NO_INDEX;
		}

		return false;
	}

	static void set_bool(T& o, const std::string& name, bool value)
	{
		if (member_deep_index == NO_INDEX)
		{
			if (auto it = members_name_index.find(name); it == members_name_index.end())
			{
				throw StructMappingException("bad member: " + name);
			}
			else if (members[it->second].type != MemberType::Type::Bool)
			{
				throw StructMappingException("bad type (bool) for member: " + name);
			}
			else
			{
				set<bool>(o, value, it->second);
			}
		}
		else
		{
			functions.set_bool[member_deep_index](o, name, value);
		}
	}

	static void set_floating_point(T& o, const std::string& name, double value)
	{
		if (member_deep_index == NO_INDEX)
		{
			if (auto it = members_name_index.find(name); it == members_name_index.end())
			{
				throw StructMappingException("bad member: " + name);
			}
			else
			{
				switch (members[it->second].type)
				{
				case MemberType::Type::Float:
					set<float>(o, value, it->second);
					break;
				case MemberType::Type::Double:
					set<double>(o, value, it->second);
					break;
				default:
					throw StructMappingException("bad set type (floating point) for member: " + name);
				}
			}
		}
		else
		{
			functions.set_floating_point[member_deep_index](o, name, value);
		}
	}

	static void set_integral(T& o, const std::string& name, long long value)
	{
		if (member_deep_index == NO_INDEX)
		{
			if (auto it = members_name_index.find(name); it == members_name_index.end())
			{
				throw StructMappingException("bad member: " + name);
			}
			else
			{
				switch (members[it->second].type)
				{
				case MemberType::Type::Char:
					set<char>(o, value, it->second);
					break;
				case MemberType::Type::UnsignedChar:
					set<unsigned char>(o, value, it->second);
					break;
				case MemberType::Type::Short:
					set<short>(o, value, it->second);
					break;
				case MemberType::Type::UnsignedShort:
					set<unsigned short>(o, value, it->second);
					break;
				case MemberType::Type::Int:
					set<int>(o, value, it->second);
					break;
				case MemberType::Type::UnsignedInt:
					set<unsigned int>(o, value, it->second);
					break;
				case MemberType::Type::Long:
					set<long>(o, value, it->second);
					break;
				case MemberType::Type::LongLong:
					set<long long>(o, value, it->second);
					break;
				case MemberType::Type::Float:
					set<float>(o, value, it->second);
					break;
				case MemberType::Type::Double:
					set<double>(o, value, it->second);
					break;
				default:
					throw StructMappingException("bad type (integral) for member: " + name);
				}
			}
		}
		else
		{
			functions.set_integral[member_deep_index](o, name, value);
		}
	}

	static void set_string(T& o, const std::string& name, const std::string& value)
	{
		if (member_deep_index == NO_INDEX)
		{
			if (auto it = members_name_index.find(name); it == members_name_index.end())
			{
				throw StructMappingException("bad member: " + name);
			}
			else if (members[it->second].type == MemberType::Type::Enum
				|| (members[it->second].type == MemberType::Type::Complex
						&& members[it->second].member_string_index != NO_INDEX))
			{
				members[it->second].changed = true;
				member_string_from_string[members[it->second].member_string_index](o, value);
			}
			else if (members[it->second].type != MemberType::Type::String)
			{
				throw StructMappingException("bad type (string) for member: " + name);
			}
			else
			{
				set<std::string>(o, value, it->second);
			}
		}
		else
		{
			functions.set_string[member_deep_index](o, name, value);
		}
	}

	static void use(T& o, const std::string& name)
	{
		if (member_deep_index == NO_INDEX)
		{
			if (auto it = members_name_index.find(name); it == members_name_index.end())
			{
				throw StructMappingException("bad member: " + name);
			}
			else
			{
				member_deep_index = members[it->second].deep_index;
				functions.init[member_deep_index]();
				members[it->second].changed = true;
			}
		}
		else
		{
			functions.use[member_deep_index](o, name);
		}
	}

private:
	static inline FunctionsType functions;

	static inline std::vector<std::function<void(T&, const std::string&)>> member_string_from_string{};
	static inline std::vector<std::function<std::string (T&)>> member_string_to_string{};
	static inline Index member_deep_index = NO_INDEX;
	static inline std::vector<MemberType> members;
	
	template<typename V>
	static inline std::vector<std::function<void(V, const std::string&)>> members_bounds{};
	
	template<typename V>
	static inline std::vector<V> members_default{};
	
	static inline std::unordered_map<typename MemberType::Name, Index> members_name_index;
	
	template<typename V>
	static inline std::vector<MemberPtr<T, V>> members_ptr{};

	template<typename V>
	static void reg_reset()
	{
		Reset::reg(reset);
		if constexpr (is_array_like_v<V> || is_map_like_v<V>)
		{
			reg_reset_array_map_like<V>();
		}
	}

	template<typename V>
	static void reg_reset_array_map_like()
	{
		Reset::reg(Object<V>::reset);
		if constexpr (is_array_like_v<typename Object<V>::template ValueType<V>>
			|| is_map_like_v<typename Object<V>::template ValueType<V>>)
		{
			reg_reset_array_map_like<typename Object<V>::template ValueType<V>>();
		}
	}

	static void reset()
	{
		member_deep_index = NO_INDEX;
	}

	template<
		typename U,
		typename V>
	static void set(T& o, V value, unsigned int index)
	{
		if constexpr (is_integer_or_floating_point_v<U>)
		{
			if (!in_limits<U>(value))
			{
				throw StructMappingException(
					"bad value for '"
						+ members[index].name
						+ "': "
						+ std::to_string(value)
						+ " is out of limits of type ["
						+	std::to_string(std::numeric_limits<U>::lowest())
						+ " : "
						+	std::to_string(std::numeric_limits<U>::max())
						+ "]");
			}
		}

		if (members[index].bounds_index != NO_INDEX)
		{
			members_bounds<U>[members[index].bounds_index](static_cast<U>(value), members[index].name);
		}

		members[index].changed = true;

		o.*members_ptr<U>[members[index].ptr_index] = static_cast<U>(value);
	}
};

} // struct_mapping::detail

#endif
