# EOGLL Examples

add_executable(eogll_ex_dragon dragon.c)
target_link_libraries(eogll_ex_dragon eogll)


# The example runner is a basic program that asks the user which example to run and runs it
# it depends on the examples being built
configure_file(example_runner.c.in ${CMAKE_CURRENT_BINARY_DIR}/example_runner.c)
add_executable(eogll_example_runner ${CMAKE_CURRENT_BINARY_DIR}/example_runner.c)
target_include_directories(eogll_example_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(eogll_example_runner eogll_ex_dragon)


