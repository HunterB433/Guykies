# =============================================================================
# CMakeLists.txt For a Godot Extension
# =============================================================================
cmake_minimum_required(VERSION 3.21)

# --- Dependancies ---
include(FetchContent)
FetchContent_Declare(
    godot-cpp
    GIT_REPOSITORY  https://github.com/godotengine/godot-cpp.git
    GIT_TAG         4.4
    GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(godot-cpp)

# --- Project def ---
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH MY_PARENT_DIR)
get_filename_component(PROJECT_NAME ${MY_PARENT_DIR} NAME)
string(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})
project(${PROJECT_NAME} LANGUAGES C CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add .debug suffix for debug version
set(CMAKE_DEBUG_POSTFIX .debug)

# Generate compile_commands.json, useful for code analysis
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_COLOR_MAKEFILE ON)

# Define build output folders
 set(BUILD_PATH ${CMAKE_SOURCE_DIR}/../godot/bin)
 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
 set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}") 

# Retrieve source files and headers
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h*")

#Create the library
#add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME} SHARED ${SOURCES} )

#Link our library to godot-cpp
target_link_libraries(${PROJECT_NAME} PRIVATE godot-cpp)

# associate headers 
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})

# Add src folder to include path
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#enable link time optimization for release
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE ON
)

set(GDEXTENSION_CONTENT
"[configuration]
entry_symbol = \"library_init\" 
compatibility_minimum = \"4.2\"
reloadable = true

[libraries]
windows.debug.x86_64 = \"res://bin/${PROJECT_NAME}.debug.dll\"
windows.release.x86_64 = \"res://bin/${PROJECT_NAME}.dll\"
")

# Generate the file
file(CONFIGURE
    OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../godot/bin/library.gdextension"
    CONTENT "${GDEXTENSION_CONTENT}"
    NEWLINE_STYLE UNIX
)
