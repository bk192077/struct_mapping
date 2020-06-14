#ifndef STRUCT_MAPPING_FS_H
#define STRUCT_MAPPING_FS_H

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

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

class Fs_iterate_over {
public:
	using SetBool = void(std::string const &, bool);
	using SetIntegral = void(std::string const &, long long);
	using SetFloatingPoint = void(std::string const &, double);
	using SetString = void(std::string const &, std::string const &);
	using StartStruct = void(std::string const &);
	using EndStruct = void();
	using StartArray = void(std::string const &);
	using EndArray = void();

	static inline std::function<SetBool> set_bool;
	static inline std::function<SetIntegral> set_integral;
	static inline std::function<SetFloatingPoint> set_floating_point;
	static inline std::function<SetString> set_string;
	static inline std::function<StartStruct> start_struct;
	static inline std::function<EndStruct> end_struct;
	static inline std::function<StartArray> start_array;
	static inline std::function<EndArray> end_array;
};

template<typename T>
class Fs_iterate_over_fields {
public:
	using IterateOver = std::function<void(T&)>;
	static void add(std::string const & name, IterateOver f) {
		if (names.find(name) == names.end()) {
			names.insert(name);
			fs.push_back(f);
		}
	}

	static inline std::unordered_set<std::string> names;
	static inline std::vector<IterateOver> fs;
};

}

#endif
