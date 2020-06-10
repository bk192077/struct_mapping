#ifndef STRUCT_MAPPING_MANAGED_STRUCT_H
#define STRUCT_MAPPING_MANAGED_STRUCT_H

#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "../debug.h"
#include "../exception.h"

namespace struct_mapping::managed {

template<typename F>
class Fs_set_field {
public:
	static void add(std::string const & name, F f) {
		if (fs.find(name) == fs.end()) fs[name] = f;
	}

	static inline std::unordered_map<std::string, F> fs;
};

template<typename F>
class Fs_set {
public:
	static void add(std::string const & name, F f) {
		if (fs.find(name) == fs.end()) fs[name] = f;
	}

	static inline std::unordered_map<std::string, F> fs;
};

template<typename F>
class Fs_use {
public:
	static void add(std::string const & name, F f) {
		if (fs.find(name) == fs.end()) fs[name] = f;
	}

	static inline std::unordered_map<std::string, F> fs;
};

template<typename F>
class Fs_release {
public:
	static void add(std::string const & name, F f) {
		if (fs.find(name) == fs.end()) fs[name] = f;
	}

	static inline std::unordered_map<std::string, F> fs;
};

}

#define MANAGED_STRING_Q5w6E7r8(v) MANAGED_STRING_Q5w6E7r8_M(v)
#define MANAGED_STRING_Q5w6E7r8_M(v) #v

