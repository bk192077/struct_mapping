#ifndef STRUCT_MAPPING_F_STRUCT_H
#define STRUCT_MAPPING_F_STRUCT_H

#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "f.h"
#include "member_string.h"
#include "options/option_bounds.h"
#include "options/option_default.h"
#include "options/option_not_empty.h"
#include "options/option_required.h"

namespace struct_mapping::detail {

template<typename T, bool = is_array_like_v<T>, bool = is_map_like_v<T>>
class F {
public:
	using Index = unsigned int;
	template<typename V> using Member_ptr = V T::*;

	template<typename V> struct MemberType {};

	class Functions {
	public:
		using CheckNotEmpty = void (T&, const std::string &);
		using Init = void ();
		using IterateOver = void (T&, const std::string &);
		using Release = bool (T&);
		using SetBool = void (T&, const std::string &, bool);
		using SetDefault = void (T&, Index);
		using SetFloatingPoint = void (T&, const std::string &, double);
		using SetIntegral = void (T&, const std::string &, long long);
		using SetString = void (T&, const std::string &, const std::string &);
		using Use = void (T&, const std::string &);

		template<typename V>
		Index add(Member_ptr<V> ptr) {
			f_check_not_empty.emplace_back([ptr] (T & o, const std::string & name_) {F<V>::check_not_empty(o.*ptr, name_);});
			f_init.emplace_back([] {F<V>::init();});
			f_iterate_over.emplace_back([ptr] (T & o, const std::string & name_) {F<V>::iterate_over(o.*ptr, name_);});
			f_release.emplace_back([ptr] (T & o) {return F<V>::release(o.*ptr);});
			f_set_bool.emplace_back([ptr] (T & o, const std::string & name_, bool value_) {F<V>::set_bool(o.*ptr, name_, value_);});
			f_set_default.emplace_back([ptr] (T & o, Index index_) {o.*ptr = members_default<V>[index_];});
			f_set_floating_point.emplace_back([ptr] (T & o, const std::string & name_, double value_) {F<V>::set_floating_point(o.*ptr, name_, value_);});
			f_set_integral.emplace_back([ptr] (T & o, const std::string & name_, long long value_) {F<V>::set_integral(o.*ptr, name_, value_);});
			f_set_string.emplace_back([ptr] (T & o, const std::string & name_, const std::string & value_) {F<V>::set_string(o.*ptr, name_, value_);});
			f_use.emplace_back([ptr] (T & o, const std::string & name_) {F<V>::use(o.*ptr, name_);});
			return static_cast<Index>(f_use.size()) - 1;
		}

		std::vector<std::function<CheckNotEmpty>> f_check_not_empty;
		std::vector<std::function<Init>> f_init;
		std::vector<std::function<IterateOver>> f_iterate_over;
		std::vector<std::function<Release>> f_release;
		std::vector<std::function<SetBool>> f_set_bool;
		std::vector<std::function<SetDefault>> f_set_default;
		std::vector<std::function<SetFloatingPoint>> f_set_floating_point;
		std::vector<std::function<SetIntegral>> f_set_integral;
		std::vector<std::function<SetString>> f_set_string;
		std::vector<std::function<Use>> f_use;
	};

	template<typename V, typename ... U, template<typename> typename ... Options>
	static void reg(Member_ptr<V> ptr, std::string const & name, Options<U>&& ... options) {
		if (members_name_index.find(name) == members_name_index.end()) {
			reg_reset<V>();			

			members_name_index.emplace(name, static_cast<Index>(members.size()));
			Member member(name, ptr, MemberType<V>{}, std::forward<Options<U>>(options)...);

			members.push_back(std::move(member));
			members_ptr<V>.push_back(ptr);
		}
	}

	static void check_not_empty(T &, const std::string &) {
	}

	static void init() {
		for (auto & member : members) {
			member.init();
		}
	}

	static void iterate_over(T & o, const std::string & name) {
		F_iterate_over::start_struct(name);
		for (auto& member : members) {
			member.iterate_over(o);
		}

		F_iterate_over::end_struct();
	}

	static bool release(T & o) {
		if (member_deep_index == NO_INDEX) {
			for (auto & member : members) {
				member.release(o);
			}
			return true;
		}	else if (functions.f_release[member_deep_index](o)) member_deep_index = NO_INDEX;

		return false;
	}

	static void set_bool(T & o, const std::string & name, bool value) {
		if (member_deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("bad member: " + name);
			else if (members[it->second].type != Member::Type::Bool) throw StructMappingException("bad type (bool) for member: " + name);
			else set<bool>(o, value, it->second);
		}	else {
			functions.f_set_bool[member_deep_index](o, name, value);
		}
	}

