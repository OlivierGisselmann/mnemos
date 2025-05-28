project(Engine)

# Get sources recursively
file(GLOB_RECURSE ENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]pp")

# Create static library with sources
add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES})

if(UNIX)
    # Link XLib to the library
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${X11_LIBRARIES})
endif()

# Include headers publicly
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})