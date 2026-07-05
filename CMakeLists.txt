cmake_minimum_required(VERSION 3.23)
project(bored_c_programming_workspace C)


# generate debug information
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "BUILD TYPE:" FORCE)
endif()
add_compile_options(-g3)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_library(util_shared src/common/util.c)
target_include_directories(util_shared PUBLIC include)


# custom cat
add_executable(my_cat src/cat/my_cat.c src/cat/my_cat.h)
target_link_libraries(my_cat PRIVATE util_shared)

# custom grep
add_executable(my_grep src/grep/my_grep.c src/grep/my_grep.h)
target_link_libraries(my_grep PRIVATE util_shared)

# custom ls
add_executable(my_ls src/ls/my_ls.c src/ls/my_ls.h)
target_link_libraries(my_ls PRIVATE util_shared)

# custom wc
add_executable(my_wc src/wc/my_wc.c src/wc/my_wc.h)
target_link_libraries(my_wc PRIVATE util_shared)


# program debugging
include(${CMAKE_SOURCE_DIR}/cmake/testing.cmake)


# source code formatting
include(${CMAKE_SOURCE_DIR}/cmake/format.cmake)
enable_clang_format(util_shared)
enable_clang_format(my_cat)
enable_clang_format(my_ls)
enable_clang_format(my_grep)
