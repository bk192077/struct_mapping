#pragma once

#include "iterate_over.h"
#include "member_string.h"
#include "options/option_bounds.h"
#include "options/option_default.h"
#include "options/option_not_empty.h"
#include "options/option_required.h"
#include "utility.h"

#include <functional>
#include <string>
#include <type_traits>
#include <utility>

namespace struct_mapping::detail
{

template<
	typename T,
	typename ObjectType>
class Member
{
public:
	enum class Type
	{
		Bool,
		Char,
		UnsignedChar,
		Short,
		UnsignedShort,
		Int,
		UnsignedInt,
		Long,
		LongLong,
		Float,
		Double,
		String,
		Enum,
		Complex,
	};

public:
	template<
		typename V,
		typename ... U,
		template<typename> typename ... Options>
	Member(const std::string& name_, MemberPtr<T, V> ptr_, Options<U>&& ... options)
		:	name(name_), type(get_member_type<remove_optional_t<V>>())
	{
		is_optional = is_optional_v<V>;
		ptr_index = static_cast<Index>(ObjectType::template members_ptr<V>.size());

		if constexpr (get_member_type<remove_optional_t<V>>() == Type::Complex)
		{
			if (!IsMemberStringExist<remove_optional_t<V>>::value)
			{
				deep_index = ObjectType::functions.add(ptr_);
				(add_option<V>(std::forward<Options<U>>(options)), ...);
				return;
			}
		}

		deep_index = NO_INDEX;

		if (get_member_type<remove_optional_t<V>>() == Type::Enum
			|| (get_member_type<remove_optional_t<V>>() == Type::Complex
				&& IsMemberStringExist<remove_optional_t<V>>::value))
		{
			member_string_index = static_cast<Index>(ObjectType::member_string_from_string.size());

			ObjectType::member_string_from_string.push_back(
				[ptr_, name_] (T& o, const std::string& value_)
				{
						o.*ptr_ = MemberString<remove_optional_t<V>>::from_string(name_)(value_);
				});

			ObjectType::member_string_to_string.push_back(
				[ptr_, name_] (T& o) -> std::optional<std::string>
				{
					if constexpr (!is_optional_v<V>)
					{
						return MemberString<V>::to_string(name_)(o.*ptr_);
					}
					else
					{
						if ((o.*ptr_).has_value())
						{
							return MemberString<remove_optional_t<V>>::to_string(name_)((o.*ptr_).value());
						}
						else
						{
							return std::nullopt;
						}
					}
				});
		}

		(add_option<V>(std::forward<Options<U>>(options)), ...);
	}

	template<typename V>
	static constexpr auto get_member_type()
	{
		if constexpr (std::is_same_v<V, bool>) {return Type::Bool;}
		if constexpr (std::is_same_v<V, char>) {return Type::Char;}
		if constexpr (std::is_same_v<V, unsigned char>) {return Type::UnsignedChar;}
		if constexpr (std::is_same_v<V, short>) {return Type::Short;}
		if constexpr (std::is_same_v<V, unsigned short>) {return Type::UnsignedShort;}
		if constexpr (std::is_same_v<V, int>) {return Type::Int;}
		if constexpr (std::is_same_v<V, unsigned int>) {return Type::UnsignedInt;}
		if constexpr (std::is_same_v<V, long>) {return Type::Long;}
		if constexpr (std::is_same_v<V, long long>) {return Type::LongLong;}
		if constexpr (std::is_same_v<V, float>) {return Type::Float;}
		if constexpr (std::is_same_v<V, double>) {return Type::Double;}
		if constexpr (std::is_same_v<V, std::string>) {return Type::String;}
		if constexpr (std::is_enum_v<V>) {return Type::Enum;}
		
		return Type::Complex;
	}

	void init()
	{
		changed = false;
	}

