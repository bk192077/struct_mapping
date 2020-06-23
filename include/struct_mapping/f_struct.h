#ifndef STRUCT_MAPPING_F_STRUCT_H
#define STRUCT_MAPPING_F_STRUCT_H

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "f.h"

namespace struct_mapping::detail {

template<typename T, bool = is_array_like_v<T>, bool = is_map_like_v<T>>
class F {
public:
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
		if (std::find(order_members.begin(), order_members.end(), name) == order_members.end()) order_members.push_back(name);

		if constexpr (is_integral_or_floating_point_or_string_v<V>) {
			members<V>[name] = ptr;
		} else {
			fs_release[name] = std::function<Release>([ptr] (T & o) {
				return F<V>::release(o.*ptr);
			});

			fs_set_bool[name] = std::function<SetBool>([ptr] (T & o, const std::string & name_, bool value_) {
				F<V>::set_bool(o.*ptr, name_, value_);
			});

			fs_set_floating_point[name] = std::function<SetFloatingPoint>([ptr] (T & o, const std::string & name_, double value_) {
				F<V>::set_floating_point(o.*ptr, name_, value_);
			});

			fs_set_integral[name] = std::function<SetFloatingPoint>([ptr] (T & o, const std::string & name_, long long value_) {
				F<V>::set_integral(o.*ptr, name_, value_);
			});

			fs_set_string[name] = std::function<SetString>([ptr] (T & o, const std::string & name_, const std::string & value_) {
				F<V>::set_string(o.*ptr, name_, value_);
			});

			fs_use[name] = std::function<Use>([ptr] (T & o, const std::string & name_) {
				F<V>::use(o.*ptr, name_);
			});

			fs_iterate_over[name] = std::function<IterateOver>([ptr] (T & o, const std::string & name_) {
				F<V>::iterate_over(o.*ptr, name_);
			});
		}
	}

	static void iterate_over(T & o, const std::string & name) {
		F_iterate_over::start_struct(name);
		for (auto& member_name : order_members) {
			if (auto it_b = members<bool>.find(member_name); it_b != members<bool>.end()) F_iterate_over::set_bool(member_name, o.*it_b->second);
			else if (auto it_c = members<char>.find(member_name); it_c != members<char>.end()) F_iterate_over::set_integral(member_name, o.*it_c->second);
			else if (auto it_uc = members<unsigned char>.find(member_name); it_uc != members<unsigned char>.end()) F_iterate_over::set_integral(member_name, o.*it_uc->second);
			else if (auto it_s = members<short>.find(member_name); it_s != members<short>.end()) F_iterate_over::set_integral(member_name, o.*it_s->second);
			else if (auto it_us = members<unsigned short>.find(member_name); it_us != members<unsigned short>.end()) F_iterate_over::set_integral(member_name, o.*it_us->second);
			else if (auto it_i = members<int>.find(member_name); it_i != members<int>.end()) F_iterate_over::set_integral(member_name, o.*it_i->second);
			else if (auto it_ui = members<unsigned int>.find(member_name); it_ui != members<unsigned int>.end()) F_iterate_over::set_integral(member_name, o.*it_ui->second);
			else if (auto it_l = members<long>.find(member_name); it_l != members<long>.end()) F_iterate_over::set_integral(member_name, o.*it_l->second);
			else if (auto it_ul = members<unsigned long>.find(member_name); it_ul != members<unsigned long>.end()) F_iterate_over::set_integral(member_name, static_cast<long long>(o.*it_ul->second));
			else if (auto it_ll = members<long long>.find(member_name); it_ll != members<long long>.end()) F_iterate_over::set_integral(member_name, o.*it_ll->second);
			else if (auto it_f = members<float>.find(member_name); it_f != members<float>.end()) F_iterate_over::set_floating_point(member_name, o.*it_f->second);
			else if (auto it_d = members<double>.find(member_name); it_d != members<double>.end()) F_iterate_over::set_floating_point(member_name, o.*it_d->second);
			else if (auto it_st = members<std::string>.find(member_name); it_st != members<std::string>.end()) F_iterate_over::set_string(member_name, o.*it_st->second);
			else if (auto it = fs_iterate_over.find(member_name); it != fs_iterate_over.end()) (it->second)(o, member_name);
			else throw StructMappingException("iterate_over: unknown member: " + name + "::" + member_name);
		}

		F_iterate_over::end_struct();
	}

	static bool release(T & o) {
		if (used_name.empty()) {
			return true;
		}	else {
			if (fs_release[used_name](o)) {
				used_name = "";
			}
			return false;
		}
	}

	static void set_bool(T & o, const std::string & name, bool value) {
		if (used_name.empty()) {
			if (auto it = members<bool>.find(name); it == members<bool>.end()) {
				throw StructMappingException("set_bool: unknown member: " + name);
			}

			o.*members<bool>[name] = value;
		}	else {
			fs_set_bool[used_name](o, name, value);
		}
	}

