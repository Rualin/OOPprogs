cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем библиотеку bitarray
add_library(circular_buffer CircularBuffer.cpp)

# Добавляем тестовое приложение
add_executable(circularbuffer_test CircularBuffer_test.cpp)

# Связываем тестовое приложение с библиотекой и GoogleTest
target_link_libraries(circularbuffer_test PRIVATE circular_buffer GTest::gtest_main)

# Находим тесты
include(GoogleTest)
gtest_discover_tests(circularbuffer_test)