	static void set_floating_point(T & o, const std::string & name, double value) {
		if (member_deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("bad member: " + name);
			else {
				switch (members[it->second].type) {
				case Member::Type::Float: set<float>(o, value, it->second); break;
				case Member::Type::Double: set<double>(o, value, it->second); break;
				default: throw StructMappingException("bad set type (floating point) for member: " + name);
				}
			}
		}	else {
			functions.f_set_floating_point[member_deep_index](o, name, value);
		}
	}

	static void set_integral(T & o, const std::string & name, long long value) {
		if (member_deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("bad member: " + name);
			else {
				switch (members[it->second].type) {
				case Member::Type::Char: set<char>(o, value, it->second); break;
				case Member::Type::UnsignedChar: set<unsigned char>(o, value, it->second); break;
				case Member::Type::Short: set<short>(o, value, it->second); break;
				case Member::Type::UnsignedShort: set<unsigned short>(o, value, it->second); break;
				case Member::Type::Int: set<int>(o, value, it->second); break;
				case Member::Type::UnsignedInt: set<unsigned int>(o, value, it->second); break;
				case Member::Type::Long: set<long>(o, value, it->second); break;
				case Member::Type::LongLong: set<long long>(o, value, it->second); break;
				case Member::Type::Float: set<float>(o, value, it->second); break;
				case Member::Type::Double: set<double>(o, value, it->second); break;
				default: throw StructMappingException("bad type (integral) for member: " + name);
				}
			}
		}	else functions.f_set_integral[member_deep_index](o, name, value);
	}

	static void set_string(T & o, const std::string & name, const std::string & value) {
		if (member_deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) {
				throw StructMappingException("bad member: " + name);
			}	else if (members[it->second].type == Member::Type::Enum || (members[it->second].type == Member::Type::Complex && members[it->second].member_string_index != NO_INDEX)) {
				members[it->second].changed = true;
				member_string_from_string[members[it->second].member_string_index](o, value);
			}	else if (members[it->second].type != Member::Type::String) {
				throw StructMappingException("bad type (string) for member: " + name);
			}	else {
				set<std::string>(o, value, it->second);
			}
		}	else {
			functions.f_set_string[member_deep_index](o, name, value);
		}
	}

	static void use(T & o, const std::string & name) {
		if (member_deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("bad member: " + name);
			else {
				member_deep_index = members[it->second].deep_index;
				functions.f_init[member_deep_index]();
				members[it->second].changed = true;
			}
		}	else functions.f_use[member_deep_index](o, name);
	}

private:
	class Member {
	public:
		using Name = std::string;

		enum class Type {
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

		template<typename V, typename ... U, template<typename> typename ... Options>
		Member(Name name_, Member_ptr<V> ptr_, MemberType<V>, Options<U>&& ... options)
			:	name(name_), type(get_member_type<V>()) {

			ptr_index = static_cast<Index>(members_ptr<V>.size());

			if constexpr (Member::template get_member_type<V>() == Member::Type::Complex) {
				if (!IsMemberStringExist<V>::value) {
					deep_index = functions.add(ptr_);
					(add_option<V>(std::forward<Options<U>>(options)), ...);
					return;
				}
			}

			deep_index = NO_INDEX;

			if (Member::template get_member_type<V>() == Member::Type::Enum ||
					(Member::template get_member_type<V>() == Member::Type::Complex && IsMemberStringExist<V>::value)) {
				member_string_index = static_cast<Index>(member_string_from_string.size());
				member_string_from_string.push_back([ptr_, name_] (T & o, const std::string & value_) {
					o.*ptr_ = MemberString<V>::from_string(name_)(value_);
				});
				member_string_to_string.push_back([ptr_, name_] (T & o) {
					return MemberString<V>::to_string(name_)(o.*ptr_);
				});
			}

			(add_option<V>(std::forward<Options<U>>(options)), ...);
		}

		template<typename V>
		static constexpr auto get_member_type() {
			if constexpr (std::is_same_v<V, bool>) return Member::Type::Bool;
			if constexpr (std::is_same_v<V, char>) return Member::Type::Char;
			if constexpr (std::is_same_v<V, unsigned char>) return Member::Type::UnsignedChar;
			if constexpr (std::is_same_v<V, short>) return Member::Type::Short;
			if constexpr (std::is_same_v<V, unsigned short>) return Member::Type::UnsignedShort;
			if constexpr (std::is_same_v<V, int>) return Member::Type::Int;
			if constexpr (std::is_same_v<V, unsigned int>) return Member::Type::UnsignedInt;
			if constexpr (std::is_same_v<V, long>) return Member::Type::Long;
			if constexpr (std::is_same_v<V, long long>) return Member::Type::LongLong;
			if constexpr (std::is_same_v<V, float>) return Member::Type::Float;
			if constexpr (std::is_same_v<V, double>) return Member::Type::Double;
			if constexpr (std::is_same_v<V, std::string>) return Member::Type::String;
			if constexpr (std::is_enum_v<V>) return Member::Type::Enum;
			
			return Member::Type::Complex;
		}

