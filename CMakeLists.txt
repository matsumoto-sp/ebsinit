cmake_minimum_required(VERSION 3.0.2)
project(
    ebsinit
    VERSION 1.0.3
    LANGUAGES C
)
enable_testing()
set(CMAKE_C_FLAGS "-g -Wall")
add_definitions(-D_GNU_SOURCE -DEBSINIT_VERSION="${PROJECT_VERSION}")
add_subdirectory(test)
add_executable(ebsinit main.c)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_CONF_FILE "Doxyfile")
    set(DOXYGEN_CONF_PATH   ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONF_FILE})
    set(DOXYGEN_SOURCE_DIR ${CMAKE_SOURCE_DIR})
    set(DOXYGEN_TARGET "doc" )
    set(DOXYGEN_OUTPUT_PATH   ${CMAKE_CURRENT_BINARY_DIR}/doc)

    configure_file(${DOXYGEN_CONF_FILE}.in ${DOXYGEN_CONF_PATH})

    add_custom_target(${DOXYGEN_TARGET}
        COMMAND rm -fR ${DOXYGEN_OUTPUT_PATH}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF_PATH}
        DEPENDS  ${DOXYGEN_CONF_PATH})
else(DOXYGEN_FOUND)
        message (WARNING "doxygen binary couldn't be found")
endif(DOXYGEN_FOUND)

install(TARGETS ebsinit RUNTIME DESTINATION bin)

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${ebsinit_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${ebsinit_VERSION_MINOR}")
include (CPack)
