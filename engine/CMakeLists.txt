project(Engine)

# Get sources recursively
file(GLOB_RECURSE ENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]pp")

# Create static library with sources
add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES})

# Include headers publicly
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})