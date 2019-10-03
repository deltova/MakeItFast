SET(BINDINGS "${CMAKE_CURRENT_SOURCE_DIR}/build")
add_custom_command(OUTPUT ${BINDINGS} 
                   COMMAND "python" "setup.py" "build"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
                   DEPENDS ${TWITTER})
add_custom_target(
    build-bindings ALL
    DEPENDS ${BINDINGS}
)
