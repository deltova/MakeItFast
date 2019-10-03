CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
SET(PACKAGE_NAME "Twitter")
SET(TWITTER "Twitter")
set(CMAKE_CXX_STANDARD 17)
PROJECT(${TWITTER} CXX)

add_library(${TWITTER} SHARED src/twitter.cc)
add_compile_options("-std=c++17" "-pedantic" "-Wall" "-Wextra")

add_executable(${TWITTER}_test test/test.cc)
target_include_directories(${TWITTER}_test PUBLIC src)
target_link_libraries(${TWITTER}_test PUBLIC ${TWITTER})
add_subdirectory(wrapper)
