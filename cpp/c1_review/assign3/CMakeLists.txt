cmake_minimum_required(VERSION 3.22)

project(Assign3 VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add compile flags for better debugging and warnings
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# The steps to create the executable and library:
# 1. Set the executable and library names, so they can be reused as the variable names
set(EXECUTABLE_NAME assign3.out)
set(LIBRARY_NAME Library)

# 2. Define library and what source files it contains
add_library(${LIBRARY_NAME} 
    url_history.cpp 
    ../assign1/url.cpp
)

# 3. Add include directories for the library
# tells the compiler where to look for header files when compiling your library. 
# When your source files have #include statements, the compiler needs to know which directories to search in to find those header files.
# it needs to define after the library is created, so that it can find the header files
# and it needs to be PUBLIC so that the executable can also use the library's headers
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../assign1
)

# 4. Define the executable
add_executable(${EXECUTABLE_NAME} main.cpp)

# 5. Link the executable with the library so that executable can use the library
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
