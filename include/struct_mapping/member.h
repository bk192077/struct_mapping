#ifndef STRUCT_MAPPING_MEMBER_H
#define STRUCT_MAPPING_MEMBER_H

#include <functional>
#include <string>
#include <type_traits>
#include <utility>

#include "iterate_over.h"
#include "member_string.h"
#include "options/option_bounds.h"
#include "options/option_default.h"
#include "options/option_not_empty.h"
#include "options/option_required.h"
#include "utility.h"

namespace struct_mapping::detail
{

template<
	typename T,
	typename ObjectType>
class Member
{
public:
	using Name = std::string;

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

	template<
		typename V,
		typename ... U,
		template<typename> typename ... Options>
	Member(Name name_, MemberPtr<T, V> ptr_, Options<U>&& ... options)
		:	name(name_), type(get_member_type<V>())
	{
		ptr_index = static_cast<Index>(ObjectType::template members_ptr<V>.size());

		if constexpr (get_member_type<V>() == Type::Complex)
		{
			if (!IsMemberStringExist<V>::value)
			{
				deep_index = ObjectType::functions.add(ptr_);
				(add_option<V>(std::forward<Options<U>>(options)), ...);
				return;
			}
		}

		deep_index = NO_INDEX;

		if (get_member_type<V>() == Type::Enum
			|| (get_member_type<V>() == Type::Complex && IsMemberStringExist<V>::value))
		{
			member_string_index = static_cast<Index>(ObjectType::member_string_from_string.size());
			ObjectType::member_string_from_string.push_back(
				[ptr_, name_] (T& o, const std::string& value_)
				{
					o.*ptr_ = MemberString<V>::from_string(name_)(value_);
				});
			ObjectType::member_string_to_string.push_back(
				[ptr_, name_] (T& o)
				{
					return MemberString<V>::to_string(name_)(o.*ptr_);
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
			IterateOver::set<bool>(name, o.*ObjectType::template members_ptr<bool>[ptr_index]);
			break;
		case Type::Char:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<char>[ptr_index]);
			break;
		case Type::UnsignedChar:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<unsigned char>[ptr_index]);
			break;
		case Type::Short:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<short>[ptr_index]);
			break;
		case Type::UnsignedShort:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<unsigned short>[ptr_index]);
			break;
		case Type::Int:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<int>[ptr_index]);
			break;
		case Type::UnsignedInt:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<unsigned int>[ptr_index]);
			break;
		case Type::Long:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<long>[ptr_index]);
			break;
		case Type::LongLong:
			IterateOver::set<long long>(name, o.*ObjectType::template members_ptr<long long>[ptr_index]);
			break;
		case Type::Float:
			IterateOver::set<double>(name, o.*ObjectType::template members_ptr<float>[ptr_index]);
			break;
		case Type::Double:
			IterateOver::set<double>(name, o.*ObjectType::template members_ptr<double>[ptr_index]);
			break;
		case Type::String:
			IterateOver::set<std::string>(name, o.*ObjectType::template members_ptr<std::string>[ptr_index]);
			break;
		case Type::Enum:
			IterateOver::set<std::string>(name, ObjectType::member_string_to_string[member_string_index](o));
			break;
		case Type::Complex:
			if (member_string_index != NO_INDEX)
			{
				IterateOver::set<std::string>(name, ObjectType::member_string_to_string[member_string_index](o));
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

	Index bounds_index = NO_INDEX;
	bool changed = false;
	Index default_index = NO_INDEX;
	Index deep_index;
	Index member_string_index = NO_INDEX;
	Name name;
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
			add_option_required<V>();
		}
	}

	template<
		typename V,
		typename U>
	void add_option_bounds(Bounds<U>& op)
	{
		bounds_index = static_cast<Index>(ObjectType::template members_bounds<V>.size());
		ObjectType::template members_bounds<V>.push_back(op);
	}

	template<
		typename V,
		typename U>
	void add_option_default(Default<U>& op){
		if constexpr (std::is_same_v<V, std::string>&& std::is_same_v<U, const char*>)
		{
			default_index = static_cast<Index>(ObjectType::template members_default<std::string>.size());
			ObjectType::template members_default<std::string>.push_back(op.get_value());
		}
		else if constexpr (std::is_enum_v<V>)
		{
			default_index = static_cast<Index>(ObjectType::template members_default<std::string>.size());
			ObjectType::template members_default<std::string>.push_back(MemberString<V>::to_string(name)(op.get_value()));
		}
		else if constexpr (std::is_class_v<V>&& (std::is_same_v<U, std::string> || std::is_same_v<U, const char*>))
		{
			if (member_string_index != NO_INDEX)
			{
				default_index = static_cast<Index>(ObjectType::template members_default<std::string>.size());
				ObjectType::template members_default<std::string>.push_back(op.get_value());
			}
		}
		else if constexpr (std::is_same_v<V, U> || (is_integer_or_floating_point_v<V>&& is_integer_or_floating_point_v<U>))
		{
			default_index = static_cast<Index>(ObjectType::template members_default<V>.size());
			ObjectType::template members_default<V>.push_back(static_cast<V>(op.get_value()));
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
				NotEmpty<>::check_result(o.*ObjectType::template members_ptr<std::string>[ptr_index], name);
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
			o.*ObjectType::template members_ptr<V>[ptr_index] = ObjectType::template members_default<V>[default_index];
		}
	}
};

} // struct_mapping::detail

#endif
