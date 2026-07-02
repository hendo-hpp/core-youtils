find_program(CLANG_FORMAT_BIN "clang-format")

function(enable_clang_format TARGET_NAME)
    if (NOT CLANG_FORMAT_BIN)
        message(WARNING "clang-format executable not found.")
        return()
    endif()

    if(NOT TARGET format)
        add_custom_target(format)
    endif()

    get_target_property(TARGET_SOURCES ${TARGET_NAME} SOURCES)
    
    set(TARGET_NAME_FORMAT "${TARGET_NAME}_format")

    add_custom_target(${TARGET_NAME_FORMAT}
        COMMAND ${CLANG_FORMAT_BIN} -i ${TARGET_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Formatting ${TARGET_NAME} sources"
        VERBATIM
    )

    add_dependencies(format ${TARGET_NAME_FORMAT})
endfunction()