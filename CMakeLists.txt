cmake_minimum_required(VERSION 2.8)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

add_subdirectory(src)

#set(CMAKE_GENERATOR "MinGW Makefiles")

set(INCLUDE_DIRECTORY include)
set(SOURCE_DIRECTORY src)
set(TESTS_DIRECTORY tests)

set(MAIN_SOURCES ${SOURCE_DIRECTORY}/main.cpp ${SOURCE_DIRECTORY}/Calculator.cpp ${INCLUDE_DIRECTORY}/Calculator.hpp)		# Установка переменной со списком исходников для исполняемого файла
set(TEST_SOURCES ${TESTS_DIRECTORY}/Tests.cpp ${SOURCE_DIRECTORY}/Calculator.cpp ${INCLUDE_DIRECTORY}/Calculator.hpp ${TESTS_DIRECTORY}/catch.hpp)

#target_link_libraries(test INTERFACE catch)		# Линковка программы с библиотекой

enable_testing()
add_subdirectory(tests)
