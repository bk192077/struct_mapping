set(TARGET unittest)

find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_Add(
	googletest
	URL https://github.com/google/googletest/archive/refs/heads/main.zip
	PREFIX ${CMAKE_SOURCE_DIR}/thirdparty/gooletest
	DOWNLOAD_NO_PROGRESS true
	INSTALL_COMMAND ""
	CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
)

ExternalProject_Get_property(googletest SOURCE_DIR BINARY_DIR)

set(GTEST_INCLUDE_DIRS "${SOURCE_DIR}/googletest/include")
set(GTEST_LIBRARY_DIRS "${BINARY_DIR}/lib")

add_library(gtest IMPORTED STATIC)
add_dependencies(gtest googletest)
set_target_properties(gtest PROPERTIES
	"IMPORTED_LOCATION" "${GTEST_LIBRARY_DIRS}/libgtest.a"
	"INTERFACE_LINK_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(gtest_main IMPORTED STATIC)
add_dependencies(gtest_main googletest)
set_target_properties(gtest_main PROPERTIES
	"IMPORTED_LOCATION" "${GTEST_LIBRARY_DIRS}/libgtest_main.a"
	"INTERFACE_LINK_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

set(GMOCK_INCLUDE_DIRS "${SOURCE_DIR}/googlemock/include")
set(GMOCK_LIBRARY_DIRS "${BINARY_DIR}/lib")

add_library(gmock IMPORTED STATIC)
add_dependencies(gmock googletest)
set_target_properties(gmock PROPERTIES
	"IMPORTED_LOCATION" "${GMOCK_LIBRARY_DIRS}/libgmock.a"
	"INTERFACE_LINK_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem${GTEST_INCLUDE_DIRS} -isystem${GMOCK_INCLUDE_DIRS}")

set(TEST_SOURCES
	option_bounds_test.cpp
	option_default_test.cpp
	option_not_empty_test.cpp
	option_required_test.cpp
	optional_test.cpp
	parser_test.cpp
	map_json_to_struct_test.cpp
	map_struct_to_json_test.cpp
)

add_executable(${TARGET} ${TEST_SOURCES})

if(DEBUG_OUTPUT)
	target_compile_definitions(${TARGET} PRIVATE DEBUG_OUTPUT)
endif()

target_compile_features(${TARGET} PRIVATE cxx_std_17)

target_include_directories(${TARGET} PRIVATE SYSTEM
	${CMAKE_SOURCE_DIR}/include
	${GTEST_INCLUDE_DIRS}
	${GMOCK_INCLUDE_DIRS}
)

target_link_libraries(${TARGET}
	gmock
	gtest
	gtest_main
)

add_test(
	NAME ${TARGET}
	COMMAND ${TARGET})
