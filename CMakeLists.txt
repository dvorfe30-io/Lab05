cmake_minimum_required(VERSION 3.14)
project(lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" OFF)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB TEST_SOURCES tests/*.cpp)
    add_executable(lab05_tests ${TEST_SOURCES})
    
    target_include_directories(lab05_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)

    target_link_libraries(lab05_tests PRIVATE banking GTest::gtest_main GTest::gmock_main)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(lab05_tests PRIVATE --coverage)
        target_link_options(lab05_tests PRIVATE --coverage)
    endif()

    add_test(NAME lab05_tests COMMAND lab05_tests)
endif()
