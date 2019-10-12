find_package(benchmark REQUIRED)

set(BENCH_FILE ${CMAKE_SOURCE_DIR}/bench/bench.json)

add_executable(benchbin
  EXCLUDE_FROM_ALL
  main.cc
)

target_link_libraries(benchbin PRIVATE
  benchmark::benchmark
  ${TWITTER}
)

target_include_directories(benchbin PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

add_custom_target(bench benchbin DEPENDS benchbin COMMENT "Running benchs...")
