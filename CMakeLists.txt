cmake_minimum_required(VERSION 3.14)
project(StudentManagementSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build unit tests" ON)

# Main executable
add_executable(student_system
    src/main.cpp
    src/Student.cpp
    src/StudentManager.cpp
    include/Student.h
    include/StudentManager.h
)

target_include_directories(student_system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Testing
if(BUILD_TESTING)
    enable_testing()
    
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)
    
    add_executable(student_system_tests
        tests/StudentTests.cpp
        tests/StudentManagerTests.cpp
        src/Student.cpp
        src/StudentManager.cpp
    )
    
    target_include_directories(student_system_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    target_link_libraries(student_system_tests
        GTest::gtest_main
        GTest::gmock_main
    )
    
    include(GoogleTest)
    gtest_discover_tests(student_system_tests)
endif()
