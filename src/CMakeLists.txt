cmake_minimum_required(VERSION 3.10)
project(fixed_source)

# Define the executable
find_package(ZLIB REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-sign-compare)
elseif (MSVC)
    add_compile_options(/W4)
endif()

# build gtkwave library
file(GLOB GTKWAVE_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/fstapi/gtkwave/*.c"
)
add_library(gtkwave STATIC ${GTKWAVE_SRCS})
target_include_directories(gtkwave PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fstapi)
target_link_libraries(gtkwave PUBLIC ZLIB::ZLIB lz4)

# build cpp fst library
file(GLOB FSTAPI_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/fstapi/fstcpp/*.cpp"
)
add_library(fstapi STATIC ${FSTAPI_SRCS})
target_include_directories(fstapi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fstapi)
target_link_libraries(fstapi PUBLIC ZLIB::ZLIB lz4)

# Build target simple testbench
file(GLOB_RECURSE SIMPLE_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/simple/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare/*.cpp"
)

add_executable(simple ${SIMPLE_SRCS})
target_include_directories(
    simple
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/simple/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare
)
target_link_libraries(simple PRIVATE fstapi ZLIB::ZLIB lz4)

add_executable(simple_gtkwave ${SIMPLE_SRCS})
target_include_directories(
    simple_gtkwave
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/simple/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare
)
target_link_libraries(simple_gtkwave PRIVATE gtkwave ZLIB::ZLIB lz4)

# Build target bench1, with cppfst and gtkwave variant
file(GLOB_RECURSE BENCH1_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/bench1/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare/*.cpp"
)

add_executable(bench1 ${BENCH1_SRCS})
target_include_directories(
    bench1
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bench1/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare
)
target_link_libraries(bench1 PRIVATE fstapi ZLIB::ZLIB lz4)

add_executable(bench1_gtkwave ${BENCH1_SRCS})
target_include_directories(
    bench1_gtkwave
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bench1/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare
)
target_link_libraries(bench1_gtkwave PRIVATE gtkwave ZLIB::ZLIB lz4)

# Build target benchmark2
file(GLOB_RECURSE BENCH2_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/bench2/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare/*.cpp"
)

add_executable(bench2 ${BENCH2_SRCS})
target_include_directories(
    bench2
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bench2/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare
)
target_link_libraries(bench2 PRIVATE fstapi ZLIB::ZLIB lz4)

add_executable(bench2_gtkwave ${BENCH2_SRCS})
target_include_directories(
    bench2_gtkwave
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bench2/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/verilatorshare
)
target_link_libraries(bench2_gtkwave PRIVATE ZLIB::ZLIB lz4 gtkwave)

# copy file for bench2 running data
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bench2/firmware
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Build unittest
enable_testing()
add_executable(WriterTest test/Writer_test.cpp)
target_link_libraries(WriterTest fstapi gtest gtest_main)
add_test(WriterTest WriterTest)