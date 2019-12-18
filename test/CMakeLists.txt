cmake_minimum_required(VERSION 3.0.2)

project(ebsinit_test C)

function(my_add_test name)
    add_executable(${name} ${name}.c)
    target_link_libraries(${name} aio)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

my_add_test(ebsinit_alloc_test)
my_add_test(ebsinit_setup_test)
my_add_test(ebsinit_alignment_offset_test)
my_add_test(ebsinit_max_no_test)
my_add_test(ebsinit_do_test)
my_add_test(ebsinit_core_test)
