cmake_minimum_required(VERSION 3.23)
project(bored_c_programming_workspace C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(util_shared src/common/util.c)
target_include_directories(util_shared PUBLIC include) # public since utils will need it to compile

# custom cat
add_executable(my_cat 
    src/cat/my_cat.c 
    src/cat/my_cat.h
)
target_link_libraries(my_cat PRIVATE util_shared)

# custom grep
add_executable(my_grep 
    src/grep/my_grep.c 
    src/grep/my_grep.h
)
target_link_libraries(my_grep PRIVATE util_shared)

# custom ls
add_executable(my_ls 
    src/ls/my_ls.c 
    src/ls/my_ls.h
)
target_link_libraries(my_ls PRIVATE util_shared)

# custom wc
add_executable(my_wc 
    src/wc/my_wc.c 
    src/wc/my_wc.h
)
target_link_libraries(my_wc PRIVATE util_shared)

include(${CMAKE_SOURCE_DIR}/cmake/format.cmake)
enable_clang_format(util_shared)
enable_clang_format(my_cat)
enable_clang_format(my_ls)
enable_clang_format(my_grep)
