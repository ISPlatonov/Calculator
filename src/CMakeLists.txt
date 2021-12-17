add_executable(main main.cpp Calculator.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_include_directories(main
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  )