set(EXAMPLES
	array_like
	containers
	enumeration
	how_it_work
	in_struct_reg
	macro_reg
	map_like
	optional
	options
	options_default
	person
	simple
	struct
	struct_from_string
	struct_to_json
)

include_directories("../include")

foreach (example ${EXAMPLES})
	add_executable(${example} ${example}/${example}.cpp)
	target_compile_features(${example} PRIVATE cxx_std_17)
endforeach()

if(DEBUG_OUTPUT)
	add_definitions(-DDEBUG_OUTPUT)
endif()

add_custom_target(examples ALL DEPENDS ${EXAMPLES})
