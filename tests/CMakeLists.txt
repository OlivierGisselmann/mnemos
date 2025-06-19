project(Tests)

# Get GoogleTest library
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Prevent overriding parent's compiler and linker settings
if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Enable GoogleTest library
FetchContent_MakeAvailable(googletest)

message(STATUS "Building tests...")

# Enable GoogleTest
enable_testing()

# Create the executable with selected files
add_executable(${PROJECT_NAME}
    core/filesystem_test.cpp
    core/timer_test.cpp
    math/matrix_test.cpp
    math/vector_test.cpp
    platform/inputsystem_test.cpp
    platform/types_test.cpp
    platform/window_test.cpp
)

# Link engine library
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gmock GTest::gtest_main Engine)

# Let google discover tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})