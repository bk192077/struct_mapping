#ifndef STRUCT_MAPPING_DEBUG_H
#define STRUCT_MAPPING_DEBUG_H

namespace struct_mapping {

#ifdef STRUCT_MAPPING_DEBUG
	constexpr bool debug = true;
#else
	constexpr bool debug = false;
#endif

}

#endif

