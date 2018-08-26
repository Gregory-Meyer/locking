cmake_minimum_required(VERSION 3.8)

project(locking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

option(LOCKING_BUILD_BENCHMARKS "build benchmarks for locking" OFF)

if(LOCKING_BUILD_BENCHMARKS)
    find_package(Threads REQUIRED)

    find_package(benchmark REQUIRED)
    include_directories(${benchmark_INCLUDE_DIRS})

    add_executable(bench bench/main.cpp bench/adaptive_mutex.cpp
                         bench/mutex.cpp bench/spinlock.cpp)
    target_link_libraries(bench benchmark benchmark_main Threads::Threads)
endif()
