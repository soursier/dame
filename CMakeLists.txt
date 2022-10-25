cmake_minimum_required(VERSION 3.0.0)
project(dames VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(lib)
add_executable(dames main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_link_libraries(dames damesLib)
