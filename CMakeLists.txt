cmake_minimum_required(VERSION 2.8)

project(Calculator)

#set(CMAKE_GENERATOR "MinGW Makefiles")

set(SOURCE_EXE main.cpp Calculator.cpp Calculator.hpp)		# Установка переменной со списком исходников для исполняемого файла
set(TEST_EXE Tests.cpp Calculator.cpp Calculator.hpp)
#set(HEADERS_LIB catch.hpp)

#set(SOURCE_LIB foo.cpp)			# То же самое, но для библиотеки

#add_library(catch INTERFACE)
#target_include_directories(catch INTERFACE .)

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main
add_executable(tests ${TEST_EXE})

#target_link_libraries(test INTERFACE catch)		# Линковка программы с библиотекой