cmake_minimum_required(VERSION 3.16)

project(MiniAI VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(CTest)

add_library(miniai
    src/math/statistics.c
)

target_include_directories(miniai
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(BUILD_TESTING)
    add_executable(lab03_b6_tests tests/lab03_b6_tests.c)
    target_link_libraries(lab03_b6_tests PRIVATE miniai)
    add_test(NAME lab03_b6_tests COMMAND lab03_b6_tests)
endif()
