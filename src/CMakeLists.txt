cmake_minimum_required(VERSION 3.10)
project(fstcpp VERSION 1.0.0)

# Find dependencies
find_package(ZLIB REQUIRED)
find_package(GTest REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-sign-compare)
elseif (MSVC)
    add_compile_options(/W4)
endif()

# Include current source directory for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#######################################
# build our FST library
#######################################

# Collect cpp files (recursively) and split regular library sources vs tests (files ending with ".test.cpp")
file(GLOB_RECURSE FST_CPP_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/fstcpp/*.cpp"
)

# Lists to populate
# We have 2 lists
# 1. FSTCPP_SRCS - all non-test source files
# 2. FSTCPP_TEST_MAIN - all test source files that will be compiled into executables and run by ctest (ending with .test.cpp)
set(FSTCPP_SRCS "")
set(FSTCPP_TEST_MAIN "")

foreach(FP ${FST_CPP_FILES})
    # get the filename with extension, e.g. "Writer.test.cpp"
    get_filename_component(FNAME ${FP} NAME)
    if(FNAME MATCHES ".*\\.test\\.cpp$")
        list(APPEND FSTCPP_TEST_MAIN "${FP}")
    else()
        list(APPEND FSTCPP_SRCS "${FP}")
    endif()
endforeach()

# Create fstcpp library from non-test sources
add_library(fstcpp STATIC ${FSTCPP_SRCS})
target_include_directories(fstcpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(fstcpp PUBLIC ZLIB::ZLIB lz4)
# Core library shall only be built with C++14
set_target_properties(fstcpp PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES)

# Build unittest targets for each *.test.cpp and register with CTest
enable_testing()
foreach(TEST_SRC ${FSTCPP_TEST_MAIN})
    get_filename_component(TEST_NAME_WE ${TEST_SRC} NAME_WE)
    # sanitize a valid CMake target name (replace dots with underscores)
    string(REPLACE "." "_" TEST_TARGET ${TEST_NAME_WE})
    add_executable(${TEST_TARGET} ${TEST_SRC})
    target_link_libraries(${TEST_TARGET} PRIVATE fstcpp GTest::GTest GTest::Main)
    add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
endforeach()

#######################################
# Build the integration tests
#######################################
file(GLOB_RECURSE INTEGRATION_TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/integration_test/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/integration_test)
add_executable(integration_test_c ${INTEGRATION_TEST_SRCS} gtkwave/fstapi.c)
add_executable(integration_test_cpp ${INTEGRATION_TEST_SRCS} gtkwave/fstapi.cpp)

target_link_libraries(integration_test_c PRIVATE fstcpp)
target_link_libraries(integration_test_cpp PRIVATE fstcpp)

add_test(NAME integration_test_cpp COMMAND integration_test_cpp dump_cpp.fst)
add_test(NAME integration_test_c COMMAND integration_test_c dump_c.fst)
