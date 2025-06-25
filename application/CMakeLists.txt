project(Game)

# Get sources recursively
file(GLOB_RECURSE GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]pp")

# Create executable from sources
add_executable(${PROJECT_NAME} ${GAME_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/application$<0:>)

# Include headers from this folder
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link engine library
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)