		void init() {
			changed = false;
		}

		void iterate_over(T & o) {
			switch (type) {
			case Member::Type::Bool: F_iterate_over::set_bool(name, o.*members_ptr<bool>[ptr_index]); break;
			case Member::Type::Char: F_iterate_over::set_integral(name, o.*members_ptr<char>[ptr_index]); break;
			case Member::Type::UnsignedChar: F_iterate_over::set_integral(name, o.*members_ptr<unsigned char>[ptr_index]); break;
			case Member::Type::Short: F_iterate_over::set_integral(name, o.*members_ptr<short>[ptr_index]); break;
			case Member::Type::UnsignedShort: F_iterate_over::set_integral(name, o.*members_ptr<unsigned short>[ptr_index]); break;
			case Member::Type::Int: F_iterate_over::set_integral(name, o.*members_ptr<int>[ptr_index]); break;
			case Member::Type::UnsignedInt: F_iterate_over::set_integral(name, o.*members_ptr<unsigned int>[ptr_index]); break;
			case Member::Type::Long: F_iterate_over::set_integral(name, o.*members_ptr<long>[ptr_index]); break;
			case Member::Type::LongLong: F_iterate_over::set_integral(name, o.*members_ptr<long long>[ptr_index]); break;
			case Member::Type::Float: F_iterate_over::set_floating_point(name, o.*members_ptr<float>[ptr_index]); break;
			case Member::Type::Double: F_iterate_over::set_floating_point(name, o.*members_ptr<double>[ptr_index]); break;
			case Member::Type::String: F_iterate_over::set_string(name, o.*members_ptr<std::string>[ptr_index]); break;
			case Member::Type::Enum: F_iterate_over::set_string(name, member_string_to_string[member_string_index](o)); break;
			case Member::Type::Complex:
				if (member_string_index != NO_INDEX) {
					F_iterate_over::set_string(name, member_string_to_string[member_string_index](o));
				} else {
					functions.f_iterate_over[deep_index](o, name);
				}
 				break;
			}
		}

		void release(T & o) {
			process_required();
			process_default(o);
			process_not_empty(o);
			changed = false;
		}

		Name name;
		Index bounds_index = NO_INDEX;
		bool changed = false;
		Index default_index = NO_INDEX;
		Index deep_index;
		Index member_string_index = NO_INDEX;
		Index ptr_index;
		bool option_not_empty = false;
		bool option_required = false;
		Type type;

	private:
		template<typename V, typename U, template<typename> typename Op>
		void add_option(Op<U>&& op) {
			if constexpr (std::is_same_v<Bounds<U>, std::decay_t<Op<U>>>) {
				op.template check_option<V>(name);
				add_option_bounds<V>(op);
			} else if constexpr (std::is_same_v<Default<U>, std::decay_t<Op<U>>>) {
				op.template check_option<V>(name);
				add_option_default<V>(op);
			} else if constexpr (std::is_same_v<NotEmpty<U>, std::decay_t<Op<U>>>) {
				op.template check_option<V>();
				add_option_not_empty<V>();
			} else if constexpr (std::is_same_v<Required<U>, std::decay_t<Op<U>>>) {
				add_option_required<V>();
			}
		}

		template<typename V, typename U>
		void add_option_bounds(Bounds<U> & op) {
			bounds_index = static_cast<Index>(members_bounds<V>.size());
			members_bounds<V>.push_back(op);
		}

		template<typename V, typename U>
		void add_option_default(Default<U> & op) {
			if constexpr (std::is_same_v<V, std::string> && std::is_same_v<U, const char *>) {
				default_index = static_cast<Index>(members_default<std::string>.size());
				members_default<std::string>.push_back(op.get_value());
			}	else if constexpr (std::is_enum_v<V>) {
				default_index = static_cast<Index>(members_default<std::string>.size());
				members_default<std::string>.push_back(MemberString<V>::to_string(name)(op.get_value()));
			}	else if constexpr (std::is_class_v<V> && (std::is_same_v<U, std::string> || std::is_same_v<U, const char *>)) {
				if (member_string_index != NO_INDEX) {
					default_index = static_cast<Index>(members_default<std::string>.size());
					members_default<std::string>.push_back(op.get_value());
				}
			}	else if constexpr (std::is_same_v<V, U> || (is_integer_or_floating_point_v<V> && is_integer_or_floating_point_v<U>)) {
				default_index = static_cast<Index>(members_default<V>.size());
				members_default<V>.push_back(static_cast<V>(op.get_value()));
			}
		}

