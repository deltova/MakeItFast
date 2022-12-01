SET(TEST "test")
add_custom_command(OUTPUT ${TEST} 
    COMMAND "/bin/bash" "-c" "LD_PRELOAD=../build/libTwitter.so python run.py"
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
                   DEPENDS ${TWITTER})
add_custom_target(check 
                  DEPENDS ${TEST})
