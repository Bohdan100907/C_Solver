cmake_minimum_required(VERSION 3.16)
project(MiniAI C)

enable_testing()

add_library(miniai_ml STATIC
    src/ml/loss/clip_probability.c
    src/ml/loss/binary_cross_entropy.c
)
target_include_directories(miniai_ml PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
if(UNIX)
    target_link_libraries(miniai_ml PUBLIC m)
endif()

add_executable(bce_value_tests tests/bce_value_tests.c)
target_link_libraries(bce_value_tests PRIVATE miniai_ml)
add_test(NAME bce_half_predictions COMMAND bce_value_tests half)
add_test(NAME bce_correct_predictions COMMAND bce_value_tests correct)
add_test(NAME bce_saturated_predictions COMMAND bce_value_tests saturated)
add_test(NAME bce_invalid_values COMMAND bce_value_tests invalid)
add_test(NAME bce_soft_targets COMMAND bce_value_tests soft)
