cmake_minimum_required(VERSION 3.10)
project(fixed_source)

# Define the executable
find_package(ZLIB REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-sign-compare)
elseif (MSVC)
    add_compile_options(/W4)
endif()

# build gtkwave FST library
file(GLOB GTKWAVE_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/fstapi/gtkwave/*.c"
)
add_library(gtkwave STATIC ${GTKWAVE_SRCS})
target_include_directories(gtkwave PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fstapi)
target_link_libraries(gtkwave PUBLIC ZLIB::ZLIB lz4)

# build our FST library
# Collect cpp files (recursively) and split regular library sources vs tests (files ending with ".test.cpp")
file(GLOB_RECURSE FST_CPP_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/fstapi/fstcpp/*.cpp"
)

# Lists to populate
set(FSTAPI_SRCS "")
set(FSTAPI_TEST_SRCS "")

foreach(FP ${FST_CPP_FILES})
    # get the filename with extension, e.g. "Writer.test.cpp"
    get_filename_component(FNAME ${FP} NAME)
    if(FNAME MATCHES ".*\\.test\\.cpp$")
        list(APPEND FSTAPI_TEST_SRCS "${FP}")
    else()
        list(APPEND FSTAPI_SRCS "${FP}")
    endif()
endforeach()

# Create fstapi library from non-test sources
add_library(fstapi STATIC ${FSTAPI_SRCS})
target_include_directories(fstapi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fstapi)
target_link_libraries(fstapi PRIVATE ZLIB::ZLIB lz4)

# Build unittest targets for each *.test.cpp and register with CTest
enable_testing()
foreach(TEST_SRC ${FSTAPI_TEST_SRCS})
    get_filename_component(TEST_NAME_WE ${TEST_SRC} NAME_WE)
    # sanitize a valid CMake target name (replace dots with underscores)
    string(REPLACE "." "_" TEST_TARGET ${TEST_NAME_WE})
    add_executable(${TEST_TARGET} ${TEST_SRC})
    target_link_libraries(${TEST_TARGET} PRIVATE fstapi gtest gtest_main)
    add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
endforeach()

# Build integration tests
set(VERIALTOR_SHARE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare/*.cpp")
file(GLOB BENCHMARK_NAME_LIST
    "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/list/*"
)
foreach(flong ${BENCHMARK_NAME_LIST})
    get_filename_component(f ${flong} NAME)

    # Build target ${f} testbench
    file(GLOB_RECURSE TEST_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/list/${f}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/benchmark/verilatorshare/*.cpp"
    )

    add_executable(${f}         ${TEST_SRCS})
    add_executable(${f}_gtkwave ${TEST_SRCS})

    target_include_directories(
        ${f}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/list/${f}/fixed
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/verilatorshare
    )
    target_include_directories(
        ${f}_gtkwave
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/list/${f}/fixed
        ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/verilatorshare
    )

    target_link_libraries(${f}         PRIVATE fstapi ZLIB::ZLIB lz4)
    target_link_libraries(${f}_gtkwave PRIVATE gtkwave ZLIB::ZLIB lz4)
endforeach()

# copy file for bench2 running data
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/list/bench2/firmware
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
