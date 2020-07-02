set(EXAMPLES
	array
	containers
	how_it_work
	in_struct_reg
	macro_reg
	map
	options
	person
	simple
	struct
	struct_to_json
)

include_directories("../include")

foreach (example ${EXAMPLES})
	add_executable(${example} ${example}/${example}.cpp)
	target_compile_features(${example} PRIVATE cxx_std_17)
endforeach()

if(STRUCT_MAPPING_DEBUG)
	add_definitions(-DSTRUCT_MAPPING_DEBUG)
endif()

add_custom_target(examples ALL DEPENDS ${EXAMPLES})
