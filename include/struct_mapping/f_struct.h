#ifndef STRUCT_MAPPING_F_STRUCT_H
#define STRUCT_MAPPING_F_STRUCT_H

#include <functional>
#include <limits>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "f.h"

namespace struct_mapping::detail {

template<typename T, bool = is_array_like_v<T>, bool = is_map_like_v<T>>
class F {
public:
	enum class MemberType {
		Complex = -1,
		Bool = 0,
		Char = 1,
		UnsignedChar = 2,
		Short = 3,
		UnsignedShort = 4,
		Int = 5,
		UnsignedInt = 6,
		Long = 7,
		UnsignedLong = 8,
		LongLong = 9,
		Float = 10,
		Double = 11,
		String = 12,
	};

	using MemberPtrIndex = unsigned int;
	using MemberDeepIndex = unsigned int;
	using MemberName = std::string;
	using Member = std::tuple<MemberName, MemberType, MemberPtrIndex, MemberDeepIndex>;

	template<typename V>
	using Member_ptr = V T::*;

	using Release = bool (T&);
	using SetBool = void (T&, const std::string &, bool);
	using SetFloatingPoint = void (T&, const std::string &, double);
	using SetIntegral = void (T&, const std::string &, long long);
	using SetString = void (T&, const std::string &, const std::string &);
	using Use = void (T&, const std::string &);
	using IterateOver = void (T&, const std::string &);

	template<typename V>
	static void reg(Member_ptr<V> ptr, std::string const & name) {
		if (members_name_index.find(name) == members_name_index.end()) {
			F_reset::add(reset);
			if constexpr (is_array_like_v<V> || is_map_like_v<V>) add_reset_array_map_like<V>();

			members_name_index.emplace(name, members.size());

			if constexpr (constexpr auto member_type = get_member_type<V>(); member_type == MemberType::Complex) {
				members.emplace_back(name, member_type, NO_INDEX, members_release.size());
				members_release.emplace_back(std::function<Release>([ptr] (T & o) {
					return F<V>::release(o.*ptr);
				}));

				members_set_bool.emplace_back(std::function<SetBool>([ptr] (T & o, const std::string & name_, bool value_) {
					F<V>::set_bool(o.*ptr, name_, value_);
				}));

				members_set_floating_point.emplace_back(std::function<SetFloatingPoint>([ptr] (T & o, const std::string & name_, double value_) {
					F<V>::set_floating_point(o.*ptr, name_, value_);
				}));

				members_set_integral.emplace_back(std::function<SetFloatingPoint>([ptr] (T & o, const std::string & name_, long long value_) {
					F<V>::set_integral(o.*ptr, name_, value_);
				}));

				members_set_string.emplace_back(std::function<SetString>([ptr] (T & o, const std::string & name_, const std::string & value_) {
					F<V>::set_string(o.*ptr, name_, value_);
				}));

				members_use.emplace_back(std::function<Use>([ptr] (T & o, const std::string & name_) {
					F<V>::use(o.*ptr, name_);
				}));

				members_iterate_over.emplace_back(std::function<IterateOver>([ptr] (T & o, const std::string & name_) {
					F<V>::iterate_over(o.*ptr, name_);
				}));
			} else {
				members.emplace_back(name, member_type, members_ptr<V>.size(), NO_INDEX);
				members_ptr<V>.emplace_back(ptr);
			}
		}
	}