		template<typename V>
		void add_option_not_empty() {
			option_not_empty = true;
		}

		template<typename V>
		void add_option_required() {
			option_required = true;
		}

		void process_default(T & o) {
			if (!changed) {
				switch (type) {
				case Member::Type::Bool: set_default<bool>(o); break;
				case Member::Type::Char: set_default<char>(o); break;
				case Member::Type::UnsignedChar: set_default<unsigned char>(o); break;
				case Member::Type::Short: set_default<short>(o); break;
				case Member::Type::UnsignedShort: set_default<unsigned short>(o); break;
				case Member::Type::Int: set_default<int>(o); break;
				case Member::Type::UnsignedInt: set_default<unsigned int>(o); break;
				case Member::Type::Long: set_default<long>(o); break;
				case Member::Type::LongLong: set_default<long long>(o); break;
				case Member::Type::Float: set_default<float>(o); break;
				case Member::Type::Double: set_default<double>(o); break;
				case Member::Type::String: set_default<std::string>(o); break;
				case Member::Type::Enum:
					if (default_index != NO_INDEX) member_string_from_string[member_string_index](o, members_default<std::string>[default_index]);
					break;
				case Member::Type::Complex:
					if (default_index != NO_INDEX) {
						if (member_string_index != NO_INDEX) member_string_from_string[member_string_index](o, members_default<std::string>[default_index]);
						else functions.f_set_default[deep_index](o, default_index);
					}
					break;
				}
			}
		}

		void process_not_empty(T & o) {
			if (option_not_empty) {
				switch (type) {
				case Member::Type::String: NotEmpty<>::check_result(o.*members_ptr<std::string>[ptr_index], name); break;
				case Member::Type::Complex: functions.f_check_not_empty[deep_index](o, name);	break;
				default: break;
				}
			} 
		}

		void process_required() {
			if (option_required) {
				Required<>::check_result(changed, name);
			}
		}

		template<typename V>
		void set_default(T & o) {
			if (default_index != NO_INDEX) o.*members_ptr<V>[ptr_index] = members_default<V>[default_index];
		}
	};

	static inline constexpr Index NO_INDEX = std::numeric_limits<Index>::max();

	static inline Functions functions;
	static inline std::vector<std::function<void(T&, const std::string &)>> member_string_from_string{};
	static inline std::vector<std::function<std::string (T&)>> member_string_to_string{};
	static inline Index member_deep_index = NO_INDEX;
	static inline std::vector<Member> members;
	
	template<typename V>
	static inline std::vector<std::function<void(V, const std::string &)>> members_bounds{};
	
	template<typename V>
	static inline std::vector<V> members_default{};
	
	static inline std::unordered_map<typename Member::Name, Index> members_name_index;
	
	template<typename V>
	static inline std::vector<Member_ptr<V>> members_ptr{};

	template<typename V>
	static void reg_reset() {
		F_reset::reg(reset);
		if constexpr (is_array_like_v<V> || is_map_like_v<V>) reg_reset_array_map_like<V>();
	}

	template<typename V>
	static void reg_reset_array_map_like() {
		F_reset::reg(F<V>::reset);
		if constexpr (is_array_like_v<typename F<V>::template ValueType<V>> || is_map_like_v<typename F<V>::template ValueType<V>>) {
			reg_reset_array_map_like<typename F<V>::template ValueType<V>>();
		}
	}

	static void reset() {
		member_deep_index = NO_INDEX;
	}

	template<typename U, typename V>
	static void set(T & o, V value, unsigned int index) {
		if constexpr (is_integer_or_floating_point_v<U>) {
			if (!in_limits<U>(value)) {
				throw StructMappingException(
					"bad value for '" + members[index].name + "': " + std::to_string(value) + " is out of limits of type [" +
					std::to_string(std::numeric_limits<U>::lowest()) +
					" : " +
					std::to_string(std::numeric_limits<U>::max()) + "]");
			}
		}

		if (members[index].bounds_index != NO_INDEX) members_bounds<U>[members[index].bounds_index](static_cast<U>(value), members[index].name);

		members[index].changed = true;

		o.*members_ptr<U>[members[index].ptr_index] = static_cast<U>(value);
	}
};

}

#endif
