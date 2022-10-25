cmake_minimum_required(VERSION 3.0.0)
project(dames VERSION 0.1.0)

include(CTest)
enable_testing()
set(SRCS dames.c)
set(HEADERS dames.h)

add_library(damesLib ${SRCS} ${HEADERS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