#define BEGIN_MANAGED_STRUCT struct MANAGED_STRUCT_NAME {                                                                                                      \
	std::string used_field_name_Q5w6E7r8 = "";                                                                                                                   \
                                                                                                                                                               \
	void set(std::string const & field_name_Q5w6E7r8, bool value_Q5w6E7r8) {                                                                                     \
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: " << MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::set_bool: " <<            \
			field_name_Q5w6E7r8 << " : " << value_Q5w6E7r8 << std::endl;                                                                                             \
		if (used_field_name_Q5w6E7r8.empty()) {                                                                                                                    \
			if (auto it_Q5w6E7r8 = struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, bool)>>::fs.find(field_name_Q5w6E7r8);             \
				it_Q5w6E7r8 == struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, bool)>>::fs.end()) {                                     \
				throw struct_mapping::StructMappingException(                                                                                                          \
					std::string(MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::set(std::string const &, bool): unknown field name: ") + field_name_Q5w6E7r8);           \
			} else {                                                                                                                                                 \
				it_Q5w6E7r8->second(*this, value_Q5w6E7r8);                                                                                                            \
			}                                                                                                                                                        \
		} else {                                                                                                                                                   \
			struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, bool)>>                                                    \
				::fs[used_field_name_Q5w6E7r8](*this, field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                            \
		}                                                                                                                                                          \
	}                                                                                                                                                            \
                                                                                                                                                               \
	void set(std::string const & field_name_Q5w6E7r8, std::string const & value_Q5w6E7r8) {                                                                      \
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: " << MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::set_string: " <<          \
			field_name_Q5w6E7r8 << " : " << value_Q5w6E7r8 << std::endl;                                                                                             \
		if (used_field_name_Q5w6E7r8.empty()) {                                                                                                                    \
			if (auto it_Q5w6E7r8 = struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>                             \
				::fs.find(field_name_Q5w6E7r8);                                                                                                                        \
				it_Q5w6E7r8 == struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>::fs.end()) {                      \
				throw struct_mapping::StructMappingException(                                                                                                          \
					std::string(MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::set(std::string const &, std::string const &): unknown field name: ") +                  \
						field_name_Q5w6E7r8);                                                                                                                              \
			} else {                                                                                                                                                 \
				it_Q5w6E7r8->second(*this, value_Q5w6E7r8);                                                                                                            \
			}                                                                                                                                                        \
		} else {                                                                                                                                                   \
			struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, std::string const &)>>                                     \
				::fs[used_field_name_Q5w6E7r8](*this, field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                            \
		}                                                                                                                                                          \
	}                                                                                                                                                            \
	                                                                                                                                                             \
	void set(std::string const & field_name_Q5w6E7r8, long long value_Q5w6E7r8) {                                                                                \
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: " << MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME)  "::set_long_long: " <<      \
			field_name_Q5w6E7r8 << " : " << value_Q5w6E7r8 << std::endl;                                                                                             \
		if (used_field_name_Q5w6E7r8.empty()) {                                                                                                                    \
			if (auto it_Q5w6E7r8_ll = struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, long long)>>                                    \
				::fs.find(field_name_Q5w6E7r8);                                                                                                                        \
				it_Q5w6E7r8_ll != struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, long long)>>::fs.end()) {                             \
				it_Q5w6E7r8_ll->second(*this, value_Q5w6E7r8);                                                                                                         \
			} else if (auto it_Q5w6E7r8_d = struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, double)>>::                               \
				fs.find(field_name_Q5w6E7r8);                                                                                                                          \
				it_Q5w6E7r8_d != struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, double)>>::fs.end()) {                                 \
				it_Q5w6E7r8_d->second(*this, static_cast<double>(value_Q5w6E7r8));                                                                                     \
			} else {                                                                                                                                                 \
				throw struct_mapping::StructMappingException(                                                                                                          \
					std::string(MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::set(std::string const &, long long): unknown field name: ") + field_name_Q5w6E7r8);      \
			}                                                                                                                                                        \
		} else {                                                                                                                                                   \
			struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, long long)>>                                               \
				::fs[used_field_name_Q5w6E7r8](*this, field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                            \
		}                                                                                                                                                          \
	}                                                                                                                                                            \
                                                                                                                                                               \
	void set(std::string const & field_name_Q5w6E7r8, double value_Q5w6E7r8) {                                                                                   \
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: " << MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME)  "::set_double: " <<         \
			field_name_Q5w6E7r8 << " : " << value_Q5w6E7r8 << std::endl;                                                                                             \
		if (used_field_name_Q5w6E7r8.empty()) {                                                                                                                    \
			if (auto it_Q5w6E7r8_d = struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, double)>>                                        \
				::fs.find(field_name_Q5w6E7r8);                                                                                                                        \
				it_Q5w6E7r8_d != struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, double)>>::fs.end()) {                                 \
				it_Q5w6E7r8_d->second(*this, value_Q5w6E7r8);                                                                                                          \
			} else if (auto it_Q5w6E7r8_ll = struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, long long)>>                             \
				::fs.find(field_name_Q5w6E7r8);                                                                                                                        \
				it_Q5w6E7r8_ll != struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, long long)>>::fs.end()) {                             \
				it_Q5w6E7r8_ll->second(*this, static_cast<long long>(value_Q5w6E7r8));                                                                                 \
			} else {                                                                                                                                                 \
				throw struct_mapping::StructMappingException(                                                                                                          \
					std::string(MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::set(std::string const &, double): unknown field name: ") + field_name_Q5w6E7r8);         \
			}                                                                                                                                                        \
		} else {                                                                                                                                                   \
			struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, double)>>                                                  \
				::fs[used_field_name_Q5w6E7r8](*this, field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                            \
		}                                                                                                                                                          \
	}                                                                                                                                                            \
                                                                                                                                                               \
	void use(std::string const & field_name_Q5w6E7r8) {                                                                                                          \
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: " << MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME)  "::use: " <<                \
			field_name_Q5w6E7r8 << std::endl;                                                                                                                        \
		if (used_field_name_Q5w6E7r8.empty()) {                                                                                                                    \
			if (auto it_Q5w6E7r8 = struct_mapping::managed::Fs_use<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>                                   \
				::fs.find(field_name_Q5w6E7r8);                                                                                                                        \
				it_Q5w6E7r8 == struct_mapping::managed::Fs_use<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>::fs.end()) {                            \
				throw struct_mapping::StructMappingException(std::string(MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME) "::use: unknown field name: ") +                 \
					field_name_Q5w6E7r8);                                                                                                                                \
			}                                                                                                                                                        \
                                                                                                                                                               \
			used_field_name_Q5w6E7r8 = field_name_Q5w6E7r8;                                                                                                          \
		} else {                                                                                                                                                   \
			struct_mapping::managed::Fs_use<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>                                                          \
				::fs[used_field_name_Q5w6E7r8](*this, field_name_Q5w6E7r8);                                                                                            \
		}                                                                                                                                                          \
	}                                                                                                                                                            \
                                                                                                                                                               \
	bool release() {                                                                                                                                             \
		if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: " << MANAGED_STRING_Q5w6E7r8(MANAGED_STRUCT_NAME)  "::release:" << std::endl;  \
		if (used_field_name_Q5w6E7r8.empty()) return true;                                                                                                         \
		if (struct_mapping::managed::Fs_release<std::function<bool(MANAGED_STRUCT_NAME&)>>                                                                         \
			::fs[used_field_name_Q5w6E7r8](*this)) used_field_name_Q5w6E7r8.clear();                                                                                 \
		return false;                                                                                                                                              \
	}

