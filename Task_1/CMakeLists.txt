cmake_minimum_required(VERSION 3.10)
project(MyProject)
#set(CMAKE_CXX_CPPLINT "cpplint") СМЕРТНЫЙ ГРЕХ


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(finalt1 InputOutput.cpp MemoryWork.cpp ProductManagement.cpp Task1.cpp)

option(USE_ASAN "Enable AddressSanitizer" ON)
option(USE_TSAN "Enable ThreadSanitizer" OFF)

if (USE_ASAN)
    message(STATUS "AddressSanitizer enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()

if (USE_TSAN)
    message(STATUS "ThreadSanitizer enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fno-omit-frame-pointer -g")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=thread")
endif()