	static void iterate_over(T & o, const std::string & name) {
		F_iterate_over::start_struct(name);
		for (auto& [member_name, member_type, member_ptr_index, member_deep_index] : members) {
			switch (member_type) {
			case MemberType::Bool: F_iterate_over::set_bool(member_name, o.*members_ptr<bool>[member_ptr_index]);break;
			case MemberType::Char: F_iterate_over::set_integral(member_name, o.*members_ptr<char>[member_ptr_index]);break;
			case MemberType::UnsignedChar: F_iterate_over::set_integral(member_name, o.*members_ptr<unsigned char>[member_ptr_index]);break;
			case MemberType::Short: F_iterate_over::set_integral(member_name, o.*members_ptr<short>[member_ptr_index]);break;
			case MemberType::UnsignedShort: F_iterate_over::set_integral(member_name, o.*members_ptr<unsigned short>[member_ptr_index]);break;
			case MemberType::Int: F_iterate_over::set_integral(member_name, o.*members_ptr<int>[member_ptr_index]);break;
			case MemberType::UnsignedInt: F_iterate_over::set_integral(member_name, o.*members_ptr<unsigned int>[member_ptr_index]);break;
			case MemberType::Long: F_iterate_over::set_integral(member_name, o.*members_ptr<long>[member_ptr_index]);break;
			case MemberType::UnsignedLong: F_iterate_over::set_integral(member_name, static_cast<long long>(o.*members_ptr<unsigned long>[member_ptr_index]));break;
			case MemberType::LongLong: F_iterate_over::set_integral(member_name, o.*members_ptr<long long>[member_ptr_index]);break;
			case MemberType::Float: F_iterate_over::set_floating_point(member_name, o.*members_ptr<float>[member_ptr_index]);break;
			case MemberType::Double: F_iterate_over::set_floating_point(member_name, o.*members_ptr<double>[member_ptr_index]);break;
			case MemberType::String: F_iterate_over::set_string(member_name, o.*members_ptr<std::string>[member_ptr_index]);break;
			case MemberType::Complex: members_iterate_over[member_deep_index](o, member_name);break;
			}
		}

		F_iterate_over::end_struct();
	}

	static bool release(T & o) {
		if (deep_index == NO_INDEX) return true;
		else if (members_release[deep_index](o)) deep_index = NO_INDEX;

		return false;
	}

	static void set_bool(T & o, const std::string & name, bool value) {
		if (deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("set_bool : unknown member " + name);
			else if (std::get<1>(members[it->second]) != MemberType::Bool) throw StructMappingException("set_bool : bad type for " + name);
			else o.*members_ptr<bool>[std::get<2>(members[it->second])] = value;
		}	else {
			members_set_bool[deep_index](o, name, value);
		}
	}

	static void set_floating_point(T & o, const std::string & name, double value) {
		if (deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("set_floating_point : unknown member " + name);
			else {
				switch (auto member_type = std::get<1>(members[it->second]); member_type) {
				case MemberType::Float: o.*members_ptr<float>[std::get<2>(members[it->second])] = static_cast<float>(value); break;
				case MemberType::Double: o.*members_ptr<double>[std::get<2>(members[it->second])] = static_cast<double>(value); break;
				case MemberType::Char: o.*members_ptr<char>[std::get<2>(members[it->second])] = static_cast<char>(value); break;
				case MemberType::UnsignedChar: o.*members_ptr<unsigned char>[std::get<2>(members[it->second])] = static_cast<unsigned char>(value); break;
				case MemberType::Short: o.*members_ptr<short>[std::get<2>(members[it->second])] = static_cast<short>(value); break;
				case MemberType::UnsignedShort: o.*members_ptr<unsigned short>[std::get<2>(members[it->second])] = static_cast<unsigned short>(value); break;
				case MemberType::Int: o.*members_ptr<int>[std::get<2>(members[it->second])] = static_cast<int>(value); break;
				case MemberType::UnsignedInt: o.*members_ptr<unsigned int>[std::get<2>(members[it->second])] = static_cast<unsigned int>(value); break;
				case MemberType::Long: o.*members_ptr<long>[std::get<2>(members[it->second])] = static_cast<long>(value); break;
				case MemberType::UnsignedLong: o.*members_ptr<unsigned long>[std::get<2>(members[it->second])] = static_cast<unsigned long>(value); break;
				case MemberType::LongLong: o.*members_ptr<long long>[std::get<2>(members[it->second])] = static_cast<long long>(value); break;
				default: throw StructMappingException("set_floating_point : bad type for " + name);
				}
			}
		}	else {
			members_set_floating_point[deep_index](o, name, value);
		}
	}