#if defined(__clang__)

#define MANAGED_FIELD(FIELD_TYPE, FIELD_NAME) FIELD_TYPE FIELD_NAME =	[] {																								                                     \
	using value_type_Q5w6E7r8 =                                                                                                                                  \
		std::conditional_t<std::is_same_v<bool, FIELD_TYPE>, bool, 																			 									                                         \
			std::conditional_t<std::is_same_v<std::string, FIELD_TYPE>, std::string const &, 																			 								                   \
				std::conditional_t<std::is_floating_point_v<FIELD_TYPE>, double, long long>>>;                                                                         \
	struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, value_type_Q5w6E7r8)>>::add(                                                  \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, value_type_Q5w6E7r8 value_Q5w6E7r8) {                                                                                \
			FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                          \
			o_Q5w6E7r8.*p_Q5w6E7r8 = static_cast<FIELD_TYPE>(value_Q5w6E7r8);                                                                                        \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_field: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;         \
		});                                                                                                                                                        \
	using USING_FIELD_TYPE_Q5w6E7r8 = FIELD_TYPE;                                                                                                                \
	return USING_FIELD_TYPE_Q5w6E7r8{};                                                                                                                          \
}();

#define MANAGED_FIELD_STRUCT(FIELD_TYPE, FIELD_NAME) FIELD_TYPE FIELD_NAME = [] {                                                                              \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, bool)>>::add(                                                  \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, bool value_Q5w6E7r8) {                                                      \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_bool: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;          \
			FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                          \
			auto& pp_Q5w6E7r8 = o_Q5w6E7r8.*p_Q5w6E7r8;                                                                                                              \
			pp_Q5w6E7r8.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                                    \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, double)>>::add(                                                \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, double value_Q5w6E7r8) {                                                    \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_double: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;        \
			FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                          \
			auto& pp_Q5w6E7r8 = o_Q5w6E7r8.*p_Q5w6E7r8;                                                                                                              \
			pp_Q5w6E7r8.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                                    \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, long long)>>::add(                                             \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, long long value_Q5w6E7r8) {                                                 \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_long_long: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;     \
			FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                          \
			auto& pp_Q5w6E7r8 = o_Q5w6E7r8.*p_Q5w6E7r8;                                                                                                              \
			pp_Q5w6E7r8.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                                    \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, std::string const &)>>::add(                                   \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, std::string const & value_Q5w6E7r8) {                                       \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_string: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;        \
			FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                          \
			auto& pp_Q5w6E7r8 = o_Q5w6E7r8.*p_Q5w6E7r8;                                                                                                              \
			pp_Q5w6E7r8.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                                    \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_use<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>::add(                                                        \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & name_Q5w6E7r8) {                                                                                 \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: use: " << #FIELD_NAME << " : " << name_Q5w6E7r8 << std::endl;                \
			FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                          \
			auto& pp_Q5w6E7r8 = o_Q5w6E7r8.*p_Q5w6E7r8;                                                                                                              \
			pp_Q5w6E7r8.use(name_Q5w6E7r8);                                                                                                                          \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_release<std::function<bool(MANAGED_STRUCT_NAME&)>>::add(                                                                         \
		#FIELD_NAME,                                                                                                                                               \
			[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8) {                                                                                                                  \
				if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: release: " << #FIELD_NAME << std::endl;                                    \
				FIELD_TYPE MANAGED_STRUCT_NAME::*p_Q5w6E7r8 = &MANAGED_STRUCT_NAME::FIELD_NAME;                                                                        \
				auto& pp_Q5w6E7r8 = o_Q5w6E7r8.*p_Q5w6E7r8;                                                                                                            \
				return pp_Q5w6E7r8.release();                                                                                                                          \
			});                                                                                                                                                      \
	using USING_FIELD_TYPE_Q5w6E7r8 = FIELD_TYPE;                                                                                                                \
	return USING_FIELD_TYPE_Q5w6E7r8{};                                                                                                                          \
}();

