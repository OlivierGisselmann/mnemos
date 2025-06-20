project(Engine)

# Get sources recursively
file(GLOB_RECURSE ENGINE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]pp")
file(GLOB_RECURSE ENGINE_SOURCES_C "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]")

# Find OpenGL libraries
find_package(OpenGL REQUIRED)

# Create static library with sources
add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES} ${ENGINE_SOURCES_C})

if(UNIX)
    # Link XLib to the library
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${X11_LIBRARIES}
        X11::Xi
        OpenGL::GL OpenGL::GLX
    )
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        winmm.lib
        OpenGL::GL
    )
endif()

# Include headers publicly
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ../include
)