	static void set_integral(T & o, const std::string & name, long long value) {
		if (deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("set_integral : unknown member " + name);
			else {
				switch (auto member_type = std::get<1>(members[it->second]); member_type) {
				case MemberType::Char: o.*members_ptr<char>[std::get<2>(members[it->second])] = static_cast<char>(value); break;
				case MemberType::UnsignedChar: o.*members_ptr<unsigned char>[std::get<2>(members[it->second])] = static_cast<unsigned char>(value); break;
				case MemberType::Short: o.*members_ptr<short>[std::get<2>(members[it->second])] = static_cast<short>(value); break;
				case MemberType::UnsignedShort: o.*members_ptr<unsigned short>[std::get<2>(members[it->second])] = static_cast<unsigned short>(value); break;
				case MemberType::Int: o.*members_ptr<int>[std::get<2>(members[it->second])] = static_cast<int>(value); break;
				case MemberType::UnsignedInt: o.*members_ptr<unsigned int>[std::get<2>(members[it->second])] = static_cast<unsigned int>(value); break;
				case MemberType::Long: o.*members_ptr<long>[std::get<2>(members[it->second])] = static_cast<long>(value); break;
				case MemberType::UnsignedLong: o.*members_ptr<unsigned long>[std::get<2>(members[it->second])] = static_cast<unsigned long>(value); break;
				case MemberType::LongLong: o.*members_ptr<long long>[std::get<2>(members[it->second])] = static_cast<long long>(value); break;
				case MemberType::Float: o.*members_ptr<float>[std::get<2>(members[it->second])] = static_cast<float>(value); break;
				case MemberType::Double: o.*members_ptr<double>[std::get<2>(members[it->second])] = static_cast<double>(value); break;
				default: throw StructMappingException("set_integral : bad type for " + name);
				}
			}
		}	else members_set_integral[deep_index](o, name, value);
	}

	static void set_string(T & o, const std::string & name, const std::string & value) {
		if (deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("set_string : unknown member " + name);
			else if (std::get<1>(members[it->second]) != MemberType::String) throw StructMappingException("set_string : bad type for " + name);
			else o.*members_ptr<std::string>[std::get<2>(members[it->second])] = value;
		}	else members_set_string[deep_index](o, name, value);
	}

	static void use(T & o, const std::string & name) {
		if (deep_index == NO_INDEX) {
			if (auto it = members_name_index.find(name); it == members_name_index.end()) throw StructMappingException("use : unknown member " + name);
			else deep_index = std::get<3>(members[it->second]);
		}	else members_use[deep_index](o, name);
	}

private:
	static constexpr unsigned int NO_INDEX = std::numeric_limits<unsigned int>::max();

	static inline std::vector<Member> members;
	static inline std::unordered_map<MemberName, unsigned int> members_name_index;

	template<typename V>
	static inline std::vector<Member_ptr<V>> members_ptr;

	static inline std::vector<std::function<Release>> members_release;
	static inline std::vector<std::function<SetBool>> members_set_bool;
	static inline std::vector<std::function<SetFloatingPoint>> members_set_floating_point;
	static inline std::vector<std::function<SetIntegral>> members_set_integral;
	static inline std::vector<std::function<SetString>> members_set_string;
	static inline std::vector<std::function<Use>> members_use;
	static inline std::vector<std::function<IterateOver>> members_iterate_over;

	static inline unsigned int deep_index = NO_INDEX;

	template<typename V>
	static constexpr MemberType get_member_type() {
		if constexpr (std::is_same_v<V, bool>) return MemberType::Bool;
		if constexpr (std::is_same_v<V, char>) return MemberType::Char;
		if constexpr (std::is_same_v<V, unsigned char>) return MemberType::UnsignedChar;
		if constexpr (std::is_same_v<V, short>) return MemberType::Short;
		if constexpr (std::is_same_v<V, unsigned short>) return MemberType::UnsignedShort;
		if constexpr (std::is_same_v<V, int>) return MemberType::Int;
		if constexpr (std::is_same_v<V, unsigned int>) return MemberType::UnsignedInt;
		if constexpr (std::is_same_v<V, long>) return MemberType::Long;
		if constexpr (std::is_same_v<V, unsigned long>) return MemberType::UnsignedLong;
		if constexpr (std::is_same_v<V, long long>) return MemberType::LongLong;
		if constexpr (std::is_same_v<V, float>) return MemberType::Float;
		if constexpr (std::is_same_v<V, double>) return MemberType::Double;
		if constexpr (std::is_same_v<V, std::string>) return MemberType::String;
		
		return MemberType::Complex;
	}

	template<typename V>
	static void add_reset_array_map_like() {
		F_reset::add(F<V>::reset);
		if constexpr (is_array_like_v<typename F<V>::ValueType<V>> || is_map_like_v<typename F<V>::ValueType<V>>) {
			add_reset_array_map_like<typename F<V>::ValueType<V>>();
		}
	}

	static void reset() {
		deep_index = NO_INDEX;
	}
};

}

#endif
