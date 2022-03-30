cmake_minimum_required(VERSION 3.21)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers src/main.cpp)

target_compile_options(ft_containers PUBLIC -Wall -Wextra -Werror)

target_include_directories(ft_containers PUBLIC ${CMAKE_SOURCE_DIR}/includes)