	void iterate_over(T& o)
	{
		switch (type)
		{
		case Type::Bool:
			iterate_over_impl<bool, bool>(o);
			break;
		case Type::Char:
			iterate_over_impl<long long, char>(o);
			break;
		case Type::UnsignedChar:
			iterate_over_impl<long long, unsigned char>(o);
			break;
		case Type::Short:
			iterate_over_impl<long long, short>(o);
			break;
		case Type::UnsignedShort:
			iterate_over_impl<long long, unsigned short>(o);
			break;
		case Type::Int:
			iterate_over_impl<long long, int>(o);
			break;
		case Type::UnsignedInt:
			iterate_over_impl<long long, unsigned int>(o);
			break;
		case Type::Long:
			iterate_over_impl<long long, long>(o);
			break;
		case Type::LongLong:
			iterate_over_impl<long long, long long>(o);
			break;
		case Type::Float:
			iterate_over_impl<double, float>(o);
			break;
		case Type::Double:
			iterate_over_impl<double, double>(o);
			break;
		case Type::String:
			iterate_over_impl<std::string, std::string>(o);
			break;
		case Type::Enum:
			if (const auto& value_string = ObjectType::member_string_to_string[member_string_index](o); value_string)
			{
				IterateOver::set<std::string>(name, value_string.value());
			}
			else
			{
				IterateOver::set_null(name);
			}
			break;
		case Type::Complex:
			if (member_string_index != NO_INDEX)
			{
				if (const auto& value_string = ObjectType::member_string_to_string[member_string_index](o); value_string)
				{
					IterateOver::set<std::string>(name, value_string.value());
				}
				else
				{
					IterateOver::set_null(name);
				}
			}
			else
			{
				ObjectType::functions.iterate_over[deep_index](o, name);
			}
			break;
		}
	}

	void release(T& o)
	{
		process_required();
		process_default(o);
		process_not_empty(o);
		changed = false;
	}

public:
	Index bounds_index = NO_INDEX;
	bool changed = false;
	Index default_index = NO_INDEX;
	Index deep_index;
	bool is_optional;
	Index member_string_index = NO_INDEX;
	std::string name;
	Index ptr_index;
	bool option_not_empty = false;
	bool option_required = false;
	Type type;

private:
	template<
		typename V,
		typename U,
		template<typename> typename Op>
	void add_option(Op<U>&& op)
	{
		if constexpr (std::is_same_v<Bounds<U>, std::decay_t<Op<U>>>)
		{
			op.template check_option<V>(name);
			add_option_bounds<V>(op);
		}
		else if constexpr (std::is_same_v<Default<U>, std::decay_t<Op<U>>>)
		{
			op.template check_option<V>(name);
			add_option_default<V>(op);
		}
		else if constexpr (std::is_same_v<NotEmpty<U>, std::decay_t<Op<U>>>)
		{
			op.template check_option<V>();
			add_option_not_empty<V>();
		}
		else if constexpr (std::is_same_v<Required<U>, std::decay_t<Op<U>>>)
		{
			op.template check_option<V>();
			add_option_required<V>();
		}
	}

	template<
		typename V,
		typename U>
	void add_option_bounds(const Bounds<U>& op)
	{
		bounds_index = static_cast<Index>(ObjectType::template members_bounds<V>.size());
		ObjectType::template members_bounds<V>.push_back(op);
	}

	template<
		typename V,
		typename U>
	void add_option_default(const Default<U>& op)
	{
		if constexpr (std::is_same_v<remove_optional_t<V>, std::string> && std::is_same_v<U, const char*>)
		{
			if constexpr (is_optional_v<V>)
			{
				default_index = static_cast<Index>(ObjectType::template members_default<std::optional<std::string>>.size());
				ObjectType::template members_default<std::optional<std::string>>.push_back(op.get_value());
			}
			else
			{
				default_index = static_cast<Index>(ObjectType::template members_default<std::string>.size());
				ObjectType::template members_default<std::string>.push_back(op.get_value());
			}
		}
		else if constexpr (std::is_enum_v<remove_optional_t<V>>)
		{
			default_index = static_cast<Index>(ObjectType::template members_default<std::string>.size());
			ObjectType::template members_default<std::string>.push_back(
				MemberString<remove_optional_t<V>>::to_string(name)(op.get_value()));
		}
		else if constexpr (std::is_class_v<remove_optional_t<V>>
			&& (std::is_same_v<U, std::string> || std::is_same_v<U, const char*>))
		{
			if (member_string_index != NO_INDEX)
			{
				default_index = static_cast<Index>(ObjectType::template members_default<std::string>.size());
				ObjectType::template members_default<std::string>.push_back(op.get_value());
			}
		}
		else if constexpr (std::is_same_v<remove_optional_t<V>, U>
			|| (is_integer_or_floating_point_v<remove_optional_t<V>> && is_integer_or_floating_point_v<U>))
		{
			default_index = static_cast<Index>(ObjectType::template members_default<V>.size());
			ObjectType::template members_default<V>.push_back(static_cast<remove_optional_t<V>>(op.get_value()));
		}
	}

