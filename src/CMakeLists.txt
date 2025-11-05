cmake_minimum_required(VERSION 3.10)
project(fixed_source)

# Define the executable
find_package(ZLIB REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (MSVC)
    add_compile_options(/W4)
endif()

# Recursively find all .cpp (or .c) files
file(GLOB_RECURSE BENCH1_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/bench1/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fstapi/*.cpp"
#    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_executable(bench1 ${BENCH1_SRCS})
target_include_directories(
    bench1
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/bench1/fixed
    ${CMAKE_CURRENT_SOURCE_DIR}/fstapi
)
target_link_libraries(bench1 PRIVATE ZLIB::ZLIB lz4)