#else

#define MANAGED_FIELD(FIELD_TYPE, FIELD_NAME) FIELD_TYPE FIELD_NAME =	[] {																								                                     \
	using value_type_Q5w6E7r8 =                                                                                                                                  \
		std::conditional_t<std::is_same_v<bool, FIELD_TYPE>, bool, 																			 									                                         \
			std::conditional_t<std::is_same_v<std::string, FIELD_TYPE>, std::string const &, 																			 								                   \
				std::conditional_t<std::is_floating_point_v<FIELD_TYPE>, double, long long>>>;                                                                         \
	struct_mapping::managed::Fs_set_field<std::function<void(MANAGED_STRUCT_NAME&, value_type_Q5w6E7r8)>>::add(                                                  \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, value_type_Q5w6E7r8 value_Q5w6E7r8) {                                                                                \
			o_Q5w6E7r8.FIELD_NAME = static_cast<FIELD_TYPE>(value_Q5w6E7r8);													                                            									 \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_field: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;         \
		});                                                                                                                                                        \
	using USING_FIELD_TYPE_Q5w6E7r8 = FIELD_TYPE;                                                                                                                \
	return USING_FIELD_TYPE_Q5w6E7r8{};                                                                                                                          \
}();

#define MANAGED_FIELD_STRUCT(FIELD_TYPE, FIELD_NAME) FIELD_TYPE FIELD_NAME = [] {                                                                              \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, bool)>>::add(                                                  \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, bool value_Q5w6E7r8) {                                                      \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_bool: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;          \
			o_Q5w6E7r8.FIELD_NAME.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                          \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, double)>>::add(                                                \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, double value_Q5w6E7r8) {                                                    \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_double: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;        \
			o_Q5w6E7r8.FIELD_NAME.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                          \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, long long)>>::add(                                             \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, long long value_Q5w6E7r8) {                                                 \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_long_long: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;     \
			o_Q5w6E7r8.FIELD_NAME.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                          \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_set<std::function<void(MANAGED_STRUCT_NAME&, std::string const &, std::string const &)>>::add(                                   \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & field_name_Q5w6E7r8, std::string const & value_Q5w6E7r8) {                                       \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: set_string: " << #FIELD_NAME << " : " << value_Q5w6E7r8 << std::endl;        \
			o_Q5w6E7r8.FIELD_NAME.set(field_name_Q5w6E7r8, value_Q5w6E7r8);                                                                                          \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_use<std::function<void(MANAGED_STRUCT_NAME&, std::string const &)>>::add(                                                        \
		#FIELD_NAME,                                                                                                                                               \
		[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8, std::string const & name_Q5w6E7r8) {                                                                                 \
			if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: use: " << #FIELD_NAME << " : " << name_Q5w6E7r8 << std::endl;                \
			o_Q5w6E7r8.FIELD_NAME.use(name_Q5w6E7r8);                                                                                                                \
		});                                                                                                                                                        \
	struct_mapping::managed::Fs_release<std::function<bool(MANAGED_STRUCT_NAME&)>>::add(                                                                         \
		#FIELD_NAME,                                                                                                                                               \
			[] (MANAGED_STRUCT_NAME & o_Q5w6E7r8) {                                                                                                                  \
				if constexpr (struct_mapping::debug_Q5w6E7r8) std::cout << "struct_mapping: release: " << #FIELD_NAME << std::endl;                                    \
				return o_Q5w6E7r8.FIELD_NAME.release();                                                                                                                \
			});                                                                                                                                                      \
	using USING_FIELD_TYPE_Q5w6E7r8 = FIELD_TYPE;                                                                                                                \
	return USING_FIELD_TYPE_Q5w6E7r8{};                                                                                                                          \
}();

#endif

#define END_MANAGED_STRUCT };

#endif

