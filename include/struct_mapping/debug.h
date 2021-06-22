#ifndef STRUCT_MAPPING_DEBUG_H
#define STRUCT_MAPPING_DEBUG_H

namespace struct_mapping
{

#ifdef DEBUG_OUTPUT
	constexpr bool debug = true;
#else
	constexpr bool debug = false;
#endif

} // struct_mapping

#endif

