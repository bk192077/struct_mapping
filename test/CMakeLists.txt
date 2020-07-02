set(TARGET unittest)

find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_Add(
	googletest
	URL https://github.com/google/googletest/archive/master.zip
	PREFIX ${CMAKE_SOURCE_DIR}/thirdparty/gooletest
	DOWNLOAD_NO_PROGRESS true
	INSTALL_COMMAND ""
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

set(GMOCK_INCLUDE_DIRS "${SOURCE_DIR}/googlemock/include")
set(GMOCK_LIBRARY_DIRS "${BINARY_DIR}/lib")

add_library(gmock IMPORTED STATIC)
add_dependencies(gmock googletest)
set_target_properties(gmock PROPERTIES
	"IMPORTED_LOCATION" "${GMOCK_LIBRARY_DIRS}/libgmock.a"
	"INTERFACE_LINK_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

set(TEST_SOURCES
	main.cpp
	option_bounds.cpp
	option_default.cpp
	option_not_empty.cpp
	parser.cpp
	map_json_to_struct.cpp
	map_struct_to_json.cpp
)

add_executable(${TARGET} ${TEST_SOURCES})

if(STRUCT_MAPPING_DEBUG)
	target_compile_definitions(${TARGET} PRIVATE STRUCT_MAPPING_DEBUG)
endif()

target_compile_features(${TARGET} PRIVATE cxx_std_17)

target_include_directories(${TARGET} PRIVATE SYSTEM
	${CMAKE_SOURCE_DIR}/include
	${GTEST_INCLUDE_DIRS}
)

target_link_libraries(${TARGET}
	gmock
	gtest
)

add_test(
	NAME ${TARGET}
	COMMAND ${TARGET})