	static void set_floating_point(T & o, const std::string & name, double value) {
		if (used_name.empty()) {
			if (auto it_float = members<float>.find(name); it_float != members<float>.end()) o.*it_float->second = static_cast<float>(value);
			else if (auto it_double = members<double>.find(name); it_double != members<double>.end()) o.*it_double->second = value;
			else if (auto it_char = members<char>.find(name); it_char != members<char>.end()) o.*it_char->second = static_cast<char>(value);
			else if (auto it_unsigned_char = members<unsigned char>.find(name); it_unsigned_char != members<unsigned char>.end()) o.*it_unsigned_char->second = static_cast<unsigned char>(value);
			else if (auto it_short = members<short>.find(name); it_short != members<short>.end()) o.*it_short->second = static_cast<short>(value);
			else if (auto it_unsigned_short = members<unsigned short>.find(name); it_unsigned_short != members<unsigned short>.end()) o.*it_unsigned_short->second = static_cast<unsigned short>(value);
			else if (auto it_int = members<int>.find(name); it_int != members<int>.end()) o.*it_int->second = static_cast<int>(value);
			else if (auto it_unsigned_int = members<unsigned int>.find(name); it_unsigned_int != members<unsigned int>.end()) o.*it_unsigned_int->second = static_cast<unsigned int>(value);
			else if (auto it_long = members<long>.find(name); it_long != members<long>.end()) o.*it_long->second = static_cast<long>(value);
			else if (auto it_unsigned_long = members<unsigned long>.find(name); it_unsigned_long != members<unsigned long>.end()) o.*it_unsigned_long->second = static_cast<unsigned long>(value);
			else if (auto it_long_long = members<long long>.find(name); it_long_long != members<long long>.end()) o.*it_long_long->second = static_cast<long long>(value);
			else throw StructMappingException("set_floating_point: unknown member: " + name);
		}	else {
			fs_set_floating_point[used_name](o, name, value);
		}
	}

	static void set_integral(T & o, const std::string & name, long long value) {
		if (used_name.empty()) {
			if (auto it_float = members<float>.find(name); it_float != members<float>.end()) o.*it_float->second = static_cast<float>(value);
			else if (auto it_double = members<double>.find(name); it_double != members<double>.end()) o.*it_double->second = static_cast<double>(value);
			else if (auto it_char = members<char>.find(name); it_char != members<char>.end()) o.*it_char->second = static_cast<char>(value);
			else if (auto it_unsigned_char = members<unsigned char>.find(name); it_unsigned_char != members<unsigned char>.end()) o.*it_unsigned_char->second = static_cast<unsigned char>(value);
			else if (auto it_short = members<short>.find(name); it_short != members<short>.end()) o.*it_short->second = static_cast<short>(value);
			else if (auto it_unsigned_short = members<unsigned short>.find(name); it_unsigned_short != members<unsigned short>.end()) o.*it_unsigned_short->second = static_cast<unsigned short>(value);
			else if (auto it_int = members<int>.find(name); it_int != members<int>.end()) o.*it_int->second = static_cast<int>(value);
			else if (auto it_unsigned_int = members<unsigned int>.find(name); it_unsigned_int != members<unsigned int>.end()) o.*it_unsigned_int->second = static_cast<unsigned int>(value);
			else if (auto it_long = members<long>.find(name); it_long != members<long>.end()) o.*it_long->second = static_cast<long>(value);
			else if (auto it_unsigned_long = members<unsigned long>.find(name); it_unsigned_long != members<unsigned long>.end()) o.*it_unsigned_long->second = static_cast<unsigned long>(value);
			else if (auto it_long_long = members<long long>.find(name); it_long_long != members<long long>.end()) o.*it_long_long->second = static_cast<long long>(value);
			else throw StructMappingException("set_integral: unknown member: " + name);
		}	else {
			fs_set_integral[used_name](o, name, value);
		}
	}

	static void set_string(T & o, const std::string & name, const std::string & value) {
		if (used_name.empty()) {
			if (auto it = members<std::string>.find(name); it == members<std::string>.end()) {
				throw StructMappingException("set_string: unknown member: " + name);
			}

			o.*members<std::string>[name] = value;
		}	else {
			fs_set_string[used_name](o, name, value);
		}
	}

	static void use(T & o, const std::string & name) {
		if (used_name.empty()) {
			used_name = name;
		}	else {
			fs_use[used_name](o, name);
		}
	}

private:
	static inline std::string used_name = "";

	template<typename V>
	static inline std::unordered_map<std::string, Member_ptr<V>> members;

	static inline std::unordered_map<std::string, std::function<Release>> fs_release;
	static inline std::unordered_map<std::string, std::function<SetBool>> fs_set_bool;
	static inline std::unordered_map<std::string, std::function<SetFloatingPoint>> fs_set_floating_point;
	static inline std::unordered_map<std::string, std::function<SetIntegral>> fs_set_integral;
	static inline std::unordered_map<std::string, std::function<SetString>> fs_set_string;
	static inline std::unordered_map<std::string, std::function<Use>> fs_use;
	static inline std::unordered_map<std::string, std::function<IterateOver>> fs_iterate_over;

	static inline std::vector<std::string> order_members;
};

}

#endif
