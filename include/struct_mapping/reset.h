#ifndef STRUCT_MAPPING_RESET_H
#define STRUCT_MAPPING_RESET_H

#include <unordered_set>

namespace struct_mapping::detail
{

class Reset
{
public:
	using ResetFunction = void(*)();

	static void reg(ResetFunction reset)
	{
		functions.insert(reset);
	}

	static void reset()
	{
		for (auto f : functions) f();
	}

private:
	static inline std::unordered_set<ResetFunction> functions;
};

} // struct_mapping::detail

#endif
