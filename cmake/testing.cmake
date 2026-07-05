add_custom_target(valgrind_wc
    COMMAND -valgrind --leak-check=full --track-origins=yes ./my_wc -o ../CMakeLists.txt
    DEPENDS my_wc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)