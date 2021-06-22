#ifndef STRUCT_MAPPING_ITERATE_OVER_H
#define STRUCT_MAPPING_ITERATE_OVER_H

#include <functional>
#include <string>

namespace struct_mapping::detail
{

class IterateOver
{
public:
	template<typename T>
	using Set = void(const std::string&, const T&);

	using SetNull = void(const std::string&);
	using StartStruct = void(const std::string&);
	using EndStruct = void();
	using StartArray = void(const std::string&);
	using EndArray = void();

	template<typename T>
	static inline std::function<Set<T>> set;
	
	static inline std::function<SetNull> set_null;
	static inline std::function<StartStruct> start_struct;
	static inline std::function<EndStruct> end_struct;
	static inline std::function<StartArray> start_array;
	static inline std::function<EndArray> end_array;
};

} // struct_mapping::detail

#endif
