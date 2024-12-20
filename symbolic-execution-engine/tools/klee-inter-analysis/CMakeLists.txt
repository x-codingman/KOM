add_executable(klee-inter-analysis
  main.cpp
)

set(KLEE_LIBS
  kleeCore
)

target_link_libraries(klee-inter-analysis ${KLEE_LIBS})

install(TARGETS klee-inter-analysis RUNTIME DESTINATION bin)

# The KLEE binary depends on the runtimes
add_dependencies(klee-inter-analysis BuildKLEERuntimes)