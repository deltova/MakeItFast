CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
SET(PACKAGE_NAME "Twitter")
SET(TWITTER "Twitter")
set(CMAKE_CXX_STANDARD 17)
PROJECT(${TWITTER} CXX)

add_compile_options("-std=c++17" "-pedantic" "-Wall" "-Wextra")

set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${TWITTER} SHARED src/twitter.cc)

#Generate bindings for the library
execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
message("CPYY_MODULE_PATH: " ${CPPYY_MODULE_PATH})
list(INSERT CMAKE_MODULE_PATH 0 ${CPPYY_MODULE_PATH})
find_package(Cppyy)
cppyy_add_bindings(
    "twitwi" "0.0.1" "Clement" "clementmagnard3@gmail.com"
    LANGUAGE_STANDARD "17"
    GENERATE_OPTIONS ""
    INCLUDE_DIRS    ${CMAKE_CURRENT_SOURCE_DIR}
    LINK_LIBRARIES 
    H_DIRS  ${CMAKE_CURRENT_SOURCE_DIR} 
    H_FILES "twitter.hh")

add_subdirectory(test)
add_subdirectory(bench)
