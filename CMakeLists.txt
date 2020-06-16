cmake_minimum_required(VERSION 3.5)
 
project(struct_mapping LANGUAGES CXX)

set(LIB_MAJOR_VERSION "0")
set(LIB_MINOR_VERSION "2")
set(LIB_PATCH_VERSION "1")
set(LIB_VERSION "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

set(WARNINGS "")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")

	set(WARNINGS "${WARNINGS} -Weverything")
	set(WARNINGS "${WARNINGS} -Wno-c++98-compat-pedantic")
	set(WARNINGS "${WARNINGS} -Wno-c++98-compat")
	set(WARNINGS "${WARNINGS} -Wno-padded")
	set(WARNINGS "${WARNINGS} -Wno-global-constructors")
	set(WARNINGS "${WARNINGS} -Wno-exit-time-destructors")
	set(WARNINGS "${WARNINGS} -Wno-weak-vtables")
	set(WARNINGS "${WARNINGS} -Wno-unused-member-function")
	set(WARNINGS "${WARNINGS} -Wno-ctad-maybe-unsupported")
	set(WARNINGS "${WARNINGS} -Wno-undef")
	set(WARNINGS "${WARNINGS} -Wno-double-promotion")

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

	set(WARNINGS "${WARNINGS} -Wpedantic")
	set(WARNINGS "${WARNINGS} -Wall")
	set(WARNINGS "${WARNINGS} -Wextra")
	set(WARNINGS "${WARNINGS} -Wshadow")
	set(WARNINGS "${WARNINGS} -Wnon-virtual-dtor")
	set(WARNINGS "${WARNINGS} -Wold-style-cast")
	set(WARNINGS "${WARNINGS} -Wcast-align")
	set(WARNINGS "${WARNINGS} -Wunused")
	set(WARNINGS "${WARNINGS} -Woverloaded-virtual")
	set(WARNINGS "${WARNINGS} -Wconversion")
	set(WARNINGS "${WARNINGS} -Wsign-conversion")
	set(WARNINGS "${WARNINGS} -Wnull-dereference")
	set(WARNINGS "${WARNINGS} -Wformat=2")
	set(WARNINGS "${WARNINGS} -Wduplicated-cond")
	set(WARNINGS "${WARNINGS} -Wduplicated-branches")
	set(WARNINGS "${WARNINGS} -Wlogical-op")

endif()

set(CMAKE_CXX_FLAGS "${WARNINGS}")
set(CMAKE_CXX_EXTENSIONS false)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

option(STRUCT_MAPPING_BUILD_EXAMPLES "Build struct_mapping examples." ON)
option(STRUCT_MAPPING_BUILD_TESTS "Build struct_mapping tests." ON)
option(STRUCT_MAPPING_DEBUG "Enable debug output" OFF)

sat(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(STRUCT_MAPPING_BUILD_EXAMPLES)
	add_subdirectory(example)
endif()

if(STRUCT_MAPPING_BUILD_TESTS AND (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))
	enable_testing()
	add_subdirectory(test)
endif()

set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "")
set(DOC_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/doc/${PROJECT_NAME}" CACHE PATH "")

install(FILES readme.md readme_ru.md
	DESTINATION "${DOC_INSTALL_DIR}"
	COMPONENT doc)

install(DIRECTORY include/struct_mapping
	DESTINATION "${INCLUDE_INSTALL_DIR}"
	COMPONENT dev)

install(DIRECTORY example/
	DESTINATION "${DOC_INSTALL_DIR}/examples"
	COMPONENT examples
	PATTERN "CMakeLists.txt" EXCLUDE)
