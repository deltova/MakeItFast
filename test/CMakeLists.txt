SET(TEST "test")
add_custom_command(OUTPUT ${TEST} 
                   COMMAND "python" "run.py"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
                   DEPENDS ${TWITTER} ${BINDINGS})
add_custom_target(
    check 
    DEPENDS ${TEST}
)
