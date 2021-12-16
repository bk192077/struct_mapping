cmake_minimum_required(VERSION 3.5)
 
project(struct_mapping LANGUAGES CXX)

set(LIB_MAJOR_VERSION "0")
set(LIB_MINOR_VERSION "6")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions("-fno-limit-debug-info")
endif()

set(WARNINGS "")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

	set(WARNINGS "${WARNINGS} -Weverything")
	set(WARNINGS "${WARNINGS} -Wno-c++98-compat-pedantic")
	set(WARNINGS "${WARNINGS} -Wno-c++98-compat")
	set(WARNINGS "${WARNINGS} -Wno-padded")
	set(WARNINGS "${WARNINGS} -Wno-global-constructors")
	set(WARNINGS "${WARNINGS} -Wno-exit-time-destructors")
	set(WARNINGS "${WARNINGS} -Wno-newline-eof")
	set(WARNINGS "${WARNINGS} -Wno-weak-vtables")
	set(WARNINGS "${WARNINGS} -Wno-unused-member-function")
	set(WARNINGS "${WARNINGS} -Wno-ctad-maybe-unsupported")
	set(WARNINGS "${WARNINGS} -Wno-undef")
	set(WARNINGS "${WARNINGS} -Wno-double-promotion")
	set(WARNINGS "${WARNINGS} -Wno-switch-enum")

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
	set(WARNINGS "${WARNINGS} -Wno-sign-compare")
	set(WARNINGS "${WARNINGS} -Wno-stringop-overflow")
	set(WARNINGS "${WARNINGS} -Wno-array-bounds")

endif()

set(TEMPLATE_BACKTRACE_LIMIT "-ftemplate-backtrace-limit=0")

set(CMAKE_CXX_FLAGS "${WARNINGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TEMPLATE_BACKTRACE_LIMIT}")

set(CMAKE_CXX_EXTENSIONS false)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

option(BUILD_EXAMPLES "Build struct_mapping examples." ON)
option(BUILD_TESTS "Build struct_mapping tests." ON)
option(DEBUG_OUTPUT "Enable debug output" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(BUILD_EXAMPLES)
	add_subdirectory(example)
endif()

if(BUILD_TESTS AND (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))
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
