add_executable(tests Tests.cpp catch.hpp ${CMAKE_CURRENT_SOURCE_DIR}/../src/Calculator.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include/Calculator.hpp)

target_include_directories(tests
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
  )

add_test(
  NAME
    test
  COMMAND
    $<TARGET_FILE:tests>
  )