	template<typename V>
	void add_option_not_empty()
	{
		option_not_empty = true;
	}

	template<typename V>
	void add_option_required()
	{
		option_required = true;
	}

	template<
		typename ValueType,
		typename MemberType>
	void iterate_over_impl(T& o)
	{
		if (!is_optional)
		{
			IterateOver::set<ValueType>(name, o.*ObjectType::template members_ptr<MemberType>[ptr_index]);
		}
		else
		{
			if (const auto& member_value = o.*ObjectType::template members_ptr<std::optional<MemberType>>[ptr_index];
				member_value)
			{
				IterateOver::set<ValueType>(name, member_value.value());
			}
			else
			{
				IterateOver::set_null(name);
			}
		}
	}

	void process_default(T& o)
	{
		if (!changed)
		{
			switch (type)
			{
			case Type::Bool: set_default<bool>(o); break;
			case Type::Char: set_default<char>(o); break;
			case Type::UnsignedChar: set_default<unsigned char>(o); break;
			case Type::Short: set_default<short>(o); break;
			case Type::UnsignedShort: set_default<unsigned short>(o); break;
			case Type::Int: set_default<int>(o); break;
			case Type::UnsignedInt: set_default<unsigned int>(o); break;
			case Type::Long: set_default<long>(o); break;
			case Type::LongLong: set_default<long long>(o); break;
			case Type::Float: set_default<float>(o); break;
			case Type::Double: set_default<double>(o); break;
			case Type::String: set_default<std::string>(o); break;
			case Type::Enum:
				if (default_index != NO_INDEX)
				{
					ObjectType::member_string_from_string[member_string_index](
						o,
						ObjectType::template members_default<std::string>[default_index]);
				}
				break;
			case Type::Complex:
				if (default_index != NO_INDEX)
				{
					if (member_string_index != NO_INDEX)
					{
						ObjectType::member_string_from_string[member_string_index](
							o,
							ObjectType::template members_default<std::string>[default_index]);
					}
					else
					{
						ObjectType::functions.set_default[deep_index](o, default_index);
					}
				}
				break;
			}
		}
	}

	void process_not_empty(T& o)
	{
		if (option_not_empty)
		{
			switch (type)
			{
			case Type::String:
				if (is_optional)
				{
					NotEmpty<>::check_result(o.*ObjectType::template members_ptr<std::optional<std::string>>[ptr_index], name);
				}
				else
				{
					NotEmpty<>::check_result(o.*ObjectType::template members_ptr<std::string>[ptr_index], name);
				}
				break;
			case Type::Complex:
				ObjectType::functions.check_not_empty[deep_index](o, name);
				break;
			default:
				break;
			}
		} 
	}

	void process_required()
	{
		if (option_required)
		{
			Required<>::check_result(changed, name);
		}
	}

	template<typename V>
	void set_default(T& o)
	{
		if (default_index != NO_INDEX)
		{
			if (is_optional)
			{
				o.*ObjectType::template members_ptr<std::optional<V>>[ptr_index] = 
					ObjectType::template members_default<std::optional<V>>[default_index];
			}
			else
			{
				o.*ObjectType::template members_ptr<V>[ptr_index] = ObjectType::template members_default<V>[default_index];
			}
		}
	}
};

} // struct_mapping::detail